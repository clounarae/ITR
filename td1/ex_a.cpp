
#include <iostream>
#include <ctime>
#include <csignal>
#include "ex_a.h"

void myHandler(int sig, siginfo_t* si, void*)
{
	int* ptr = (int*) si->si_value.sival_ptr;
	std::cout << "Compteur :" << *(ptr) << ".\n";
	*(ptr)++ ;
}

void exA(void)
{
	struct sigaction sa ;
	sa.sa_flags=SA_SIGINFO ;
	sa.sa_sigaction = myHandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);
	struct sigevent sev ;
	sev.sigev_notify = SIGEV_SIGNAL ;
	sev.sigev_signo = SIGRTMIN ;
	int compteur = 0;
	sev.sigev_value.sival_ptr = &compteur ;
	timer_t tid;
	timer_create(CLOCK_REALTIME, &sev, &tid);
	itimerspec its;
	its.it_value.tv_sec = 0; 
	its.it_value.tv_nsec = 500000000; 
	its.it_interval.tv_sec = 0; 
	its.it_interval.tv_nsec = 500000000; 
	
	timer_settime(tid,0,&its,NULL);
	while(compteur <= 15);
	timer_delete(tid);

}
	




