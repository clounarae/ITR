#ifndef __TD2_EX_A_H
#define __TD2_EX_A_H

#include <pthread.h>

struct ThreadParameters {
    unsigned int nLoops;
    double * pCounter;
    pthread_mutex_t mutex;
    bool protec;
};

void incr(unsigned int nLoops, double* pCounter);
void * call_incr(void * ptr);


#endif  //__TD2_EX_A_H
