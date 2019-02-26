#ifndef __TD2_EX_A_H
#define __TD2_EX_A_H


struct ThreadParameters {
    unsigned int nLoops;
    double * pCounter;
};

void incr(unsigned int nLoops, double* pCounter);
void * call_incr(void * ptr);


#endif  //__TD2_EX_A_H
