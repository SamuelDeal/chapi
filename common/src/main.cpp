#include <signal.h>

#include <cstdlib>

#include "chapi.h"
#include "log.h"
#include "led.h"
#include "error.h"

void loop(){
    sigset_t mask;
    sigemptyset(&mask);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        log(LOG_ERR, "unable to remove sgnal masks");
        exit(2);
    }

    while(true) {
        sleep(1);
    }
}

int main() {
    int appFailureCode = 1;
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
            throw Error::system(sigError, "Unable to listen to signals: ");
        }

        Chapi chapi(mask, redLed);
        chapi.exec();
        appFailureCode = 0;
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
    log(LOG_INFO, "chapi ended");
    return appFailureCode;
}
