#include "ex_b.h"

#include <cstdlib>

void incr(unsigned int nLoops, double* pCounter)
{
    while(nLoops--)
        *pCounter += 1.;
}

void exB(int argc, char* argv[])
{
    double counter = 0.;

    incr(std::atoi(argv[1]), &counter);
}
