#include <iostream>
#include <cstring>

#include "chapi.h"
#include "log.h"

int main() {
    try{
        initLog(false);

        Chapi chapi;
        chapi.exec();
        std::cout << "Ciao" << std::endl;
    }
    catch(...){
        return 1;
    }
    return 0;
}
