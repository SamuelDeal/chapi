#ifndef NLPROTOCOL_H
#define NLPROTOCOL_H

#include <list>
#include <string>
#include <queue>
#include <functional>

struct NlCommand {
    std::string command;
    std::list<std::string> lines;
};

class NlProtocol {

public:
    typedef std::function<void(NlCommand)> Callback;

    NlProtocol(int socketFd, Callback onReceived, Callback onFailure, Callback onClose);

    void sendCommand(const std::string& cmd, const std::list<std::string> &lines);
    void sendCommand(const std::string& cmd, const std::string &line);
    void sendCommand(const std::string& cmd);
    void read();
    int getSocketFd() const;

private:
    void send(const NlCommand& cmd);
    void parseCommand();
    void popSendingQueue();

    int _socketFd;
    std::string _readBuffer;
    std::queue<NlCommand> _outQueue;
    bool _reading;
    NlCommand _sendingCommand;
    NlCommand _readingCommand;

    Callback _onCommandFailed;
    Callback _onCommandReceived;
    Callback _onClose;
};

#endif // NLPROTOCOL_H
