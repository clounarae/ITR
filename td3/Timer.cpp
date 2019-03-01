#include "Timer.h"

#include "../td1/timer.h"


Timer::Timer(void)
{
    struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = Timer::call_callback;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = (void*)this;

	timer_create(CLOCK_REALTIME, &sev, &m_tid);
}

Timer::~Timer()
{
    timer_delete(m_tid);
}


void Timer::start(double duration)
{
    itimerspec its;
    timespec ts;

    ts = timespec_from_ms(duration);
	its.it_value.tv_sec = ts.tv_sec;
	its.it_value.tv_nsec = ts.tv_nsec;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;
	timer_settime(m_tid, 0, &its, NULL);
}


void Timer::stop(void)
{
    itimerspec its;
	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;
	timer_settime(m_tid, 0, &its, NULL);
}


void Timer::call_callback(int sig, siginfo_t * si, void * user)
{
    Timer * timerPtr = (Timer *)si->si_value.sival_ptr;

    timerPtr->callback();
}
