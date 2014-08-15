#ifndef CHAPI_H
#define CHAPI_H

#include "config.h"
#include "helloer.h"
#include "videohub.h"
#include "circuitconfig.h"
#include "led.h"

class LedGroup;
class ButtonGroup;
class Server;
class ServerCnx;


class Chapi {

public:
    Chapi(sigset_t &mask, Led &redLed);
    ~Chapi();

    void exec();

private:
    void onStatusChanged(VideoHub::CnxStatus status);
    void onInputChanged(unsigned char input);
    void onNetworkStatus(bool connected);
    void onConfigSet();
    int initFdSet(fd_set &readFsSet);

    void onConfigUpdateStart();
    void onTargetIpChanged(const std::string &newIp);
    void onConfigUpdateLoaded(Config &cfg);

    Config _cfg;
    Helloer _helloer;
    Server *_server;
    VideoHub *_vHub;
    CircuitConfig _circuit;
    Led _greenLed;
    Led &_redLed;
    int _nbrButtons;
    std::list<LedGroup*> _leds;
    std::list<ButtonGroup*> _btns;
    std::list<ServerCnx*> _serverCnxs;

    int _signalFd;
};

#endif // CHAPI_H
