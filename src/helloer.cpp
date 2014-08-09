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
#include "error.h"

Helloer::Helloer()
{
    _socket = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == _socket){
        throw Error::system("socket opening failed !");
    }

    int broadcast=1;
    if(-1 == setsockopt(_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))) {
        throw Error::system("braodcast opening failed !");
    }

    struct sockaddr_in recvaddr;
    recvaddr.sin_family = AF_INET;
    recvaddr.sin_port = htons(CHAPI_BROADCAST_PORT);
    recvaddr.sin_addr.s_addr = INADDR_ANY;
    memset(recvaddr.sin_zero, '\0', sizeof(recvaddr.sin_zero));
    if(-1 == bind(_socket, (struct sockaddr*) &recvaddr, sizeof(recvaddr))) {
        throw Error::system("listener bind failed");
    }
    fcntl(_socket, F_SETFL, O_NONBLOCK);
}

Helloer::~Helloer() {
    close(_socket);
}

void Helloer::sayHello() {
    _lastHelloTime = ETime();

    unsigned int broadcastIp = SystemUtils::ipStrToInt(SystemUtils::getCurrentIp()) | (~ SystemUtils::ipStrToInt(SystemUtils::getCurrentMask()));
    std::string broadcastStr = SystemUtils::ipIntToStr(broadcastIp);

    struct sockaddr_in recvaddr;
    recvaddr.sin_family = AF_INET;
    recvaddr.sin_port = htons(CHAPI_BROADCAST_PORT);
    recvaddr.sin_addr.s_addr = inet_addr(broadcastStr.c_str());
    memset(recvaddr.sin_zero, '\0', sizeof(recvaddr.sin_zero));

    std::string msg = "HELLO " DEV_CHAPI_DEVICE " " CURRENT_VERSION " ";
    msg += SystemUtils::getCurrentMacAddress();
    msg += " ";
    msg += SystemUtils::getCurrentIp();
    msg += "\n";

    int sent = sendto(_socket, msg.c_str(), msg.length(), 0, (struct sockaddr *)&recvaddr, sizeof(recvaddr));
    if(-1 == sent) {
        log(LOG_ERR, "say hello : send failed at %s", broadcastStr.c_str());
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
    int receivedSize;
    do {
        receivedSize = recvfrom(_socket, buf, sizeof(buf), 0, (struct sockaddr *)&sendaddr, (socklen_t *)&addr_len);
    } while(receivedSize > 0);

    if(ETime::oneSecond() > ETime() - _lastHelloTime) {
        return; // We've just said hello, don't repeat it ad vitaem
    }
    sayHello();
}
