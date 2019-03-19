#ifndef __TD4_POSIX_THREAD_H
#define __TD4_POSIX_THREAD_H

#include <pthread.h>
#include <exception>

class PosixThread 
{
    public:
        PosixThread();
        PosixThread(pthread_t posixId);
        ~PosixThread();
        void start(void* (*threadFunc) (void*) , void* threadArg);
        void join();
        bool join(double timeout_ms) ;
        bool setScheduling(int schedPolicy, int priority);
        bool getScheduling(int* p_schedPolicy = nullptr, int* p_priority = nullptr);
    private:
        pthread_t m_posixId;
        pthread_attr_t m_posixAttr;
    
    class Exception:public std::exception
    {
        public:
            Exception() noexcept {} ;
            ~Exception(){};
            virtual const char* what() const noexcept
            {
                return "Thread doesn't exist";
            };

    };

};

#endif  //__TD4_POSIX_THREAD_H
