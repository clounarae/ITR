#ifndef td3_Looper_h_INCLUDED
#define td3_Looper_h_INCLUDED

#include <cfloat>

#include "PeriodicTimer.h"


class Looper
{
public:
    Looper(void);
    ~Looper();
    Looper(const Looper & e) = delete;
    Looper & operator=(const Looper & e) = delete;

    void runLoop(double nLoops = DBL_MAX);

    double getSample(void);

    double stopLoop(void);

private:
    volatile bool    m_doStop;
    volatile double  m_iLoop;
};


#endif
