#include "chapi.h"

#include <cstring>
#include <functional>
#include <iostream>
#include <signal.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <fstream>

#include "const.h"
#include "log.h"
#include "error.h"
#include "systemutils.h"
#include "ledgroup.h"
#include "buttongroup.h"
#include "server.h"
#include "servercnx.h"

Chapi::Chapi(sigset_t &mask, Led &redLed) : _greenLed(23), _redLed(redLed) {
    _vHub = NULL;
    _server = NULL;
    _signalFd = signalfd(-1, &mask, 0);
    if(_signalFd == -1) {
        throw Error::system("signalfd failed");
    }

    _cfg.load();
    if(SystemUtils::isConneted()){
        onNetworkStatus(true);
    }

    int nbrButtonsInput = 0;
    std::list<SRInfo*> inputs = _circuit.getInputs();
    for(auto i = inputs.begin(); i != inputs.end(); i++){
        ButtonGroup *btnGroup = new ButtonGroup(**i, nbrButtonsInput);
        nbrButtonsInput += btnGroup->getNbrButtons();
        _btns.push_back(btnGroup);
    }

    int nbrButtonsOutput = 0;
    std::list<SRInfo*> outputs = _circuit.getOutputs();
    for(auto i = outputs.begin(); i != outputs.end(); i++){
        LedGroup *ledGroup = new LedGroup(**i);
        ledGroup->clear();
        nbrButtonsOutput = std::max(nbrButtonsOutput, (int)ledGroup->getNbrButtons());
        _leds.push_back(ledGroup);
    }

    _nbrButtons = std::min(nbrButtonsInput, nbrButtonsOutput);
    log(LOG_DEBUG, "buttons final: %d", _nbrButtons);
}

Chapi::~Chapi() {
    if(_vHub != NULL){
        delete _vHub;
    }

    for(auto i = _leds.begin(); i != _leds.end(); i++){
        delete(*i);
    }

    for(auto i = _btns.begin(); i != _btns.end(); i++){
        delete(*i);
    }
}

void Chapi::onConfigSet(){
    _redLed.off();
    _greenLed.blinkSlowly();

    _vHub = new VideoHub(_nbrButtons, "192.168.10.51",
                 std::bind(&Chapi::onInputChanged, this, std::placeholders::_1),
                 std::bind(&Chapi::onStatusChanged, this, std::placeholders::_1));
}

void Chapi::exec() {
    bool exit = false;
    int fd;
    struct signalfd_siginfo fdsi;

    while(!exit) {
        fd_set readFsSet;
        FD_ZERO(&readFsSet);
        FD_SET(_helloer.getFd(), &readFsSet);
        int max = _helloer.getFd();

        FD_SET(_signalFd, &readFsSet);
        max = std::max(max, _signalFd);
        if(_vHub != NULL){
            fd = _vHub->getSocketFd();
            if(fd != -1){
                FD_SET(fd, &readFsSet);
                max = std::max(max, fd);
            }

            fd = _vHub->getReconnectTimerFd();
            if(fd != -1){
                FD_SET(fd, &readFsSet);
                max = std::max(max, fd);
            }

            fd = _vHub->getPingTimerFd();
            if(fd != -1){
                FD_SET(fd, &readFsSet);
                max = std::max(max, fd);
            }
        }
        if(_server != NULL) {
            fd = _server->getSocketFd();
            if(fd != -1){
                FD_SET(fd, &readFsSet);
                max = std::max(max, fd);
            }
            for(auto i = _server->getCnx().begin(); i != _server->getCnx().end(); i++){
                fd = (*i)->getCnxFd();
                if(fd != -1){
                    FD_SET(fd, &readFsSet);
                    max = std::max(max, fd);
                }
            }
        }
        for(auto i = _btns.begin(); i != _btns.end(); i++){
            fd = (*i)->getEventFd();
            if(fd != -1){
                FD_SET(fd, &readFsSet);
                max = std::max(max, fd);
            }
        }



        if(select(max+1, &readFsSet, NULL, NULL, NULL) == -1) {
            log(LOG_ERR, "unable to listen file descriptors: %s", strerror(errno));
            return;
        }
        if(FD_ISSET(_signalFd, &readFsSet)){
            if(read(_signalFd, &fdsi, sizeof(struct signalfd_siginfo)) == -1){
                throw Error::system("read signalfd failed");
            }
            if(fdsi.ssi_signo == SIGUSR1) {
                onNetworkStatus(true);
            }
            else if(fdsi.ssi_signo == SIGUSR2) {
                onNetworkStatus(false);
            }
            else { //SIGINT or SIGTERM
                log(LOG_INFO, "signal received, exiting...");
                exit = true;
            }
        }
        if(FD_ISSET(_helloer.getFd(), &readFsSet)){
            _helloer.onMsgReceived();
        }
        if(_vHub != NULL){
            if((_vHub->getSocketFd() != -1) && FD_ISSET(_vHub->getSocketFd(), &readFsSet)){
                _vHub->onSocketData();
            }
            if((_vHub->getReconnectTimerFd() != -1) && FD_ISSET(_vHub->getReconnectTimerFd(), &readFsSet)){
                _vHub->onReconnectTimer();
            }
            if((_vHub->getPingTimerFd() != -1) && FD_ISSET(_vHub->getPingTimerFd(), &readFsSet)){
                _vHub->onPingTimer();
            }
        }
        if(_server != NULL) {
            for(auto i = _server->getCnx().begin(); i != _server->getCnx().end(); i++){
                if(FD_ISSET((*i)->getCnxFd(), &readFsSet)) {
                    log(LOG_DEBUG, "on data");
                    (*i)->onData();
                }
            }
            _server->cleanClosedCnx();
            if(FD_ISSET(_server->getSocketFd(), &readFsSet)){
                log(LOG_DEBUG, "creating cnx");
                ServerCnx *newCnx = _server->onNewCnx();
                newCnx->sendConfig(_cfg, _nbrButtons);
            }
        }
        for(auto i = _btns.begin(); i != _btns.end(); i++){
            if(FD_ISSET((*i)->getEventFd(), &readFsSet)) {
                ButtonGroup::ButtonEvent evt = (*i)->getEvent();
                log(LOG_DEBUG, "btn %d %s", evt.index, evt.eventType == ButtonGroup::press ? "pressed" : "released");
            }
        }
    }
}

void Chapi::onStatusChanged(VideoHub::CnxStatus status) {
    std::cout << "new status : " << status << std::endl;
    if(!status == VideoHub::Connected){
        for(auto i = _leds.begin(); i != _leds.end(); i++){
            (*i)->clear();
        }
    }
}

void Chapi::onInputChanged(unsigned char input) {
    std::cout << "new input : " << (int)input << std::endl;
    for(auto i = _leds.begin(); i != _leds.end(); i++){
        (*i)->clear(true);
        (*i)->on(input);
    }
}

void Chapi::onNetworkStatus(bool connected) {
    if(connected){
        log(LOG_DEBUG, "connected");
        _helloer.sayHello();
        if(_cfg.isSet()) {
           _redLed.off();
           _greenLed.blinkSlowly();
        }
        else{
           _redLed.on();
        }
        if(_server == NULL){
            log(LOG_DEBUG, "creating server");
            _server = new Server();
        }
    }
    else{
        log(LOG_DEBUG, "deconnected");
        _greenLed.off();
        _redLed.blinkQuickly();
        if(_server != NULL){
            delete _server;
            _server = NULL;
        }
    }
}


