#ifndef _PIPE_HPP
#define _PIPE_HPP

template<typename T>
class Pipe {
    public:
        Pipe();
        ~Pipe();

        void send(T event) const;
        T read() const;
        int getReadFd() const;

    protected:
        int _fds[2];
};


#include <unistd.h>
#include <fcntl.h>

template<typename T>
Pipe<T>::Pipe() {
    pipe2(_fds, O_NONBLOCK);
}

template<typename T>
Pipe<T>::~Pipe(){
    close(_fds[0]);
    close(_fds[1]);
}

template<typename T>
void Pipe<T>::send(T evt) const {
    write(_fds[1], &evt, sizeof(T));
}

template<typename T>
T Pipe<T>::read() const {
    T evt;
    ::read(_fds[0], &evt, sizeof(T));
    return evt;
}

template<typename T>
int Pipe<T>::getReadFd() const {
    return _fds[0];
}

#endif // _PIPE_HPP

