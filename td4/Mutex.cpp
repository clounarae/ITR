#include "Mutex.h"

#include "../td1/timer.h"

Mutex::Mutex(void)
{
    m_posixId = PTHREAD_MUTEX_INITIALIZER;
    m_posixCondId = PTHREAD_COND_INITIALIZER;

    pthread_mutex_init(&m_posixId, nullptr);
    pthread_cond_init(&m_posixCondId, nullptr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_posixId);
    pthread_cond_destroy(&m_posixCondId);
}


void Mutex::lock(void)
{
    pthread_mutex_lock(&m_posixId);
}

bool Mutex::lock(double timeout_ms)
{
    struct timespec ts = timespec_from_ms(timeout_ms);
    return !pthread_mutex_timedlock(&m_posixId, ts);
}


bool Mutex::trylock(void)
{
    return !pthread_mutex_trylock(&m_posixId);
}

void Mutex::unlock(void)
{
    pthread_mutex_unlock(&m_posixId);
}



Mutex::Lock::Lock(Mutex & m) : m_mutex(m)
{
    m_mutex.lock();
}

Mutex::Lock::Lock(Mutex & m, double timeout_ms) : m_mutex(m)
{
    bool rslt = false;

    if(timeout_ms <= 0.)
        rslt = m_mutex.trylock();
    else
        rslt = m_mutex.lock(timeout_ms);

    if(!rslt)
        throw Exception();
}

Mutex::Lock::~Lock()
{
    m_mutex.unlock();
}


void Mutex::Lock::wait(void)
{
    pthread_cond_wait(&m_posixCondId, &m_posixId);
}

bool Mutex::Lock::wait(double timeout_ms)
{
    struct timespec ts = timespec_from_ms(timeout_ms);
    pthread_cond_timedwait(&m_posixCondId, &m_posixId, ts);
}

void Mutex::Lock::notify(void)
{
    pthread_cond_signal(&m_posixCondId);
}

void Mutex::Lock::notifyAll(void)
{
    pthread_cond_broadcast(&m_posixCondId);
}


Mutex::TryLock::TryLock(Mutex & m) : Lock(-1.)
{
    //Nuthin
}

Mutex::TryLock::~TryLock()
{
    //Nuthin
}

