#include "Chrono.h"

#include "../td1/timer.h"



Chrono::Chrono(void)
{
	restart();
}


Chrono::~Chrono()
{
	//Nothing !
}


void Chrono::stop(void)
{
	m_stopTime = timespec_now();

	m_isRunning = false;
}


void Chrono::restart(void)
{
	m_isRunning = true;
	m_startTime = timespec_now();
	m_stopTime = m_startTime;
}


bool Chrono::isActive(void) const
{
	return m_isRunning;
}


double Chrono::startTime(void) const
{
	return timespec_to_ms(m_startTime);
}

double Chrono::stopTime(void) const
{
	return timespec_to_ms(m_stopTime);
}


double Chrono::lap(void) const
{
	if(m_isRunning)
		return timespec_to_ms(timespec_now() - m_startTime);
	return timespec_to_ms(m_stopTime - m_startTime);
}
