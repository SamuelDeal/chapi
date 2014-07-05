#include "systemutils.h"

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <sys/timerfd.h>
#include <unistd.h>

#include "log.h"

std::string SystemUtils::getCurrentMacAddress() {
    std::string mac;
    std::ifstream sysfile("/sys/class/net/eth0/address");
    getline(sysfile, mac);
    return mac;
}


std::string SystemUtils::getCurrentIp() {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    std::string result;
    getifaddrs(&ifAddrStruct);

    for(ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if(ifa->ifa_addr->sa_family != AF_INET) {
            continue; //not IPv4, ignored
        }

        tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;

        char addressBuffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
        if(strcmp(ifa->ifa_name, "eth0") == 0){
            result = addressBuffer;
            break;
        }
    }
    if (ifAddrStruct!=NULL) {
        freeifaddrs(ifAddrStruct);
    }
    return result;
}


int SystemUtils::initTimer(itimerspec *interval, unsigned int msDelay, bool repeat) {
    int fd = -1;
    interval->it_value.tv_sec = msDelay / 1000000;
    interval->it_value.tv_nsec = (msDelay % 1000000) * 1000;
    if(repeat){
        interval->it_interval.tv_sec = msDelay / 1000000;
        interval->it_interval.tv_nsec = (msDelay % 1000000) * 1000;
    }
    else {
        interval->it_interval.tv_sec = 0;
        interval->it_interval.tv_nsec = 0;
    }
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if(fd == -1) {
        log(LOG_ERR, "unable to create timer: %s",  strerror(errno));
    }
    else {
        timerfd_settime(fd, 0, interval, NULL);
    }
    return fd;
}

void SystemUtils::readTimer(int timerFd){
    uint64_t data;
    read(timerFd, &data, sizeof(uint64_t));
}

std::string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}