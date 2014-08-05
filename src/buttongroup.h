#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <map>
#include <mutex>

#include "srinfo.h"
#include "gpio.h"
#include "pipe.h"

class ButtonGroup
{
public:
    enum EventType{
        none = 0,
        press,
        release,
        quit
    };

    struct ButtonEvent{
        ButtonEvent(EventType argEventType = none, int argIndex = -1);

        EventType eventType;
        int index;
    };

    ButtonGroup(const SRInfo &info, unsigned int offset);
    ~ButtonGroup();

    unsigned char getNbrButtons() const;
    Pipe<ButtonEvent> getPipe() const;

private:
    static void* _startThread(void*);
    void _start();
    void readButtons();

    unsigned char _nbrBtns;
    int _size;
    unsigned int _offset;
    std::map<int, int> _mapping;
    Pipe<ButtonEvent> _pipe;
    pthread_t _thread;
    std::mutex _mut;

    Gpio::In _dataPin;
    Gpio::Out _clockPin;
    Gpio::Out _latchPin;
};

#endif // BUTTONGROUP_H
