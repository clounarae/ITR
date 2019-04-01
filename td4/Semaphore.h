#ifndef td4_Semaphore_h_INCLUDED
#define td4_Semaphore_h_INCLUDED

#include "Mutex.h"
#include <climits>


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

#endif
