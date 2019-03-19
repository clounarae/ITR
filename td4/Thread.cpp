#include "Thread.h"
#include "../td1/timer.h"
#include <unistd.h>

Thread::Thread()
{

}

Thread::~Thread()
{

}

void Thread::start(void)
{
    PosixThread::start(&call_run,(void *) this);
}

double Thread::startTime_ms()
{
    return(m_chrono.startTime());
}

double Thread::stopTime_ms()
{
    return(m_chrono.stopTime());
}

double Thread::execTime_ms()
{
    return(stopTime_ms()-startTime_ms());
}

void Thread::sleep_ms(double delay_ms)
{
    sleep(delay_ms);
}


void * Thread::call_run(void * v_thread)
{
    Thread * thr = (Thread *) v_thread;
    thr->run();
    return nullptr;
}