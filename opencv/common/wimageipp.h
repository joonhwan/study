#pragma once

#include "wimage_t.h"
#include "ippi+.hpp"

template<typename T>
class WImageProcess
{
public:
	typedef typename WMonoImageT<T>::Type Mono;
	typedef typename WColorImageT<T>::Type Color;
	typedef typename WMonoInputImageT<T>::Type MonoIn;
	typedef typename WColorInputImageT<T>::Type ColorIn;
	typedef typename WMonoOutputImageT<T>::Type MonoOut;
	typedef typename WColorOutputImageT<T>::Type ColorOut;

	// template<typename T>
	void salt(Mono& image, int n)
	{
		cv::Mat* mat = image.matrix();
		for (int i = 0; i < n; ++i) {
			int x = (qrand() % image->cols) / 2;
			int y = qrand() % image->rows;
			// gray
			mat->at<T>(x,y) = 255;
		}
	}

	// template<typename T>
	void salt(Color& image, int n)
	{
		cv::Mat* mat = image.matrix();
		for (int i = 0; i < n; ++i) {
			int x = (qrand() % image->cols) / 2;
			int y = qrand() % image->rows;
			// color
			// NOTE : (y, x) 의 순서에 주의
			mat->at< cv::Vec<T,3> >(y, x)[0] = 255;
			mat->at< cv::Vec<T,3> >(y, x)[1] = 255;
			mat->at< cv::Vec<T,3> >(y, x)[2] = 255;
		}
	}
	// template<typename T>
	void absDiff(MonoIn& a, MonoIn& b, MonoOut& c)
	{
		QSize roiSize = c.roiSize();
		if (c.canOperateFrom(a,b))
		{
			IPPIP::ippiAbsDiff_C1R(a, a.step(),
								   b, a.step(),
								   c, a.step(), c.ippRoiSize());
		}
	} 

	// template<typename T>
	void absDiff(ColorIn& a, ColorIn& b, ColorOut& c)
	{
		QSize roiSize = c.roiSize();
		if (c.canOperateFrom(a,b))
		{
			IPPIP::ippiAbsDiff_C3R(a, a.step(),
								   b, a.step(),
								   c, a.step(), c.ippRoiSize());
		}
	}
};
