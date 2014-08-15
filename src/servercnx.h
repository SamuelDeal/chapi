#ifndef SERVERCNX_H
#define SERVERCNX_H

#include <string>
#include <functional>


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
    void setCallbacks(std::function<void()> onConfigUpdateStart,
                      std::function<void(const std::string &)> onTargetIpChanged,
                      std::function<void(Config &cfg)> onConfigUpdateLoaded);

private:
    void onCommand(NlCommand);
    void onFailure(NlCommand);
    void onClose(NlCommand);

    NlProtocol *_protocol;
    bool _closed;
    Config _newConfig;
    bool _readingConfig;
    std::function<void()> _onConfigUpdateStart;
    std::function<void(const std::string &)> _onTargetIpChanged;
    std::function<void(Config &cfg)> _onConfigUpdateLoaded;
};

#endif // SERVERCNX_H
