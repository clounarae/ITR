#ifndef __TD4_THREAD_H
#define __TD4_THREAD_H

#include "PosixThread.h"
#include "../td3/Chrono.h"

class Thread : public PosixThread
{
    public:
        Thread();
        ~Thread();

        void start(void);

        double startTime_ms(void);
        double stopTime_ms(void);
        double execTime_ms(void);

        static void sleep_ms(double delay_ms);

    protected:
        virtual void run(void)=0;

    private:
        static void * call_run(void * v_thread);
        Chrono m_chrono;

};

#endif  //__TD4_THREAD_H
