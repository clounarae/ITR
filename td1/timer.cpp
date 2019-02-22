#include "timer.h"

static const long NSEC_PER_SEC = 1000000000 ;

double timespec_to_ms(const timespec& time_ts)
{
	return (double) time_ts.tv_sec*1000 + (double) time_ts.tv_nsec/1000000;
}

timespec timespec_from_ms(double time_ms)
{
	struct timespec time_ts;

	time_ts.tv_sec = time_ms/1000;
	time_ts.tv_nsec =(time_ms - time_ts.tv_sec*1000)*1000000;

	return time_ts;
}

timespec timespec_now()
{
	struct timespec ts ;
	
	timespec_get(&ts, CLOCK_REALTIME);
	
	return ts;
}

timespec timespec_negate(const timespec& time_ts)
{
	struct timespec ts;
	
	ts.tv_sec=-time_ts.tv_sec;
	if(time_ts.tv_nsec == 0)
	{
		ts.tv_nsec =0;
	}
	else
	{
		ts.tv_nsec = NSEC_PER_SEC-time_ts.tv_nsec;
		ts.tv_sec--;
	}
	
	return ts;
	
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
	struct timespec ts;
	
	ts.tv_sec= time1_ts.tv_sec + time2_ts.tv_sec;
	ts.tv_nsec= time1_ts.tv_nsec + time2_ts.tv_nsec;
	
	if(ts.tv_nsec >= NSEC_PER_SEC)
	{
		ts.tv_nsec-=NSEC_PER_SEC;
		ts.tv_sec++;
	}
	
	return ts;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_add(time1_ts,timespec_negate(time2_ts));
}

timespec timespec_wait(const timespec& delay_ts, bool force)
{
	struct timespec rem = {0, 0};
	
	if(force)
	{
		rem = delay_ts;
		while(nanosleep(&rem, &rem) == -1);
	}
	else
		nanosleep(&delay_ts, &rem);
	
	return rem;
}

timespec  operator- (const timespec& time_ts)
{
	return timespec_negate(time_ts);
}

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_add(time1_ts,time2_ts);
}

timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{

	return time1_ts + (-time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
	return time_ts=time_ts+delay_ts ;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
	return time_ts=time_ts-delay_ts ;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
	return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
	return !(time1_ts == time2_ts);
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
	return (time1_ts.tv_sec < time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec < time2_ts.tv_nsec) );
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
	return !(time1_ts < time2_ts) && !(time1_ts==time2_ts);
}


