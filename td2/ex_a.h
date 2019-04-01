#ifndef td2_ex_a_h_INCLUDED
#define td2_ex_a_h_INCLUDED


struct ThreadParametersA
{
    unsigned int nLoops;
    double * pCounter;
};

void incrA(unsigned int nLoops, double* pCounter);
void * call_incrA(void * ptr);


#endif
