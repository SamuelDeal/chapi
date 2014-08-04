#include "server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

#include "const.h"
#include "servercnx.h"
#include "error.h"

Server::Server() {
    _socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == _socketFd){
        throw Error::system("socket opening failed !");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CHAPI_TCP_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
    if(-1 == bind(_socketFd, (struct sockaddr*) &addr, sizeof(addr))) {
        throw Error::system("listener bind failed");
    }
    fcntl(_socketFd, F_SETFL, O_NONBLOCK);
    listen(_socketFd, 10);
}


Server::~Server(){
    close(_socketFd);
    while(!_cnx.empty()){
        delete *(_cnx.begin());
        _cnx.pop_front();
    }

}

int Server::getSocketFd() const {
    return _socketFd;
}

void Server::onNewCnx() {
    struct sockaddr_in remoteAddr;
    socklen_t addrSize = sizeof(remoteAddr);
    int cnxFd = accept(_socketFd, (struct sockaddr*) &remoteAddr, &addrSize);
    if(cnxFd < 0) {
        throw Error::system("listener accept failed");
    }

    ServerCnx *cnx= new ServerCnx(cnxFd, *this);
    _cnx.push_back(cnx);
}

void Server::onCnxClose(ServerCnx *cnx) {
    _cnx.remove_if([](ServerCnx *that) {
        return that == cnx;
    });
    delete cnx;
}

const std::list<ServerCnx*>& Server::getCnx() const {
    return _cnx;
}



/*
int _serverSocketFd;
std::list<ServerCnx*> _cnx;
*/
