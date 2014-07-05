#ifndef SERVER_H
#define SERVER_H

#include <list>

class ServerCnx;

class Server {
public:
    Server();
    ~Server();

    int getSocketFd() const;
    int onNewCnx();

private:
    int _socketFd;
    std::list<ServerCnx*> _cnx;
};

#endif // SERVER_H
