#include <iostream>
#include <string>
#include <cstdlib>
#include <pthread.h>

#include "../td1/timer.h"
#include "ex_bandc.h"


int main(int argc, char * argv[])
{
    ThreadParameters params;
    double counter = 0.;
    const unsigned int nThreads = std::stoi(argv[2]);
    pthread_t * threads = nullptr;
    struct sched_param schedParam; 
    struct timespec timeStart, timeStop;
    std::string strLastArg;
    schedParam.sched_priority = sched_get_priority_max(SCHED_OTHER );


    threads = new pthread_t[nThreads];

    params.pCounter = &counter;
    params.nLoops = std::stoi(argv[1]);
    pthread_mutex_init(&params.mutex, nullptr);
    params.protec = false;
    
    if(argc >= 4)
    {
        if(std::string(argv[3]) == "-protected")
            params.protec = true;
        else if(std::string(argv[3]) == "-SCHED_RR")
        {
            schedParam.sched_priority = sched_get_priority_max(SCHED_RR);
            pthread_setschedparam(pthread_self(), SCHED_RR, &schedParam);
        }
        else if(std::string(argv[3]) == "-SCHED_FIFO")
        {
            schedParam.sched_priority = sched_get_priority_max(SCHED_FIFO);
            pthread_setschedparam(pthread_self(), SCHED_FIFO, &schedParam);
        }
        else
            std::cout << "Unexpected argument : " << argv[3] << ", ignoring.\n";
    }
    
    

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

    std::cout << "All threads stopped, result : " << counter << ".\n";
    std::cout << "Time (ms) : " << timespec_to_ms(timeStop - timeStart) << ".\n";

    pthread_mutex_destroy(&params.mutex); 

    delete[] threads;

    return 0;
}
