#include "DTimer.h"
#include <stdio.h>

	
	//dfloat DTimer::currentTime = 0.0f;
	//dfloat DTimer::startTime = 0.0f;
	//dfloat DTimer::diffTime = 0.0f;
	//dfloat DTimer::increasingDuration = 0.0f;
	//dfloat DTimer::decreasingDuration = 0.0f;

	
	DTimer::DTimer()
	{
		initTimer();
	}
	
	DTimer::DTimer(unsigned loopCount , float increasingDuration)
	{
		initTimer();
		DTimer::increasingDuration = increasingDuration;
	}
	
	void DTimer::initTimer()
	{
		diffTime = 0.0f;
		decreasingDuration = 0.0f;
		
		increasingDuration = 1000;
		

		timeval t;
		gettimeofday(&t, 0);
		m_start_sec = t.tv_sec;
		m_start_msec = t.tv_usec * 0.001f;
		startTime = (double)t.tv_sec * 1000 + (double)t.tv_usec * 0.001f;

		currentTime = startTime;
	}
	
	void DTimer::tick()
	{
		
		timeval t;
		gettimeofday(&t, 0);
		currentTime = (double)t.tv_sec * 1000 + (double)t.tv_usec * 0.001f;;	
		static long count = 0;
		count++;
		if ( diffTime > increasingDuration )
		{
			fps = count*1000.0/diffTime;

//#ifdef MACOSX
//			printf("\nFPS = %d" , fps);
//#endif
			count = 0;
			startTime = currentTime;
		}
		diffTime = ( currentTime - startTime );
	}
	
	void DTimer::setCurrentTime(float time)
	{
		startTime = time;
	}
	
	double DTimer::getCurrentTime()
	{
		double time;
		
		timeval t;
		gettimeofday(&t, 0);
		time =  (double)t.tv_sec  * 1000 + (double)t.tv_usec * 0.001f;
		//printf("Time = %f\n", time);
		return time;
	}
	
	void DTimer::stop()
	{
		
	}
	
	float DTimer::value()
	{
		return diffTime / increasingDuration;
	}
	
	void DTimer::setIncreasingDuration(float increasingDuration)
	{
		DTimer::increasingDuration = increasingDuration;
	}
	
	float DTimer::getIncreasingDuration()
	{
		return increasingDuration;
	}
	
	void DTimer::setDecreasingDuration(float decreasingDuration)
	{
		DTimer::decreasingDuration = decreasingDuration;
	}
	
	float DTimer::getDecreasingDuration()
	{
		return decreasingDuration;
	}


	