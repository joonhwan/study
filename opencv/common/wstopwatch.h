#pragma once

#include <opencv2/opencv.hpp>

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

