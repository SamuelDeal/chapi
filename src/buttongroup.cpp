#include "buttongroup.h"

ButtonGroup::ButtonGroup()
{
}

/*
#include <wiringPi.h>

#include <unistd.h>
#include <iostream>
#include <bitset>

#define CLOCK_PIN 3
#define DATA_PIN 4
#define LATCH_PIN 2

#define INTEGRATOR 0

bool integrate(unsigned char i, int value) {
    static unsigned char tab[8] = {0,0,0,0,0,0,0,0};
    static bool previous[8] = {false, false, false, false, false, false, false, false};

    if(value == HIGH){
       tab[i] = std::min((unsigned char)(tab[i]+1), (unsigned char)INTEGRATOR);
    }
    else {
       tab[i] = std::max((unsigned char)(tab[i]-1), (unsigned char)0);
    }

    if((previous[i]) && (tab[i] == 0)){
        previous[i] = false;
    }
    else if((!previous[i]) && (tab[i] == INTEGRATOR)){
        previous[i] = true;
    }
    return previous[i];
}


int main(int argc, char** argv) {
    std::cout << "Starting..." << std::endl;
    std::cout << "Type Ctrl-C to quit" << std::endl;
    wiringPiSetup();

    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, INPUT);
    pinMode(LATCH_PIN, OUTPUT);

    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(LATCH_PIN, LOW);

    bool result[8];
    for(unsigned char i = 0; i < 8; i++) {
        result[i] = 0;
    }

    while(1) {
        digitalWrite(LATCH_PIN, HIGH);
        for(unsigned char i=0; i < 8; i++) {
              //unsigned char computedIndex = ((i%8) < 4) ? i : (8 - (i%4) - 1);
              //result[computedIndex] = integrate(i, digitalRead(DATA_PIN));
              result[i] = digitalRead(DATA_PIN);
              digitalWrite(CLOCK_PIN, HIGH);
              delay(10);
              digitalWrite(CLOCK_PIN, LOW);
        }
        digitalWrite(LATCH_PIN, LOW);
        delay(10);
        std::cout << "read: ";
        for(int i = 0; i < 8; i++){
            std::cout << (result[i] ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }

    return 0;
}
*/
