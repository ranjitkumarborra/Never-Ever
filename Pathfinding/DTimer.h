#ifndef _DTIMER_H
#define _DTIMER_H


#include <sys/time.h>

	
	class DTimer
	{
	public:
		
		void start();
		
		void stop();
		
		void tick();
		
		float value();
		
		void setCurrentTime(float time);
		
		double getCurrentTime();
				
		float getIncreasingDuration();
		
		float getDecreasingDuration();
		
		void setIncreasingDuration(float);
		
		void setDecreasingDuration(float);
		
		DTimer();
		
		DTimer(unsigned , float);
		
		
	private:
		
		
		unsigned int fps;
		double currentTime , startTime;
		double diffTime;
		
		unsigned loopCount;
		float increasingDuration;
		float decreasingDuration;
		
		void initTimer();
		
		double m_start_sec;
		double m_start_msec;
		
	};


#endif