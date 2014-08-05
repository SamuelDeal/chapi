#include "gpio.h"

#ifndef NOGPIO
#include <wiringPi.h>
#endif

Gpio::In::In(unsigned char pin) {
    _pin = pin;
#ifndef NOGPIO
    wiringPiSetupPhys();
    pinMode((int) pin, INPUT);
#endif
}

Gpio::Value Gpio::In::read() {
#ifdef NOGPIO
    return Gpio::Low;
#else
    return ((digitalRead((int)_pin) == HIGH) ? Gpio::High : Gpio::Low);
#endif
}

Gpio::Out::Out(unsigned char pin) {
    _pin = pin;
#ifndef NOGPIO
    wiringPiSetupPhys();
    pinMode((int) pin, OUTPUT);
#endif
}

void Gpio::Out::write(Gpio::Value value) {
#ifndef NOGPIO
    digitalWrite((int)_pin, (value == Gpio::High)? HIGH: LOW);
#endif
}
