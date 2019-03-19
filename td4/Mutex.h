#ifndef __TD4_MUTEX_H
#define __TD4_MUTEX_H

#include "PosixThread.h"

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
        void run(void);

    private:
        static void * call_run(void * v_thread):

}

#endif  //__TD4_MUTEX_H
