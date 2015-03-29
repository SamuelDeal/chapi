#ifndef HELLOER_H
#define HELLOER_H

#include "etime.h"

class Helloer {

public:
    Helloer();
    ~Helloer();

    void sayHello();
    int getFd() const;

    void onMsgReceived();

protected:
    ETime _lastHelloTime;
    int _socket;
};

#endif // HELLOER_H
