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

int executeFunctionForGivenTime(struct timespec ts, timer_t tid, itimerspec its, volatile bool* stop)
{
    double counter = 0.;
	its.it_value.tv_sec = ts.tv_sec; 
	its.it_value.tv_nsec = ts.tv_nsec; 
	its.it_interval.tv_sec = 0; 
	its.it_interval.tv_nsec = 0; 
	timer_settime(tid,0,&its,NULL);
    std::cout << "Enter incr of " << timespec_to_ms(ts) <<"ms .\n";
    unsigned int loops = incr(UINT_MAX, &counter, stop);
    std::cout <<"Out of incr of " <<timespec_to_ms(ts) << "ms. \n";
    return loops;

}

void calib (double* a, double* b)
{
    double t1, n1, t2, n2;
    struct sigaction sa ;
	sa.sa_flags=SA_SIGINFO ;
	sa.sa_sigaction = toggleStopValue;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);
	struct sigevent sev ; 
    volatile bool stop = false; 
	sev.sigev_notify = SIGEV_SIGNAL ;
	sev.sigev_signo = SIGRTMIN ;
	sev.sigev_value.sival_ptr = (void*) &stop ;
	timer_t tid;
	timer_create(CLOCK_REALTIME, &sev, &tid);
	itimerspec its;
    t1=4000.;
    std::cout << "begin timer of" << t1 << "ms.\n";
    n1=executeFunctionForGivenTime(timespec_from_ms(t1),tid,its,&stop);
    t2=6000;
    std::cout << "begin timer of" << t2 << "ms.\n";
    n2=executeFunctionForGivenTime(timespec_from_ms(t2),tid,its,&stop);
    *a=(n2-n1)/(t2-t1);
    *b=n2-(*a)*t2;
    timer_delete(tid);
}



void exC()
{
    double counter = 0.;
    volatile bool otherStop = false; 

    double a=0;
    double b=0;
    calib(&a,&b);
    struct timespec debut, fin, duree ;

    std::cout << "a = " << a <<" b = " << b << ".\n";

    clock_gettime(CLOCK_REALTIME, &debut);
    incr(22000, &counter, &otherStop);
    clock_gettime(CLOCK_REALTIME, &fin);

    duree=fin-debut;
    std::cout << "duree = " << timespec_to_ms(duree) <<" nombre suppose de boucle  = " << a*timespec_to_ms(duree)+b << ".\n";

}
#include "ex_b.h"