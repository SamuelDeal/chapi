#include "ledgroup.h"

#include "systemutils.h"

LedGroup::LedGroup(const SRInfo &info):
    _dataPin(info.dataPin), _clockPin(info.clockPin), _latchPin(info.latchPin)
{
    _values = (bool*) malloc(info.size*sizeof(bool*));
    for(unsigned char i = 0; i < info.size; i++){
        _values[i] = false;
    }
    _nbrBtns = 0;

    int index = 0;
    for(auto i = info.pins.begin(); i != info.pins.end(); i++){
        if(*i != -1){
            _mapping[*i] = index;
            _nbrBtns = std::max((int)_nbrBtns, (*i) + 1);
        }
        ++index;
    }
    _size = info.size;
}

LedGroup::~LedGroup() {
    free(_values);
}

void LedGroup::clear(bool buffered) {
    for(unsigned char i = 0; i < _nbrBtns; i++){
        _values[i] = false;
    }
    if(!buffered){
        write();
    }
}

void LedGroup::on(unsigned char index, bool buffered) {
    if((index >= _nbrBtns) || (_mapping.find(index) == _mapping.end())) {
        return;
    }
    _values[_mapping[index]] = true;
    if(!buffered){
        write();
    }
}

void LedGroup::off(unsigned char index, bool buffered) {
    if((index >= _nbrBtns) || (_mapping.find(index) == _mapping.end())) {
        return;
    }
    _values[_mapping[index]] = false;
    if(!buffered){
        write();
    }
}

void LedGroup::write() {
    _latchPin.write(Gpio::Low);
    SystemUtils::delay(1);
    for(unsigned char i=_size-1; i >= 0; --i) {
        _clockPin.write(Gpio::Low);
        _dataPin.write(_values[i] ? Gpio::High : Gpio::Low);
        SystemUtils::delay(1);
        _clockPin.write(Gpio::High);
        SystemUtils::delay(1);
    }
    _latchPin.write(Gpio::High);
    SystemUtils::delay(1);
}

unsigned char LedGroup::getNbrButtons() const {
    return _nbrBtns;
}
