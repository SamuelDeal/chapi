#ifndef CHAPI_H
#define CHAPI_H

#include "config.h"
#include "helloer.h"
#include "server.h"
#include "videohub.h"

class Chapi {

public:
    Chapi();
    ~Chapi();

    void exec();

private:
    void onStatusChanged(VideoHub::CnxStatus status);
    void onInputChanged(unsigned char input);

    Config _cfg;
    Helloer _helloer;
    Server _server;
    VideoHub *_vHub;
};

#endif // CHAPI_H
