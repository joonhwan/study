#pragma once

#include <opencv2/opencv.hpp>
#include <QRect>

inline cv::Rect qRectToCvRect(const QRect& qrect)
{
	return cv::Rect(qrect.x(), qrect.y(),
					qrect.width(), qrect.height());
}

