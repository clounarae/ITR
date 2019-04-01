#include <iostream>

#include "Chrono.h"
#include "Timer.h"
#include "PeriodicTimer.h"


class TimerSample : public PeriodicTimer
{
public:
	TimerSample(void){};
	~TimerSample(){};

	virtual void callback(void)
	{
		std::cout << "Callback from timer !!\n";
	};
};

int main(int argc, char * argv[])
{
	char c = '\0';
	Chrono chrono;
	TimerSample timer;

	std::cout << "Chrono value at the start : " << chrono.lap() << ".\n";

	timer.start(1600.);

	std::cout << "Waiting for input...\n";
	std::cin >> c;


	std::cout << "Chrono value near the end : " << chrono.lap() << ".\n";
	chrono.stop();

	std::cout << "Chrono final value : " << chrono.lap() << ".\n";

	return 0;
}
