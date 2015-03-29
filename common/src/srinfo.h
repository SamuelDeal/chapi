#ifndef SRINFO_H
#define SRINFO_H

#include <vector>

struct SRInfo{
    int latchPin = -1;
    int clockPin = -1;
    int dataPin = -1;
    int size = -1;

    std::vector<int> pins;
};

#endif // SRINFO_H
