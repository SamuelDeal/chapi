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
#include <sstream>

#include "log.h"

std::string SystemUtils::getCurrentMacAddress() {
    std::string mac;
    std::ifstream sysfile("/sys/class/net/eth0/address");
    getline(sysfile, mac);
    return mac;
}


bool SystemUtils::isConneted(){
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    bool foundEth0 = false;
    getifaddrs(&ifAddrStruct);

    for(ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if(ifa->ifa_addr->sa_family != AF_INET) {
            continue; //not IPv4, ignored
        }

        tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;

        char addressBuffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
        if(strcmp(ifa->ifa_name, "eth0") == 0){
            foundEth0 = true;
            break;
        }
    }
    if (ifAddrStruct!=NULL) {
        freeifaddrs(ifAddrStruct);
    }
    return foundEth0;
}

std::string SystemUtils::getCurrentIp() {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    std::string result = "127.0.0.1";
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

std::string SystemUtils::getCurrentMask() {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    std::string result = "255.255.255.0";
    getifaddrs(&ifAddrStruct);

    for(ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if(ifa->ifa_addr->sa_family != AF_INET) {
            continue; //not IPv4, ignored
        }

        tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr;

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

unsigned int SystemUtils::ipStrToInt(const std::string &ip) {
    std::stringstream stream(ip);
    unsigned int a,b,c,d;
    char ch;
    stream >> a >> ch >> b >> ch >> c >> ch >> d;
    return ((a*256 + b)*256 + c)*256 + d;
}

std::string SystemUtils::ipIntToStr(unsigned int ip) {
    unsigned int bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    std::stringstream stream;
    stream << bytes[3] << '.' << bytes[2] << '.' << bytes[1] << '.' << bytes[0];
    return stream.str();
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
    int result = read(timerFd, &data, sizeof(uint64_t));
    if(result == -1){
        log(LOG_ERR, "unable to read file descriptors: %d, %s", result, strerror(errno));
    }
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

void SystemUtils::delay(double usec) {
    struct timespec sleeper, dummy ;

    sleeper.tv_sec = (time_t)(usec / 1000000) ;
    sleeper.tv_nsec = (time_t)(((long long)(usec*1000)) % 1000000000);

    nanosleep(&sleeper, &dummy) ;
}
