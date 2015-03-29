#include "threader.h"

#include <signal.h>

Threader& Threader::get() {
    static Threader instance;
    return instance;
}

Threader::Threader() : _appError(Error::noneError) {
    _nextIndex = 1;
    _errorContext = NULL;
}

Threader::~Threader() {
    for(auto i = _contexts.begin(); i != _contexts.end(); i++) {
        delete i->second;
    }
    _contexts.clear();
}

int Threader::getErrorFd() {
    return get()._pipe.getReadFd();
}

void Threader::throwError() {
    get()._throwError();
}

void Threader::_throwError() {
    _pipe.read();
    const std::lock_guard<std::mutex> lock(_mutex);
    switch(get()._errorType) {
        case appError:      throw _appError; break;
        case stdError:      throw _stdError; break;
        case unknownError:  throw Error::unknown("unknown error in thread "+std::to_string(_errorContext->index)); break;

        case noneError:
        default:
            break;
    }
}

void* Threader::_startStatic(void *arg) {
    ThreadContext *context = (ThreadContext*) arg;
    Threader::get()._start(context);
    return NULL;
}

void Threader::_start(ThreadContext *context) {
    {
        const std::lock_guard<std::mutex> lock(_mutex);
    }
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

    try{
        context->lambda();
    }
    catch(Error &e){
        const std::lock_guard<std::mutex> lock(_mutex);
        if(_errorType == noneError) {
            _errorType = appError;
            _errorContext = context;
            _appError = e;
            _pipe.send(1);
        }
    }
    catch(std::exception &e){
        const std::lock_guard<std::mutex> lock(_mutex);
        if(_errorType == noneError) {
            _errorType = stdError;
            _errorContext = context;
            _stdError = e;
            _pipe.send(1);
        }
    }
    catch(...){
        const std::lock_guard<std::mutex> lock(_mutex);
        if(_errorType == noneError) {
            _errorType = unknownError;
            _errorContext = context;
            _pipe.send(1);
        }
    }
    {
        const std::lock_guard<std::mutex> lock(_mutex);
        if(_errorContext != context) {
            _contexts.erase(_contexts.find(context->index));
            delete context;
        }
    }
}

void Threader::joinThread(unsigned int index, double timeout) {
    get()._joinThread(index, timeout);
}


void Threader::_joinThread(unsigned int index, double timeout) {
    if(_contexts.find(index) == _contexts.end()){
        return; //no more thread;
    }

    if(timeout <= 0){
        pthread_join(_contexts[index]->thread, NULL);
        return;
    }

    timespec ts;
    if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        throw Error::system("clock gettime failed");
    }
    else{
        ts.tv_sec += timeout + (((long long)(ts.tv_nsec / 1000)) + ((long long)timeout))/1000000;
        ts.tv_nsec = ((((long long)(ts.tv_nsec / 1000)) + ((long long)timeout)) % 1000000) * 1000 + (ts.tv_nsec % 1000);

        int joined = pthread_timedjoin_np(_contexts[index]->thread, NULL, &ts);
        if(joined != 0) {
            throw Error::system("unable to join the thread "+std::to_string(index));
        }
    }
}
