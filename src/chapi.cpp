#include "chapi.h"

#include <cstring>
#include <functional>
#include <iostream>

#include "log.h"

Chapi::Chapi() {
    _cfg.load();
    _vHub = NULL;
    _vHub = new VideoHub(2, "192.168.10.51",
             std::bind(&Chapi::onInputChanged, this, std::placeholders::_1),
             std::bind(&Chapi::onStatusChanged, this, std::placeholders::_1));
}

Chapi::~Chapi() {
    if(_vHub != NULL){
        delete _vHub;
    }
}


void Chapi::exec() {
    bool exit = false;
    int fd;

    while(!exit) {
        fd_set readFsSet;
        FD_ZERO(&readFsSet);
        FD_SET(_helloer.getFd(), &readFsSet);
        int max = _helloer.getFd();

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

        fd = _server.getSocketFd();
        if(fd != -1){
            FD_SET(fd, &readFsSet);
            max = std::max(max, fd);
        }

        if(select(max+1, &readFsSet, NULL, NULL, NULL) == -1) {
            log(LOG_ERR, "unable to listen file descriptors: %s", strerror(errno));
            return;
        }
        if(FD_ISSET(_helloer.getFd(), &readFsSet)){
            _helloer.onMsgReceived();
        }
        if((_vHub->getSocketFd() != -1) && FD_ISSET(_vHub->getSocketFd(), &readFsSet)){
            _vHub->onSocketData();
        }
        if((_vHub->getReconnectTimerFd() != -1) && FD_ISSET(_vHub->getReconnectTimerFd(), &readFsSet)){
            _vHub->onReconnectTimer();
        }
        if((_vHub->getPingTimerFd() != -1) && FD_ISSET(_vHub->getPingTimerFd(), &readFsSet)){
            _vHub->onPingTimer();
        }
        if(FD_ISSET(_server.getSocketFd(), &readFsSet)){
            _server.onNewCnx();
        }
    }
}

void Chapi::onStatusChanged(VideoHub::CnxStatus status) {
    std::cout << "new status : " << status << std::endl;
}

void Chapi::onInputChanged(unsigned char input) {
    std::cout << "new input : " << (int)input << std::endl;
}
