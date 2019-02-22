#include "timer.h"
#include <iostream>
#include <ctime>
#include <csignal>
#include "ex_a.h"
#include "ex_b.h"
#include "ex_c.h"


int main(int argc, char * argv[])
{
	//exA();
	exC();
	/*
	struct timespec ts ;//exo e
	double time_ms = 0.;
	ts=timespec_now();
	std::cout << "timespec : " << ts.tv_sec << ", " << ts.tv_nsec << ".\n";
	time_ms=timespec_to_ms(ts);
	std::cout << "timemilli : " << time_ms << ".\n";
	ts=timespec_from_ms(time_ms);
	std::cout << "timespec : " << ts.tv_sec << ", " << ts.tv_nsec << ".\n";
	ts=timespec_negate(ts);
	std::cout << "timespec : " << ts.tv_sec << ", " << ts.tv_nsec << ".\n";
	*/
	return 0;
}

