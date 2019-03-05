#ifndef __TD4_POSIX_THREAD_H
#define __TD4_POSIX_THREAD_H

#include <pthread.h>

class PosixThread 
{
    public:
        PosixThread();
        PosixThread(pthread_t posixId);
        ~PosixThread();
        start(void* (*) (void*) threadFunc, void* threadArg);
        join();
        bool join(double timeout_ms) ;
        bool setScheduling(int schedPolicy, int priority);
        bool getScheduling(int* p_schedPolicy = nullptr, int* p_priority = nullptr);
    private:
        pthread_t posixId;
        pthread_attr_t posixAttr;

}

#endif  //__TD4_POSIX_THREAD_H
