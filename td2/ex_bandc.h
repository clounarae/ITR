#ifndef td2_ex_bandc_h_INCLUDED
#define td2_ex_bandc_h_INCLUDED

#include <pthread.h>

struct ThreadParameters
{
    unsigned int nLoops;
    double * pCounter;
    pthread_mutex_t mutex;
    bool protec;
};

void incr(unsigned int nLoops, double* pCounter);
void * call_incr(void * ptr);


#endif
