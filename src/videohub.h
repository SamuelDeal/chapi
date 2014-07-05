#ifndef VIDEOHUB_H
#define VIDEOHUB_H

#include <string>
#include <map>
#include <functional>
#include <time.h>

#include "nlprotocol.h"

class VideoHub {
public:
    static const unsigned char NO_INPUT = 254;

    enum CnxStatus {
        NotConnected = 1,
        Connecting = 2,
        ReadingConfig = 3,
        Connected = 4
    };

    VideoHub(unsigned char outputIndex, const std::string &ip,
             const std::function<void(unsigned char)>& onInputChanged,
             const std::function<void(CnxStatus)>& onStatusChanged);
    ~VideoHub();

    void setInput(unsigned char input);
    void change(unsigned char output, const std::string &ip);

    void onReconnectTimer();
    void onPingTimer();
    void onSocketData();

    int getSocketFd() const;
    int getReconnectTimerFd() const;
    int getPingTimerFd() const;

private:
    void connect();
    void disconnect();
    void onDataReceived(NlCommand);
    void onFailure(NlCommand);

    unsigned char _outputIndex;
    std::string _ip;
    std::map<unsigned char, unsigned char> _routing;
    int _socketFd;
    int _reconnectTimerFd;
    itimerspec _reconnectInterval;
    int _pingTimerFd;
    itimerspec _pingInterval;
    unsigned int _pingSent;
    std::function<void(unsigned char)> _onInputChanged;
    std::function<void(CnxStatus)> _onStatusChanged;
    NlProtocol *_protocol;

};

#endif // VIDEOHUB_H
