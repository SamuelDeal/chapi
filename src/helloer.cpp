#include "helloer.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#include "const.h"
#include "log.h"
#include "systemutils.h"

Helloer::Helloer()
{
    _socket = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == _socket){
        throw "socket opening failed !";
    }

    int broadcast=1;
    if(-1 == setsockopt(_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))) {
        throw "braodcast opening failed !";
    }

    struct sockaddr_in recvaddr;
    recvaddr.sin_family = AF_INET;
    recvaddr.sin_port = htons(CHAPI_BROADCAST_PORT);
    recvaddr.sin_addr.s_addr = INADDR_ANY;
    memset(recvaddr.sin_zero, '\0', sizeof(recvaddr.sin_zero));
    if(-1 == bind(_socket, (struct sockaddr*) &recvaddr, sizeof(recvaddr))) {
        throw "listener bind failed";
    }
    fcntl(_socket, F_SETFL, O_NONBLOCK);
    sayHello();
}

Helloer::~Helloer() {
    close(_socket);
}

void Helloer::sayHello() {
    _lastHelloTime = ETime();

    struct sockaddr_in recvaddr;
    recvaddr.sin_family = AF_INET;
    recvaddr.sin_port = htons(CHAPI_BROADCAST_PORT);
    recvaddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    memset(recvaddr.sin_zero, '\0', sizeof(recvaddr.sin_zero));

    std::string msg = "HELLO " DEV_CHAPI_DEVICE " " CURRENT_VERSION " ";
    msg += SystemUtils::getCurrentMacAddress();
    msg += " ";
    msg += SystemUtils::getCurrentIp();
    msg += "\n";

    if(-1 == sendto(_socket, msg.c_str(), msg.length(), 0, (struct sockaddr *)&recvaddr, sizeof(recvaddr))) {
        log(LOG_ERR, "say hello : send failed");
    }
}

int Helloer::getFd() const {
    return _socket;
}

void Helloer::onMsgReceived() {
    struct sockaddr_in sendaddr;
    sendaddr.sin_family = AF_INET;
    sendaddr.sin_port = htons(CHAPI_BROADCAST_PORT);
    sendaddr.sin_addr.s_addr = INADDR_ANY;
    memset(sendaddr.sin_zero, '\0', sizeof(sendaddr.sin_zero));
    socklen_t addr_len = sizeof(sendaddr);

    char buf[512];
    while(recvfrom(_socket, buf, sizeof(buf), 0, (struct sockaddr *)&sendaddr, (socklen_t *)&addr_len) > 0) {
        //I don't care about what I've received, but we need to read it for next polling
    }

    if(ETime::oneSecond() > ETime() - _lastHelloTime) {
        return; // We've just said hello, don't repeat it ad vitaem
    }
    sayHello();
}