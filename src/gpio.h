#ifndef GPIO_H
#define GPIO_H

namespace Gpio {
    enum Value {
        Low,
        High
    };

    class In {
    public:
        In(unsigned char pin);
        Gpio::Value read();

    private:
        unsigned char _pin;
    };

    class Out {
    public:
        Out(unsigned char pin);
        void write(Gpio::Value);

    private:
        unsigned char _pin;
    };
}

#endif // GPIO_H
