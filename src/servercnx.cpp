#include "servercnx.h"

#include <unistd.h>

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

}
