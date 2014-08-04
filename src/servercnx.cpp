#include "servercnx.h"

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"
#include "error.h"

ServerCnx::ServerCnx(int cnxFd, Server &owner) : _owner(owner) {
    _cnxFd = cnxFd;
}

ServerCnx::~ServerCnx() {
    close(_cnxFd);
}

int ServerCnx::getCnxFd() const {
    return _cnxFd;
}

void ServerCnx::onData() {
    char readBuffer[1024];
    int readLength = recv(_cnxFd, readBuffer, sizeof(readBuffer)-1, 0);
    if(readLength == 0) {
        _owner.onCnxClose(this);
    }
    else if(readLength < 0) {
        throw Error::system("bad socket read");
    }
    else {
        readBuffer[readLength] = '\0';
        _buffer += readBuffer;
        parse();
    }
}

void ServerCnx::parse() {
    std::cout << _buffer << std::endl;
    _buffer = "";
}
