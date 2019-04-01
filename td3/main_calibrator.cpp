#include <iostream>


#include "Calibrator.h"
#include "CpuLoop.h"


int main(int argc, char * argv[])
{
	Calibrator calibrator(10, 1000);
	CpuLoop cpuLoop(calibrator);

	std::cout << "Starting 1 sed loop ... (" << calibrator.nLoops(1000) << " iterations)\n";
	cpuLoop.runTime(1000);
	std::cout << "End.\n";

	return 0;
}
