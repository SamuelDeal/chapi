#ifndef SERVERCNX_H
#define SERVERCNX_H

#include "nlprotocol.h"
#include "config.h"

class Server;


class ServerCnx {
public:
    ServerCnx(int cnxFd, Server &owner);
    ~ServerCnx();

    int getCnxFd() const;
    void onData();
    void sendConfig(Config &cfg, int nbrButtons);

private:
    void onCommand(NlCommand);
    void onFailure(NlCommand);
    void onClose(NlCommand);

    NlProtocol *_protocol;
    Server &_owner;
};

#endif // SERVERCNX_H
