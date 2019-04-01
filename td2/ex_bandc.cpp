#include "ex_bandc.h"


void incrBC(unsigned int nLoops, double* pCounter)
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


void * call_incrBC(void * ptr)
{
	ThreadParametersBC * structPtr = (ThreadParametersBC*)ptr;

	if(structPtr->protec)
		incrProtected(structPtr->nLoops, structPtr->pCounter, &structPtr->mutex);
	else
		incrBC(structPtr->nLoops, structPtr->pCounter);

	return ptr;
}
