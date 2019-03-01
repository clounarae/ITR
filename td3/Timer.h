#ifndef __TD3_TIMER_H
#define __TD3_TIMER_H

#include <ctime>
#include <csignal>


class Timer
{
    public:
        Timer(void);
        ~Timer();
        Timer(const Timer & e) = delete;
        Timer & operator=(const Timer & e) = delete;

        void start(double duration);

        void stop(void);

        virtual void callback(void) = 0;

        static void call_callback(int sig, siginfo_t * si, void * user);

    protected:
        timer_t m_tid;
};


#endif  //__TD3_TIMER_H
