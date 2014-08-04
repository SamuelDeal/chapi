#include "gpio.h"

#include <wiringPi.h>


Gpio::In::In(unsigned char pin) {
    wiringPiSetupPhys();
    _pin = pin;
    pinMode((int) pin, INPUT);
}

Gpio::Value Gpio::In::read() {
    return (digitalRead((int)_pin) == HIGH) ? Gpio::High : Gpio::Low;
}

Gpio::Out::Out(unsigned char pin) {
    wiringPiSetupPhys();
    _pin = pin;
    pinMode((int) pin, OUTPUT);
}

void Gpio::Out::write(Gpio::Value value) {
    digitalWrite((int)_pin, (value == Gpio::High)? HIGH: LOW);
}
