#include "buttongroup.h"

#include <signal.h>

#include "log.h"
#include "error.h"
#include "systemutils.h"


unsigned char ButtonGroup::QUIT;

ButtonGroup::ButtonEvent::ButtonEvent(EventType argEventType, int argIndex){
    eventType = argEventType;
    index = argIndex;
}


ButtonGroup::ButtonGroup(const SRInfo &info, unsigned int offset) :
    _dataPin(info.dataPin), _clockPin(info.clockPin), _latchPin(info.latchPin)
{
    _size = info.size;
    _offset = offset;
    _nbrBtns = 0;
    int index = 0;
    for(auto i = info.pins.begin(); i != info.pins.end(); i++){
        if(*i != -1){
            _mapping[*i] = index;
            _nbrBtns = std::max((int)_nbrBtns, (*i) + 1);
        }
        ++index;
    }

    pthread_create(&_thread, NULL, ButtonGroup::_startThread, (void*)this);
}

ButtonGroup::~ButtonGroup(){
    _pipe.send(ButtonEvent(quit));

    //wait thread for 3sec
    timespec ts;
    if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        log(LOG_ERR, "clock gettime failed");
    }
    else{ ts.tv_sec += 3;
        int joined = pthread_timedjoin_np(_thread, NULL, &ts);
        if(joined != 0) {
            log(LOG_ERR, "unable to join the thread");
        }
    }
}

unsigned char ButtonGroup::getNbrButtons() const {
    return _nbrBtns;
}

Pipe<ButtonGroup::ButtonEvent> ButtonGroup::getPipe() const {
    return _pipe;
}

void* ButtonGroup::_startThread(void *btnGroup){
    signal(SIGCHLD,SIG_DFL); // A child process dies
    signal(SIGTSTP,SIG_IGN); // Various TTY signals
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGHUP, SIG_IGN); // Ignore hangup signal
    signal(SIGINT,SIG_IGN); // ignore SIGTERM
    signal(SIGQUIT,SIG_IGN); // ignore SIGTERM
    signal(SIGTERM,SIG_IGN); // ignore SIGTERM
    signal(SIGUSR1,SIG_IGN);
    signal(SIGUSR2,SIG_IGN);
    int oldstate;
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);

    ((ButtonGroup*)btnGroup)->_start();
    return NULL;
}

void ButtonGroup::_start(){
    bool exit = false;
    while(!exit) {
        fd_set rfds;
        struct timeval tv;
        int retval;

        FD_ZERO(&rfds);
        FD_SET(_quitPipe.getReadFd(), &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 1000;

        retval = select(_quitPipe.getReadFd()+1, &rfds, NULL, NULL, &tv);
        if(retval == -1) {
            log(LOG_ERR, "select() failed");
            exit = true;
        }
        else if (!retval) {  // timeout
            readButtons();
        }
        else{
            unsigned char quitRead = _quitPipe.read();
            if(QUIT == quitRead) {
                exit = true;
            }
            else {
                throw Error::system("this shuld not happened");
            }
        }
    }
}

void ButtonGroup::readButtons() {
    _latchPin.write(Gpio::High);
    for(unsigned char i=0; i < _size; i++) {
          //unsigned char computedIndex = ((i%8) < 4) ? i : (8 - (i%4) - 1);
          //result[computedIndex] = integrate(i, digitalRead(DATA_PIN));

        std::cout << (_dataPin.read() == Gpio::High) ? "1" : "0";


        _clockPin.write(Gpio::High);
        SystemUtils::delay(1);
        _clockPin.write(Gpio::Low);
        SystemUtils::delay(1);
    }
    _latchPin.write(Gpio::Low);
    std::cout << std::endl;
}
