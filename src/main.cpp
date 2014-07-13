#include "chapi.h"
#include "log.h"

int main() {
    initLog(false);
    try{
        Chapi chapi;
        chapi.exec();
    }
    catch(char const*err) {
        log(LOG_ERR, "%s", err);
        return 1;
    }
    catch(...){
        return 1;
    }
    return 0;
}
