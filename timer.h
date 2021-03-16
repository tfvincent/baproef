#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <chrono>
#include "vectorUtil.h"

class Timer {
public:
    Timer(const char* name);
    ~Timer();

    void Stop();

private:
    const char* m_Name;
    chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;

};


#endif //BAPROEF_TIMER_H
