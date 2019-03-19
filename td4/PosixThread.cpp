#include "PosixThread.h"
#include "../td1/timer.h"

PosixThread::PosixThread()
{
    pthread_attr_init(&m_posixAttr);
}
        
PosixThread::PosixThread(pthread_t posixId)
{
    int policy=SCHED_OTHER;
    struct sched_param param;
    param.__sched_priority=0;
    if(pthread_getschedparam(posixId, &policy, &param))
    {
        throw PosixThread::Exception();
    }
    else
    {
        m_posixId=posixId;
        pthread_attr_init(&m_posixAttr);
        pthread_attr_setschedpolicy(&m_posixAttr,policy);
        pthread_attr_setschedparam(&m_posixAttr,&param);
    }
    
}
        
PosixThread::~PosixThread()
{
    pthread_attr_destroy(&m_posixAttr);
}
        
void PosixThread::start(void* (*threadFunc) (void*) , void* threadArg)
{
    pthread_create(&m_posixId,&m_posixAttr,threadFunc,threadArg);
}

void PosixThread::join()
{
    pthread_join(m_posixId,NULL);
}

bool PosixThread::join(double timeout_ms)
{
    struct timespec timeout_ts = timespec_from_ms(timeout_ms);
    pthread_timedjoin_np(m_posixId, NULL, &timeout_ts);
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
    struct sched_param param;
    param.__sched_priority=priority;
    pthread_attr_setschedparam(&m_posixAttr,&param);
    pthread_attr_setschedpolicy(&m_posixAttr,schedPolicy);
    if(pthread_setschedparam(m_posixId,schedPolicy,&param))
    {
        return false;
    }
    return true;
}

bool PosixThread::getScheduling(int* p_schedPolicy, int* p_priority)
{
    struct sched_param param;
    pthread_attr_getschedparam(&m_posixAttr,&param);
    *p_priority=param.__sched_priority;
    pthread_attr_getschedpolicy(&m_posixAttr,p_schedPolicy);
    if(pthread_getschedparam(m_posixId,p_schedPolicy,&param))
    {
        return false;
    }
    return true;

}


