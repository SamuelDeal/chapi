#ifndef SERVERCNX_H
#define SERVERCNX_H


class Server;

class ServerCnx {
public:
    ServerCnx(int cnxFd, Server &owner);
    ~ServerCnx();

    int getCnxFd() const;
    void onData();

private:
    int _cnxFd;
    Server &_owner;
};

#endif // SERVERCNX_H
