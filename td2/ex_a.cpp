
#include "ex_a.h"


void incr(unsigned int nLoops, double* pCounter)
{
    while(nLoops--)
        *pCounter += 1.;
}


void * call_incr(void * ptr)
{
    ThreadParameters * structPtr = (ThreadParameters*)ptr;

    incr(structPtr->nLoops, structPtr->pCounter);

    return ptr;
}
 