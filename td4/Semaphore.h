#ifndef __TD4_SEMAPHORE_H
#define __TD4_SEMAPHORE_H

#include <Mutex.h>


class Semaphore
{
    public:
        Semaphore(unsigned initCount = 0, unsigned maxCount = UINT_MAX);
        ~Semaphore();

        void give(void);
        void take(void);
        bool take(double timeout_ms);

    private:
        Mutex       m_mutex;
        unsigned    m_counter;
        unsigned    m_maxCount;

};

#endif  //__TD4_SEMAPHORE_H
