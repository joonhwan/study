#pragma once

#include "wimage_t.h"
#include "ippi+.hpp"

namespace Wf {

template<typename T>
void salt(WImageT<T>& image, int n)
{
	cv::Mat* mat = image.matrix();
	int channel = mat->channels();
	for (int i = 0; i < n; ++i) {
		int x = (qrand() % image->cols) / 2;
		int y = qrand() % image->rows;
		switch (channel) {
		case 1:
			// gray
			mat->at<T>(x,y) = 255;
			break;
		case 3:
			// color
			// NOTE : (y, x) 의 순서에 주의
			mat->at< cv::Vec<T,3> >(y, x)[0] = 255;
			mat->at< cv::Vec<T,3> >(y, x)[1] = 255;
			mat->at< cv::Vec<T,3> >(y, x)[2] = 255;
			break;
		}
	}
}

template<typename T>
void absDiff(WInputImageT<T>& a, const WInputImageT<T>& b, WOutputImageT<T>& c)
{
	QSize roiSize = c.roiSize();
	if (c.hasSameChannelWith(a,b) && c.canOperateFrom(a,b))
	{
#ifdef RAW_IPP
		switch (c.channels()) {
		case 1:
			IPPIP::ippiAbsDiff_C1R(a, a.step(),
								   b, a.step(),
								   c, a.step(), c.ippRoiSize());
			break;
		case 3:
			IPPIP::ippiAbsDiff_C3R(a, a.step(),
								   b, a.step(),
								   c, a.step(), c.ippRoiSize());
			break;
		}
#else
		cv::absdiff(a.matrix(c.roiSize()), b.matrix(c.roiSize()),
					c.matrix());
#endif
	}

} // namespace Wf

}

