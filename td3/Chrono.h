#ifndef td3_Chrono_h_INCLUDED
#define td3_Chrono_h_INCLUDED

#include <ctime>


class Chrono
{
public:
	Chrono(void);
	~Chrono();
	Chrono(const Chrono & e) = delete;
	Chrono & operator=(const Chrono & e) = delete;

	void stop(void);

	void restart(void);

	bool isActive(void) const;

	double startTime(void) const;

	double stopTime(void) const;

	double lap(void) const;

private:
	bool m_isRunning;
	timespec m_startTime;
	timespec m_stopTime;
};


#endif
