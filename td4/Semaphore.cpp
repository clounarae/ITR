#include "Semaphore.h"


Semaphore::Semaphore(unsigned initCount = 0, unsigned maxCount = UINT_MAX)
{
    m_counter = initCount;
    m_maxCount = m_maxCount;
}

Semaphore::~Semaphore()
{
    //Nuthin?
}


void Semaphore::give(void)
{
    Mutex::Lock lock(m_mutex);
    if(m_counter < m_maxCount)
    {
        m_counter++;
        m_mutex.notify();
    }
}

void Semaphore::take(void)
{
    Mutex::Lock lock(m_mutex);
    while(!m_counter)
        lock.wait();
    m_counter--;
}

bool Semaphore::take(double timeout_ms)
{
    try {
        Mutex::Lock lock(m_mutex, timeout_ms);
    }
    catch(Mutex::Lock::TimeoutException) {
        return false;
    }

    while(!m_counter)
        lock.wait();
    m_counter--;

    return true;
}
