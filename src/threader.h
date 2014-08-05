#ifndef THREADER_H
#define THREADER_H

#include <mutex>
#include <pthread.h>
#include <map>
#include <functional>

#include <iostream>

#include "pipe.h"
#include "error.h"

class Threader {
public:
    struct ThreadContext {
        std::function<void()> lambda;
        int index;
        pthread_t thread;
    };

    template<typename T>
    static unsigned int startThread(T* owner, void (T::*method)(void));

    static int getErrorFd();
    static void throwError();
    static void joinThread(unsigned int index, double timeout = -1);

    ~Threader();

private:
    enum ErrorType {
        noneError,
        appError,
        stdError,
        unknownError
    };

    static Threader& get();
    static void* _startStatic(void*);
    void _throwError();
    void _joinThread(unsigned int index, double timeout);

    Threader();
    Threader(Threader const&); //No Implementation
    void operator=(Threader const&); //No Implementation

    void _start(ThreadContext*);

    std::mutex _mutex;
    Pipe<unsigned char> _pipe;

    unsigned int _nextIndex;
    std::map<unsigned int, ThreadContext*> _contexts;

    ErrorType _errorType;
    Error _appError;
    std::exception _stdError;
    ThreadContext* _errorContext;
};


template<typename T>
unsigned int Threader::startThread(T* owner, void (T::*method)(void)) {
    const std::lock_guard<std::mutex> lock(get()._mutex);
    ThreadContext *context = new ThreadContext();
    context->lambda = [=]() -> void {
         (owner->*method)();
    };
    context->index = get()._nextIndex;

    pthread_create(&(context->thread), NULL, _startStatic, (void*) context);

    get()._contexts[get()._nextIndex] = context;
    return get()._nextIndex++;
}

#endif // THREADER_H
