#ifndef td3_Timer_h_INCLUDED
#define td3_Timer_h_INCLUDED

#include <ctime>
#include <csignal>


class Timer
{
public:
	Timer(void);
	virtual ~Timer();
	Timer(const Timer & e) = delete;
	Timer & operator=(const Timer & e) = delete;

	void start(double duration);

	void stop(void);

	virtual void callback(void) = 0;

	static void call_callback(int sig, siginfo_t * si, void * user);

protected:
	timer_t m_tid;
};


#endif
