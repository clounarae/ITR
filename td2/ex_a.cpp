#include "ex_a.h"


void incr(unsigned int nLoops, double* pCounter)
{
    while(nLoops--)
        *pCounter += 1.;
}

void incrProtected(unsigned int nLoops, double* pCounter, pthread_mutex_t * mutexPtr)
{
    while(nLoops--)
    {
        pthread_mutex_lock(mutexPtr);
        *pCounter += 1.;
        pthread_mutex_unlock(mutexPtr);
    }
}


void * call_incr(void * ptr)
{
    ThreadParameters * structPtr = (ThreadParameters*)ptr;

    if(structPtr->protec)
        incrProtected(structPtr->nLoops, structPtr->pCounter, &structPtr->mutex);
    else
        incr(structPtr->nLoops, structPtr->pCounter);

    return ptr;
}
