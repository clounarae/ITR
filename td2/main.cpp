#include <iostream>
#include <cstdlib>
#include <pthread.h>

#include "../td1/timer.h"
#include "ex_a.h"


int main(int argc, char * argv[])
{
    ThreadParameters params;
    double counter = 0.;
    const unsigned int nThreads = std::stoi(argv[2]);
    pthread_t * threads = nullptr;
    
    threads = new pthread_t[nThreads];
    
    params.pCounter = &counter;
    params.nLoops = std::stoi(argv[1]);
    
    std::cout << "Starting " << nThreads << " threads ...\n";
    for(int i = 0 ; i < nThreads ; i++)
        pthread_create(threads + i, 0, call_incr, (void*) &params);
    std::cout << "All threads launched.\n";
    
    for(int i = 0 ; i < nThreads ; i++)
        pthread_join(threads[i], 0);

    delete[] threads;
    
    return 0;
}
