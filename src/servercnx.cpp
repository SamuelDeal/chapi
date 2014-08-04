#include "servercnx.h"

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"
#include "error.h"
#include "const.h"

ServerCnx::ServerCnx(int cnxFd) {
    _closed = false;
    _protocol = new NlProtocol(cnxFd,
       std::bind(&ServerCnx::onCommand, this, std::placeholders::_1),
       std::bind(&ServerCnx::onFailure, this, std::placeholders::_1),
       std::bind(&ServerCnx::onClose, this, std::placeholders::_1));
}

ServerCnx::~ServerCnx() {
    close(_protocol->getSocketFd());
    delete _protocol;
}

bool ServerCnx::isClosed() const {
    return _closed;
}

int ServerCnx::getCnxFd() const {
    return _protocol->getSocketFd();
}

void ServerCnx::onData() {
    if(_closed) {
        return;
    }
    _protocol->read();
}

void ServerCnx::onCommand(NlCommand cmd){
    if(cmd.command == "PING"){
        _protocol->sendCommand("PONG");
    }
}

void ServerCnx::onFailure(NlCommand cmd) {
    throw Error::other("bad command:" +cmd.command);
}

void ServerCnx::onClose(NlCommand cmd) {
    _closed = true;
}

void ServerCnx::sendConfig(Config &cfg, int nbrButtons) {
    _protocol->sendCommand("VERSION", CURRENT_VERSION);
    _protocol->sendCommand("CONFIG_BEGIN");

    _protocol->sendCommand("CONFIG_SET", "0");
    _protocol->sendCommand("NBR_BUTTONS", std::to_string(nbrButtons));
    if(cfg.isSet()){
        //TODO
    }

    _protocol->sendCommand("CONFIG_END");
}

/*
const char configSetStr[] = "CONFIG_SET:";
const char nbrBtnsStr[] = "NBR_BUTTONS:";
const char dhcpStr[] = "DHCP:";
const char ipStr[] = "IP:";
const char netmaskStr[] = "NETMASK:";
const char gatewayStr[] = "GATEWAY:";
const char targetMacStr[] = "TARGET_MAC:";
const char ouputStr[] = "MEM_OUTPUT:";
const char inputStr[] = "MEM_INPUT:";
const char cnxStatusStr[] = "CNX_STATUS:";

void ChapiDevice::parseLine(const QString &line){
    if(line == "PONG"){
        _pingSent = 0;
    }
    else if(line == "CONFIG_BEGIN"){
        setStatus(Device::ReadingConfig);
    }
    else if(line == "CONFIG_END") {
        updateDeviceStatus();
    }
*/
