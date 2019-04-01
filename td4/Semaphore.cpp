#include "Semaphore.h"


Semaphore::Semaphore(unsigned initCount, unsigned maxCount)
{
	m_counter = initCount;
	m_maxCount = m_maxCount;
}

Semaphore::~Semaphore()
{
	//Nuthin?
}


void Semaphore::give(void)
{
	Mutex::Lock lock(m_mutex);
	if(m_counter < m_maxCount)
	{
		m_counter++;
		lock.notify();
	}
}

void Semaphore::take(void)
{
	Mutex::Lock lock(m_mutex);
	while(!m_counter)
		lock.wait();
	m_counter--;
}

bool Semaphore::take(double timeout_ms)
{
	try
	{
		Mutex::Lock lock(m_mutex);

		while(!m_counter)
			if(!lock.wait(timeout_ms))
				throw Mutex::Lock::TimeoutException();
		m_counter--;
	}
	catch(Mutex::Lock::TimeoutException)
	{
		return false;
	}

	return true;
}
