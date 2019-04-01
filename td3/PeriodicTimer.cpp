#include "PeriodicTimer.h"

#include "../td1/timer.h"

PeriodicTimer::PeriodicTimer(void)
{
	//Nothing!
}

PeriodicTimer::~PeriodicTimer()
{
	//Nothing!
}


void PeriodicTimer::start(double duration)
{
	itimerspec its;
	timespec ts;

	ts = timespec_from_ms(duration);
	its.it_value.tv_sec = ts.tv_sec;
	its.it_value.tv_nsec = ts.tv_nsec;
	its.it_interval.tv_sec = ts.tv_sec;
	its.it_interval.tv_nsec = ts.tv_nsec;
	timer_settime(m_tid, 0, &its, NULL);
}
