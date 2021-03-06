#ifndef _LED_HPP
#define _LED_HPP

#include <mutex>

#include "pipe.h"
#include "gpio.h"

//TODO: perf optim with poll
class Led {
    public:
       Led(int ledPin);
       ~Led();
       void on();
       void off();
       void blinkSlowly();
       void blinkQuickly();
       void blinkNumber(unsigned int);

    protected:
       static const char ON = 1;
       static const char OFF = 2;
       static const char BLINK_SLOWLY = 3;
       static const char BLINK_QUICKLY = 4;
       static const char BLINK_NUMBER = 5;
       static const char QUIT = 6;
       static const long SLOW_TIME = 300000;
       static const long QUICK_TIME = 50000;
       static const long NUMBER_TIME = 250000;

       Pipe<char> _pipe;
       unsigned int _threadIndex;
       std::mutex _mut;
       bool _isOn;
       char _status;
       Gpio::Out _pin;
       unsigned int _blinkNumber;
       unsigned int _blinkCount;

       void _light(bool);
       void _stopBlinking();
       bool _blinking();
       void _blink();
       long _getBlinkDelay();
};

#endif // _LED_HPP
