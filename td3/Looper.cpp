#include "Looper.h"


Looper::Looper(void)
{
	m_doStop = false;
	m_iLoop = 0.;
}

Looper::~Looper()
{
	//Nuthin!
}


void Looper::runLoop(double nLoops)
{
	while(!m_doStop && m_iLoop < nLoops)
		m_iLoop += 1.;
}


double Looper::getSample(void)
{
	return m_iLoop;
}


double Looper::stopLoop(void)
{
	m_doStop = true;

	return m_iLoop;
}
