#include "ex_b.h"
#include "timer.h"
#include <cstdlib>
#include <iostream>

void incr(unsigned int nLoops, double* pCounter)
{
	while(nLoops--)
		*pCounter += 1.;
}

void exB(int argc, char* argv[])
{
	double counter = 0.;
	struct timespec debut, fin, duree ;

	clock_gettime(CLOCK_REALTIME, &debut);
	incr(std::atoi(argv[1]), &counter);
	clock_gettime(CLOCK_REALTIME, &fin);
	duree = fin - debut;
	std::cout << "Durée d'execution: " << timespec_to_ms(duree) << ".\n";
}
