#include "etime.h"

#include <cstddef>
#include <iostream>

const ETime& ETime::oneSecond() {
    static ETime constant(1, 0);

    return constant;
}


ETime::ETime() {
    gettimeofday(&_data, NULL);
    std::cout<< "created now: " << _data.tv_sec << "," << _data.tv_usec << std::endl;
}

ETime::ETime(long sec, long usec){
    _data.tv_sec = sec;
    _data.tv_usec = usec;
    std::cout<< "created fixed: " << _data.tv_sec << "," << _data.tv_usec << std::endl;
}

ETime ETime::operator-(const ETime &otherTime) const {
    long long int diff = (_data.tv_usec + 1000000  * _data.tv_sec) - (otherTime._data.tv_usec + 1000000 * otherTime._data.tv_sec);
    std::cout<< "creating minus" << std::endl;
    return ETime(diff / 1000000, diff % 1000000);
}

bool ETime::operator>(const ETime &otherTime) const{
    if(_data.tv_sec > otherTime._data.tv_sec){
        std::cout<< "comp " << _data.tv_sec << ">" << otherTime._data.tv_sec << "=> true"  << std::endl;
        return true;
    }
    if(_data.tv_sec < otherTime._data.tv_sec){
        return false;
        std::cout<< "comp " << _data.tv_sec << "<" << otherTime._data.tv_sec << "=> false"  << std::endl;
    }
    std::cout<< "comp " << _data.tv_usec << ">" << otherTime._data.tv_usec << "=> " << ((_data.tv_usec > otherTime._data.tv_usec) ? "true" : "false") << std::endl;
    return _data.tv_usec > otherTime._data.tv_usec;
}
