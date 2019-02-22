#include "ex_c.h"
#include "timer.h"
#include <cstdlib>
#include <climits>
#include <iostream>

unsigned incr(unsigned int nLoops, double* pCounter, volatile bool* pStop)
{
    unsigned int counter =0;

    while(!(*pStop) && counter <nLoops)
    {
        *pCounter += 1.;
        counter ++;
    }
        
    return counter;
}

void toggleStopValue(int sig, siginfo_t* si, void*)
{
	bool* ptr = (bool*) si->si_value.sival_ptr;
	*ptr =true;
}

void exC()
{
    double counter = 0.;
    volatile bool stop = false; 
    struct timespec debut, fin, duree ;
    struct sigaction sa ;
	sa.sa_flags=SA_SIGINFO ;
	sa.sa_sigaction = toggleStopValue;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);
	struct sigevent sev ;
	sev.sigev_notify = SIGEV_SIGNAL ;
	sev.sigev_signo = SIGRTMIN ;
	sev.sigev_value.sival_ptr = &stop ;
	timer_t tid;
	timer_create(CLOCK_REALTIME, &sev, &tid);
	itimerspec its;
	its.it_value.tv_sec = 1; 
	its.it_value.tv_nsec = 0; 
	its.it_interval.tv_sec = 0; 
	its.it_interval.tv_nsec = 0; 
	timer_settime(tid,0,&its,NULL);
    clock_gettime(CLOCK_REALTIME, &debut);
    unsigned int loops = incr(UINT_MAX, &counter, &stop);
    clock_gettime(CLOCK_REALTIME, &fin);
    timer_delete(tid);
    duree = fin - debut;
    std::cout << "Durée d'execution: " << timespec_to_ms(duree) << ".\n";
    std::cout << "Nombre de boucles: " << loops << ".\n";

}
