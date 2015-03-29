#ifndef ETIME_H
#define ETIME_H

#include <sys/time.h>


class ETime {

public:
    static const ETime& oneSecond();

    ETime();

    ETime operator-(const ETime &otherTime) const;
    bool operator>(const ETime &otherTime) const;

protected:
    ETime(long sec, long usec);

    timeval _data;

};

#endif // ETIME_H
