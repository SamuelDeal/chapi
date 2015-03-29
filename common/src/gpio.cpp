#include "gpio.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>



static const char *export_filepath = "/sys/class/gpio/export";
static void export_gpio(unsigned char pin) {
    std::ofstream sysfile(export_filepath);
    if (!sysfile.is_open()){
        throw "TODO: OPERATION FAILED: Unable to export GPIO ";
    }
    sysfile << pin;
}

static const char *unexport_filepath = "/sys/class/gpio/unexport";
static void unexport_gpio(unsigned char pin) {
    std::ofstream sysfile(unexport_filepath);
    if (!sysfile.is_open()){
        throw "TODO: OPERATION FAILED: Unable to export GPIO ";
    }
    sysfile << pin;
}

Gpio::Core::Core(unsigned char pin, Direction dir) {
    _pin = pin;
    export_gpio(_pin);
    set_gpio_dir(_pin, dir);
}

Gpio::Core::~Core() throw() {
    try{
        unexport_gpio(_pin);
    }
    catch(...){
    }
}

void Gpio::Core::set_gpio_dir(unsigned char pin, Direction dir) {
    std::string filepath = "/sys/class/gpio/gpio" + std::to_string(pin) + "/direction";
    std::ofstream sysfile(filepath.c_str());
    if (!sysfile.is_open()){
        throw "TODO: OPERATION FAILED: Unable to set direction of GPIO ";
    }
    sysfile << ((dir == Gpio::Core::In) ? "in" : "out");
}

Gpio::In::In(unsigned char pin) : Gpio::Core(pin, Direction::In){
    _filepath = "/sys/class/gpio/gpio" + std::to_string(_pin) + "/value";
}

Gpio::Value Gpio::In::read() {
    std::ifstream sysfile(_filepath.c_str());
    if (!sysfile.is_open()){
        throw "TODO: OPERATION FAILED: Unable to set direction of GPIO ";
    }
    std::string value;
    sysfile >> value;
    return ((value == "0") ? Gpio::Low : Gpio::High);
}

Gpio::Out::Out(unsigned char pin) : Gpio::Core(pin, Direction::Out) {
    _filepath = "/sys/class/gpio/gpio" + std::to_string(_pin) + "/value";
}

void Gpio::Out::write(Gpio::Value value) {
    std::ofstream sysfile(_filepath.c_str());
    if (!sysfile.is_open()){
        throw "TODO: OPERATION FAILED: Unable to set direction of GPIO ";
    }
    sysfile << ((value == Gpio::High) ? "1" : "0");
}
