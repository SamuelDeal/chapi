#include "videohub.h"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>

#include "const.h"
#include "log.h"
#include "systemutils.h"

VideoHub::VideoHub(unsigned char outputIndex, const std::string &ip,
                   const std::function<void(unsigned char)>& onInputChanged,
                   const std::function<void(CnxStatus)>& onStatusChanged) {
    _outputIndex = outputIndex;
    _ip = ip;
    _onInputChanged = onInputChanged;
    _onStatusChanged = onStatusChanged;
    _socketFd = -1;
    _reconnectTimerFd = -1;
    _pingTimerFd = -1;
    _protocol = NULL;
    connect();
}

VideoHub::~VideoHub() {
    disconnect();
}

void VideoHub::connect() {
    disconnect();
    if(_reconnectTimerFd != -1){
        close(_reconnectTimerFd);
        _reconnectTimerFd = -1;
    }
    _onStatusChanged(Connecting);
    _routing.clear();
    _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(_socketFd < 0){
        log(LOG_ERR, "unable to open socket"); //should not happened !
        return;
    }

    struct sockaddr_in vhAddr;
    vhAddr.sin_family = AF_INET;
    vhAddr.sin_port = htons(VIDEOHUB_PORT);
    vhAddr.sin_addr.s_addr = inet_addr(_ip.c_str());
    memset(vhAddr.sin_zero, '\0', sizeof(vhAddr.sin_zero));

    if(::connect(_socketFd, (struct sockaddr *)&vhAddr, sizeof(vhAddr)) < 0){
        log(LOG_INFO, "unable to connect to %s", _ip.c_str());
        disconnect();
        _reconnectTimerFd = SystemUtils::initTimer(&_reconnectInterval, VH_RECONNECT_DELAY);
    }
    else {
        fcntl(_socketFd, F_SETFL, O_NONBLOCK);
        _protocol = new NlProtocol(_socketFd,
               std::bind(&VideoHub::onDataReceived, this, std::placeholders::_1),
               std::bind(&VideoHub::onFailure, this, std::placeholders::_1),
               std::bind(&VideoHub::onFailure, this, std::placeholders::_1)
            );
        _onStatusChanged(ReadingConfig);
    }
}

void VideoHub::disconnect() {
    if(_pingTimerFd != -1){
        close(_pingTimerFd);
        _pingTimerFd = -1;
    }
    if(_socketFd != -1){
        close(_socketFd);
        _socketFd = -1;
    }
    if(_protocol != NULL){
        delete _protocol;
        _protocol = NULL;
    }
    _onInputChanged(NO_INPUT);
    _onStatusChanged(NotConnected);
    _routing.clear();
}



int VideoHub::getSocketFd() const {
    return _socketFd;
}

int VideoHub::getReconnectTimerFd() const {
    return _reconnectTimerFd;
}

int VideoHub::getPingTimerFd() const {
    return _pingTimerFd;
}

void VideoHub::change(unsigned char output, const std::string &ip) {
    if(_ip == ip){
        if((output == _outputIndex) || _routing.empty()) {
            _outputIndex = output;
        }
        else{
            unsigned char oldInput = _routing[_outputIndex];
            _outputIndex = output;
            if(_routing[_outputIndex] != oldInput){
                _onInputChanged(_routing[_outputIndex]);
            }
        }
    }
    else {
        if(_socketFd != -1){
            close(_socketFd);
        }
        _ip = ip;
        _outputIndex = output;
        connect();
    }
}

void VideoHub::setInput(unsigned char input) {
    _routing[_outputIndex] = input;
    _onInputChanged(input);
    _protocol->sendCommand("VIDEO OUTPUT ROUTING", std::to_string(_outputIndex) + " " + std::to_string(input));
}


void VideoHub::onPingTimer() {
    if(_pingSent > VH_PING_LOST_TOLERANCE) {
        connect();
        return;
    }
    ++_pingSent;
    SystemUtils::readTimer(_pingTimerFd);
    _protocol->sendCommand("VIDEO OUTPUT LOCKS");
}

void VideoHub::onReconnectTimer() {
    SystemUtils::readTimer(_reconnectTimerFd);
    connect();
}

void VideoHub::onSocketData() {
    _protocol->read();
}

void VideoHub::onDataReceived(NlCommand cmd){
    _pingSent = 0;

    if(cmd.command != "VIDEO OUTPUT ROUTING"){
        return; //ignoring all other commands
    }

    bool endReadingConfig = false;
    unsigned char oldInput = NO_INPUT;
    if(_routing.empty()){
        endReadingConfig = true;
    }
    else {
        oldInput = _routing[_outputIndex];
    }
    for(std::list<std::string>::iterator it = cmd.lines.begin(); it != cmd.lines.end(); it++){
        std::string::size_type pos = it->find(' ');
        if(pos == std::string::npos){
            log(LOG_ERR, "bad line: %s", it->c_str());
            continue; //bad formatted line
        }
        unsigned char output = std::stoul(it->substr(0, pos));
        unsigned char input = std::stoul(it->substr(pos+1));
        _routing[output] = input;
        if((_outputIndex == output) && (input != oldInput)){
            _onInputChanged(input);
        }
    }
    if(endReadingConfig && (_routing.find(_outputIndex) != _routing.end())){
        _pingSent = 0;
        _pingTimerFd = SystemUtils::initTimer(&_pingInterval, VH_PING_DELAY, true);
        _onStatusChanged(Connected);
    }
}

void VideoHub::onFailure(NlCommand cmd){
    log(LOG_WARNING, "command failed %s", cmd.command.c_str());
}
