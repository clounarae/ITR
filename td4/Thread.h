#ifndef td4_Thread_h_INCLUDED
#define td4_Thread_h_INCLUDED

#include "PosixThread.h"
#include "../td3/Chrono.h"

class Thread : public PosixThread
{
public:
    Thread(void);
    virtual ~Thread();

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


#endif
