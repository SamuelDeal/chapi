#ifndef CHAPI_H
#define CHAPI_H

#include "config.h"
#include "helloer.h"
#include "server.h"
#include "videohub.h"
#include "circuitconfig.h"
#include "led.h"

class LedGroup;

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

    Config _cfg;
    Helloer _helloer;
    Server _server;
    VideoHub *_vHub;
    CircuitConfig _circuit;
    Led _greenLed;
    Led &_redLed;
    int _nbrButtons;
    std::list<LedGroup*> _leds;

    int _signalFd;
};

#endif // CHAPI_H
