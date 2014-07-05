#include <iostream>
#include <cstring>

#include "chapi.h"
#include "log.h"

int main() {
    initLog(false);

    Chapi chapi;
    chapi.exec();
    std::cout << "Ciao" << std::endl;
}
