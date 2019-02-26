#include <iostream>
#include <string>
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
    std::string strLastArg;


    threads = new pthread_t[nThreads];

    params.pCounter = &counter;
    params.nLoops = std::stoi(argv[1]);
    pthread_mutex_init(&params.mutex, nullptr);
    params.protec = argc >= 4 && std::string(argv[3]) == "-protected";

	timeStart = timespec_now();
    std::cout << "Starting " << nThreads << " threads ...\n";
    if(params.protec)
        std::cout << "(protected mode)\n";

    for(int i = 0 ; i < nThreads ; i++)
        pthread_create(threads + i, 0, call_incr, (void*) &params);
    std::cout << "All threads launched.\n";

    for(int i = 0 ; i < nThreads ; i++)
        pthread_join(threads[i], 0);
	timeStop = timespec_now();

    std::cout << "Time (ms) : " << timespec_to_ms(timeStop - timeStart) << ".\n";

    pthread_mutex_destroy(&params.mutex); 

    delete[] threads;

    return 0;
}
