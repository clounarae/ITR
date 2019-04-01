#include "ex_a.h"


void incrA(unsigned int nLoops, double* pCounter)
{
	while(nLoops--)
		*pCounter += 1.;
}


void * call_incrA(void * ptr)
{
	ThreadParametersA * structPtr = (ThreadParametersA*)ptr;

	incrA(structPtr->nLoops, structPtr->pCounter);

	return ptr;
}
