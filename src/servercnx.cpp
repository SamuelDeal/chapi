#include "servercnx.h"

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>

#include "server.h"
#include "error.h"
#include "const.h"

ServerCnx::ServerCnx(int cnxFd) {
    _closed = false;
    _readingConfig = false;
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

void ServerCnx::setCallbacks(std::function<void()> onConfigUpdateStart,
                  std::function<void(const std::string &)> onTargetIpChanged,
                  std::function<void(Config &cfg)> onConfigUpdateLoaded) {
    _onConfigUpdateStart = onConfigUpdateStart;
    _onTargetIpChanged = onTargetIpChanged;
    _onConfigUpdateLoaded = onConfigUpdateLoaded;
}

void ServerCnx::onCommand(NlCommand cmd){
    if(cmd.command == "PING"){
        _protocol->sendCommand("PONG");
    }
    else if(cmd.command == "CONFIG_BEGIN") {
        _readingConfig = true;
        _newConfig.clear();
        _onConfigUpdateStart();
    }
    else if(cmd.command == "TARGET_TYPE") {
        _newConfig.set("target_type", *cmd.lines.begin());
    }
    else if(cmd.command == "TARGET_MAC") {
        _newConfig.set("target_mac", *cmd.lines.begin());
    }
    else if(cmd.command == "TARGET_IP") {
        if(_readingConfig) {
            _newConfig.set("last_ip", *cmd.lines.begin());
        }
        else {
            _onTargetIpChanged(*cmd.lines.begin());
        }
    }
    else if(cmd.command == "NETWORK") {
        for(auto i = cmd.lines.begin(); i != cmd.lines.end(); i++){
            std::string what, value;
            std::stringstream sstream(*i);
            if(getline(sstream,what,' ') && getline(sstream,value)) {
                _newConfig.set(what, value);
            }
        }
    }
    else if(cmd.command == "OUTPUTS") {
        for(auto i = cmd.lines.begin(); i != cmd.lines.end(); i++){
            std::string what, value;
            std::stringstream sstream(*i);
            if(std::getline(sstream, what,' ') && std::getline(sstream,value)) {
                _newConfig.set("output_"+what, value);
            }
        }
    }
    else if(cmd.command == "INPUTS") {
        for(auto i = cmd.lines.begin(); i != cmd.lines.end(); i++){
            std::string what, value;
            std::stringstream sstream(*i);
            if(std::getline(sstream, what, ' ') && std::getline(sstream,value)) {
                _newConfig.set("input_"+what, value);
            }
        }
    }
    else if(cmd.command == "CONFIG_END") {
        _readingConfig = false;
        _onConfigUpdateLoaded(_newConfig);
        _newConfig.clear();
    }
}

void ServerCnx::onFailure(NlCommand cmd) {
    throw Error::other("bad command:" +cmd.command);
}

void ServerCnx::onClose(NlCommand cmd) {
    _closed = true;
}

void ServerCnx::sendConfig(Config &cfg, int nbrButtons) {
    _protocol->sendCommand("CONFIG_BEGIN");
    _protocol->sendCommand("VERSION", CURRENT_VERSION);

    _protocol->sendCommand("NBR_BUTTONS", std::to_string(nbrButtons));
    if(cfg.isEmpty()){
        _protocol->sendCommand("CONFIG_SET", "0");
    }
    else {
        _protocol->sendCommand("CONFIG_SET", "1");
        _protocol->sendCommand("TARGET_TYPE", cfg.get("target_type", "vhub"));
        _protocol->sendCommand("TARGET_MAC", cfg.get("target_mac", ""));
        if(cfg.isSet("last_ip")) {
            _protocol->sendCommand("TARGET_IP", cfg.get("last_ip", ""));
        }
        std::list<std::string> netInfo;
        netInfo.push_back("dhcp "+cfg.get("dhcp", "1"));
        if(cfg.isSet("ip")) {
            netInfo.push_back("ip "+ cfg.get("ip", ""));
        }
        if(cfg.isSet("mask")) {
            netInfo.push_back("mask "+ cfg.get("mask", ""));
        }
        if(cfg.isSet("gateway")) {
            netInfo.push_back("gateway "+ cfg.get("gateway", ""));
        }
        _protocol->sendCommand("NETWORK", netInfo);
        if(cfg.get("target_type", "vhub") == "vhub"){
            _protocol->sendCommand("OUTPUTS", "0 "+cfg.get("output_0", "0"));
        }
        else {
            //TODO ATEM
        }
        std::list<std::string> inputs;
        for(int i = 0; i < nbrButtons; i++){
            inputs.push_back(std::to_string(i)+" "+cfg.get("input_"+std::to_string(i), "255"));
        }
        _protocol->sendCommand("INPUTS", inputs);
    }
    _protocol->sendCommand("CONFIG_END");
}
