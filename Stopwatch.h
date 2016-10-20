/* 
 * File:    Stopwatch.h
 * Author:  Mauricio Matamoros
 *
 * Created: October 19, 2016
 */
 

#ifndef __STOP_WATCH_H__
#define __STOP_WATCH_H__

class Stopwatch
{
private:
	long long startTime;
	long long currentTime;
	bool running;
	Stopwatch(const Stopwatch& other);

public:
	Stopwatch(void);
	virtual ~Stopwatch(void);
	void start();
	void stop();
	void reset();
	long elapsedMilliseconds();
	long long elapsedMicroseconds();
};

#endif // __STOP_WATCH_H__