
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
    struct timespec timeStart, timeStop; 

    threads = new pthread_t[nThreads];

    params.pCounter = &counter;
    params.nLoops = std::stoi(argv[1]);

 	timeStart = timespec_now(); 
    std::cout << "Starting " << nThreads << " threads ...\n";
    for(int i = 0 ; i < nThreads ; i++)
        pthread_create(threads + i, 0, call_incr, (void*) &params);
    std::cout << "All threads launched.\n";

    for(int i = 0 ; i < nThreads ; i++)
        pthread_join(threads[i], 0);
    
	timeStop = timespec_now();

    std::cout << "All threads stopped, final value : " << counter << ".\n";
    std::cout << "Time (ms) : " << timespec_to_ms(timeStop - timeStart) << ".\n"; 

    delete[] threads;

    return 0;
} 