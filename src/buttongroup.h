#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <map>

#include "srinfo.h"
#include "gpio.h"

class ButtonGroup
{
public:
    ButtonGroup(const SRInfo &info);
    ~ButtonGroup();

    unsigned char getNbrButtons() const;

private:
    unsigned char _nbrBtns;
    int _size;
    std::map<int, int> _mapping;

    Gpio::In _dataPin;
    Gpio::Out _clockPin;
    Gpio::Out _latchPin;
};

#endif // BUTTONGROUP_H
