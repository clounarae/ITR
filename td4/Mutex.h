#ifndef __TD4_MUTEX_H
#define __TD4_MUTEX_H

#include <pthread.h>
#include <exception>


class Mutex
{
public:
    Mutex(void);
    ~Mutex();

private:
    void lock(void);
    bool lock(double timeout_ms);

    bool trylock(void);
    void unlock(void);

private:
    pthread_mutex_t m_posixId;
    pthread_cond_t  m_posixCondId;


public:
    class Lock
    {
    public:
        Lock(Mutex & m);
        Lock(Mutex & m, double timeout_ms) throw TimeoutException;
        ~Lock();
        
        void wait(void);
        bool wait(double timeout_ms);
        void notify(void);
        void notifyAll(void);

    private:
        Mutex & m_mutex;
    
    public:
        class TimeoutException : public std::exception {
        public:
            TimeoutException(){} noexcept;
            ~TimeoutException(){};
            virtual const char* what() {
                return "Mutex lock : timeout !";
            } const noexcept;
        };
    };
    
    class TryLock : public Lock
    {
    public:
        TryLock(Mutex & m) throw TimeoutException;
        ~TryLock();
    };
};

#endif  //__TD4_MUTEX_H
