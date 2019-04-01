#ifndef td2_ex_a_h_INCLUDED
#define td2_ex_a_h_INCLUDED


struct ThreadParameters
{
    unsigned int nLoops;
    double * pCounter;
};

void incr(unsigned int nLoops, double* pCounter);
void * call_incr(void * ptr);


#endif
