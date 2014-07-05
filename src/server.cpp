#include "server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

#include "const.h"
#include "servercnx.h"

Server::Server() {
    _socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == _socketFd){
        throw "socket opening failed !";
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CHAPI_TCP_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
    if(-1 == bind(_socketFd, (struct sockaddr*) &addr, sizeof(addr))) {
        throw "listener bind failed";
    }

    listen(_socketFd, 10);
    fcntl(_socketFd, F_SETFL, O_NONBLOCK);
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

int Server::onNewCnx() {

}



/*
int _serverSocketFd;
std::list<ServerCnx*> _cnx;
*/