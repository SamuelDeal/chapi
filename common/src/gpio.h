#ifndef GPIO_H
#define GPIO_H

#include <string>

namespace Gpio {

enum Value {
    Low = 0,
    High = 1
};

class Core {
public:
    enum Direction {
        In,
        Out
    };

protected:
    unsigned char _pin;

    Core(unsigned char pin, Direction dir);
    ~Core() throw();
};


class In: public Core {
public:
    In(unsigned char pin);
    Gpio::Value read();

protected:
    std::string _filepath;
};

class Out: public Core {
public:
    Out(unsigned char pin);
    void write(Gpio::Value);

protected:
    std::string _filepath;
};

}

#endif // GPIO_H
