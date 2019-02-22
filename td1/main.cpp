#include "timer.h"
#include <iostream>
#include <ctime>
#include <csignal>

void myHandler(int sig, siginfo_t* si, void*)
{
	std::cout << "Compteur :" << *(si->si_value.sival_ptr) << ".\n";
	*(si->si_value.sival_ptr) ;
}


int main(int argc, char * argv[])
{
	struct timespec ts ;//exo e
	double time_ms = 0.;
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
	while(compteur <15);
	timer_delete(tid);
	ts=timespec_now();
	std::cout << "timespec : " << ts.tv_sec << ", " << ts.tv_nsec << ".\n";
	time_ms=timespec_to_ms(ts);
	std::cout << "timemilli : " << time_ms << ".\n";
	ts=timespec_from_ms(time_ms);
	std::cout << "timespec : " << ts.tv_sec << ", " << ts.tv_nsec << ".\n";
	ts=timespec_negate(ts);
	std::cout << "timespec : " << ts.tv_sec << ", " << ts.tv_nsec << ".\n";
	
	return 0;
}

