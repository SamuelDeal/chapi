#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#include <string>

class itimerspec;

class SystemUtils {

public:
    static std::string getCurrentIp();
    static std::string getCurrentMask();
    static unsigned int ipStrToInt(const std::string &ip);
    static std::string ipIntToStr(unsigned int broadcastIp);
    static std::string getCurrentMacAddress();
    static int initTimer(itimerspec *interval, unsigned int msDelay, bool repeat = false);
    static bool isConneted();
    static void readTimer(int timerFd);
    static void delay(double usec);

private:
    SystemUtils();
};

#endif // SYSTEMUTILS_H
