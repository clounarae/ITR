#ifndef td3_PeriodicTimer_h_INCLUDED
#define td3_PeriodicTimer_h_INCLUDED

#include "Timer.h"


class PeriodicTimer : public Timer
{
public:
    PeriodicTimer(void);
    virtual ~PeriodicTimer();
    PeriodicTimer(const PeriodicTimer & e) = delete;
    PeriodicTimer & operator=(const PeriodicTimer & e) = delete;

    void start(double duration);

    virtual void callback(void) = 0;
};


#endif
