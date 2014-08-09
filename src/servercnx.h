#ifndef SERVERCNX_H
#define SERVERCNX_H

#include <string>

#include "nlprotocol.h"
#include "config.h"

class Server;


class ServerCnx {
public:
    ServerCnx(int cnxFd);
    ~ServerCnx();

    int getCnxFd() const;
    bool isClosed() const;
    void onData();
    void sendConfig(Config &cfg, int nbrButtons);

private:
    void onCommand(NlCommand);
    void onFailure(NlCommand);
    void onClose(NlCommand);

    NlProtocol *_protocol;
    bool _closed;
    Config _newConfig;
    bool _readingConfig;
};

#endif // SERVERCNX_H
