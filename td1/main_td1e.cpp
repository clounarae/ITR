#include "timer.h"
#include <iostream>
#include <ctime>
#include <csignal>


int main(int argc, char * argv[])
{
	struct timespec ts1 ;
	struct timespec ts2;

	double time1_ms =4000;
	double time2_ms=6000;

	ts1 = timespec_from_ms(time1_ms);
	ts2 = timespec_from_ms(time2_ms);

	std::cout << "timespec 1: " << ts1.tv_sec << ", " << ts2.tv_nsec << ".\n";
	std::cout << "timespec 2: " << ts1.tv_sec << ", " << ts2.tv_nsec << ".\n";

	std::cout << "timemilli 1: " << time1_ms << ".\n";
	std::cout << "timemilli : " << time2_ms << ".\n";

	struct timespec checkTs1=timespec_from_ms(time1_ms);

	std::cout << "check timespec 1: " << checkTs1.tv_sec << ", " << checkTs1.tv_nsec << ".\n";

	struct timespec substactedTs=ts2 - ts1;
	double susbstractedTs_ms = 2000;
	struct timespec addedTs=ts2 + ts1;
	double addedTs_ms =10000;

	std::cout << "check substracted timespec: " << substactedTs.tv_sec << ", " << substactedTs.tv_nsec << ".\n";
	std::cout << "check substracted timespec: " << timespec_from_ms(susbstractedTs_ms).tv_sec << ", " << timespec_from_ms(susbstractedTs_ms).tv_nsec << ".\n";

	std::cout << "check added timespec: " << addedTs.tv_sec << ", " << addedTs.tv_nsec << ".\n";
	std::cout << "check added timespec: " << timespec_from_ms(addedTs_ms).tv_sec << ", " << timespec_from_ms(addedTs_ms).tv_nsec << ".\n";





	return 0;
}