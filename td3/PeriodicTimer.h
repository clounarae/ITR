#ifndef __TD3_PERIODIC_TIMER_H
#define __TD3_PERIODIC_TIMER_H

#include "Timer.h"


class PeriodicTimer : public Timer
{
    public:
        PeriodicTimer(void);
        ~PeriodicTimer();
        PeriodicTimer(const PeriodicTimer & e) = delete;
        PeriodicTimer & operator=(const PeriodicTimer & e) = delete;

        void start(double duration);

        virtual void callback(void) = 0;

};


#endif  //__TD3_PERIODIC_TIMER_H
