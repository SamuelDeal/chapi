#ifndef SERVERCNX_H
#define SERVERCNX_H

#include <string>

class Server;

class ServerCnx {
public:
    ServerCnx(int cnxFd, Server &owner);
    ~ServerCnx();

    int getCnxFd() const;
    void onData();

private:
    void parse();

    int _cnxFd;
    Server &_owner;
    std::string _buffer;
};

#endif // SERVERCNX_H
