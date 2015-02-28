#ifndef LEDGROUP_H
#define LEDGROUP_H

#include <map>

#include "srinfo.h"
#include "gpio.h"


class LedGroup {
public:
    LedGroup(const SRInfo &info);
    ~LedGroup();

    void on(unsigned char index, bool buffered = false);
    void off(unsigned char index, bool buffered = false);
    void clear(bool buffered = false);
    unsigned char getNbrButtons() const;

private:
    void write();

    bool *_values;
    unsigned char _nbrBtns;
    int _size;
    std::map<int, int> _mapping;
    Gpio::Out _dataPin;
    Gpio::Out _clockPin;
    Gpio::Out _latchPin;
};

#endif // LEDGROUP_H
