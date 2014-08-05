#include "buttongroup.h"

#include <signal.h>

#include "log.h"
#include "error.h"
#include "systemutils.h"
#include "threader.h"

#include <iostream>

unsigned char ButtonGroup::QUIT = 2;

ButtonGroup::ButtonEvent::ButtonEvent(EventType argEventType, int argIndex){
    eventType = argEventType;
    index = argIndex;
}


ButtonGroup::ButtonGroup(const SRInfo &info, unsigned int offset) :
    _dataPin(info.dataPin), _clockPin(info.clockPin), _latchPin(info.latchPin)
{
    _size = info.size;
    _offset = offset;
    _nbrBtns = 0;
    int index = 0;
    for(auto i = info.pins.begin(); i != info.pins.end(); i++){
        if(*i != -1){
            _mapping[*i] = index;
            _nbrBtns = std::max((int)_nbrBtns, (*i) + 1);
        }
        ++index;
    }
    _previous.resize(_size, false);
    _threadIndex = Threader::startThread(this, &ButtonGroup::_start);
}

ButtonGroup::~ButtonGroup(){
    _quitPipe.send(QUIT);
    Threader::joinThread(_threadIndex, 1000000);
}

unsigned char ButtonGroup::getNbrButtons() const {
    return _nbrBtns;
}

int ButtonGroup::getEventFd() const {
    return _eventPipe.getReadFd();
}

ButtonGroup::ButtonEvent ButtonGroup::getEvent() {
    return _eventPipe.read();
}

void ButtonGroup::_start(){
    bool exit = false;
    while(!exit) {
        fd_set rfds;
        struct timeval tv;
        int retval;

        FD_ZERO(&rfds);
        FD_SET(_quitPipe.getReadFd(), &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 1000;

        retval = select(_quitPipe.getReadFd()+1, &rfds, NULL, NULL, &tv);
        if(retval == -1) {
            log(LOG_ERR, "select() failed");
            exit = true;
        }
        else if (!retval) {  // timeout
            readButtons();
        }
        else{
            unsigned char quitRead = _quitPipe.read();
            if(QUIT == quitRead) {
                exit = true;
            }
            else {
                throw Error::system("this shuld not happened");
            }
        }
    }
}

void ButtonGroup::readButtons() {
    _latchPin.write(Gpio::High);

    std::vector<bool> results;
    results.resize(_size, false);

    for(int i=0; i < _size; i++) {
        results[_mapping[_size - i - 1]] = _dataPin.read() == Gpio::High;

        _clockPin.write(Gpio::High);
        SystemUtils::delay(1);
        _clockPin.write(Gpio::Low);
        SystemUtils::delay(1);
    }
    _latchPin.write(Gpio::Low);

    for(int i = 0; i < _size; i++){
        if(results[i] != _previous[i]) {
            _eventPipe.send(ButtonEvent(results[i]? press:release, _mapping[i]+_offset));
            _previous[i] = results[i];
        }
    }

}
