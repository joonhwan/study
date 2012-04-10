#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

class WStopWatch
{
public:
	WStopWatch(bool startNow=true)
		: m_duration(0)
	{
		if (startNow) {
			start();
		}
	}
	void start()
	{
		m_duration = static_cast<double>(cv::getTickCount());
	}
	double elapsedTime()
	{
		m_duration = (static_cast<double>(cv::getTickCount()) - m_duration);
		return m_duration / cv::getTickFrequency();
	}
protected:
	double m_duration;
};

class WStopWatchLogger
{
public:
	WStopWatchLogger(const char* context = 0)
		: m_stopWatch(true)
		, m_context(context)
	{
	}
	virtual ~WStopWatchLogger()
	{
		std::cout << (m_context ? m_context : "unknown context")
				  << " : " << m_stopWatch.elapsedTime() << std::endl;
	}
protected:
	const char* m_context;
	WStopWatch m_stopWatch;
};

