#include <signal.h>
#include <sys/signalfd.h>
#include <string.h>

#include "const.h"
#include "chapi.h"
#include "log.h"
#include "led.h"
#include "error.h"

void loop(){
    while(true) {
        sleep(1);
    }
}

int main() {
    int sigError = -1;

    //Ready to catch signals
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        sigError = errno;
    }

    initLog(false);

    Led redLed(24);
    redLed.on();

    try{
        if(sigError != -1){
            throw Error(Error::systemError, std::string("Unable to listen to signals: ") + strerror(sigError));
        }

        Chapi chapi(mask, redLed);
        chapi.exec();
    }
    catch(Error &e){
        log(LOG_ERR, "%s", e.what());
        redLed.blinkNumber((e.getKind() == Error::configError) ? 2 : ((e.getKind() == Error::systemError) ? 3 : 4));
        loop();
    }
    catch(std::exception &e){
        log(LOG_ERR, "%s", e.what());
        redLed.blinkNumber(5);
        loop();
    }
    catch(char const*err) {
        log(LOG_ERR, "%s", err);
        redLed.blinkNumber(5);
        loop();
    }
    catch(...){
        log(LOG_ERR, "unknown error");
        redLed.blinkNumber(5);
        loop();
    }
    redLed.off();
    return 0;
}
