#pragma once

#include <opencv2/opencv.hpp>
#include <QRect>

inline cv::Rect qRectToCvRect(const QRect& qrect)
{
	return cv::Rect(qrect.x(), qrect.y(),
					qrect.width(), qrect.height());
}

inline cv::Size qSizeToCvSize(const QSize& qsize)
{
	return cv::Size(qsize.width(), qsize.height());
};


