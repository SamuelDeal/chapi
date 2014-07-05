#include "nlprotocol.h"

#include <sys/socket.h>
#include <iostream>

#include "stringutils.h"

NlProtocol::NlProtocol(int socketFd, Callback onReceived, Callback onFailure) {
    _socketFd = socketFd;
    _onCommandFailed = onFailure;
    _onCommandReceived = onReceived;
    _reading = false;
}

void NlProtocol::sendCommand(const std::string& cmd){
    sendCommand(cmd, std::list<std::string>());
}

void NlProtocol::sendCommand(const std::string& cmd, const std::string &line){
    std::list<std::string> lines;
    lines.push_back(line);
    sendCommand(cmd, lines);
}

void NlProtocol::sendCommand(const std::string& cmd, const std::list<std::string> &lines){
    NlCommand toSend;
    toSend.command = cmd;
    toSend.lines = lines;
    if(_reading){
        _outQueue.push(toSend);
    }
    else{
        send(toSend);
    }
}

void NlProtocol::send(const NlCommand& cmd) {
    _sendingCommand = cmd;

    std::string toSend = cmd.command + ":\n";
    for(auto it = cmd.lines.begin(); it != cmd.lines.end(); it++){
        toSend += *it + "\n";
    }
    toSend += "\n";
    ::send(_socketFd, toSend.c_str(), toSend.length(), 0);
    //no flush ?
}


void NlProtocol::read() {
    _reading = true;
    char buffer[512];
    int readBytes = recv(_socketFd, buffer, sizeof(buffer), 0);
    while(readBytes > 0) {
        buffer[readBytes] = '\0';
        _readBuffer.append(buffer);

        std::string::size_type pos = _readBuffer.find('\n',0);
        while(pos != std::string::npos){
            std::string tmp = _readBuffer.substr(0, pos);
            std::string line = trim(tmp);
            _readBuffer  = _readBuffer.substr(pos+1);
            if(line.empty()){
                _reading = !_readBuffer.empty();
                parseCommand();
            }
            else if(_readingCommand.command.empty()) {
                _readingCommand.command = line;
            }
            else{
                _readingCommand.lines.push_back(line);
            }
            pos = _readBuffer.find('\n', 0);
        }
        readBytes = recv(_socketFd, buffer, sizeof(buffer), 0);
    }
    if(_readBuffer.empty()){
        _reading = false;
    }
}

void NlProtocol::parseCommand() {
    if(_readingCommand.command.empty()){
        return;
    }
    if(_readingCommand.command == "ACK"){
        popSendingQueue();
    }
    else if(_readingCommand.command == "NAK"){
        _onCommandFailed(_sendingCommand);
        popSendingQueue();
    }
    else{
        _readingCommand.command.resize(_readingCommand.command.length()-1);
        _onCommandReceived(_readingCommand);
    }
    _readingCommand.command = "";
    _readingCommand.lines.clear();
}

void NlProtocol::popSendingQueue() {
    if(_reading || _outQueue.empty()){
        return;
    }
    send(_outQueue.front());
    _outQueue.pop();
}


