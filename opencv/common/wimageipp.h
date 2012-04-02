#pragma once

#include "wimage_t.h"
#include "ippi+.hpp"

template<typename T, int C>
class WImageProcess
{
public:
	typedef WInputImageT<T,C> In;
	typedef WOutputImageT<T,C> Out;
	typedef WOutputImageT<T,C> InOut;
	typedef cv::Vec<T,C> ValueArray;

	void salt(InOut image, int n);
	void absDiff(In a, In b, Out c);
	void abs(In a, In b, Out c);
	void addC(InOut a, T value, int scaleFator);
	void addC(InOut a, ValueArray& value, int scaleFator);
	template<typename T1, int C>
	void convertTo(In a, WOutputImageT<T1,C> b);
	void doSomething();
};

// for color processing
template<typename T>
class WImageProcess<T,3>
{
public:
	typedef WInputImageT<T,3> In;
	typedef WOutputImageT<T,3> Out;
	typedef WOutputImageT<T,3> InOut;
	typedef cv::Vec<T,3> ValueArray;

	void salt(InOut image, int n)
	{
		cv::Mat mat = image.matrix();
		QRect roi = image.roi();
		for (int i = 0; i < n; ++i) {
			int x = (qrand() % roi.width()) / 2;
			int y = qrand() % roi.height();
			// color
			// NOTE : (y, x) 의 순서에 주의
			mat.at< cv::Vec<T,3> >(y, x)[0] = 255;
			mat.at< cv::Vec<T,3> >(y, x)[1] = 255;
			mat.at< cv::Vec<T,3> >(y, x)[2] = 255;
		}
	}
	void absDiff(In a, In b, Out c)
	{
		QSize roiSize = c.roiSize();
		if (c.canOperateFrom(a,b))
		{
			IPPIP::ippiAbsDiff_C3R(a, a.step(),
								   b, b.step(),
								   c, c.step(), c.ippRoiSize());
		}
	}
	void abs(In a, Out b)
	{
		QSize roiSize = b.roiSize();
		if (b.canOperateFrom(a))
		{
			IPPIP::ippiAbs_C3R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
		}
	}
	void addC(InOut a, T value, int scaleFator)
	{
		IPPIP::ippiAdd_C3R(&values(value,value,value)[0], a, a.step(), a.ippRoiSize(), scaleFator);
	}
	void addC(InOut a, const ValueArray& value, int scaleFator)
	{
		IPPIP::ippiAdd_C3R(&value[0], a, a.step(), a.ippRoiSize(), scaleFator);
	}
	template<typename T1>
	void convertTo(In a, WOutputImageT<T1,3> b)
	{
		IPPIP::ippiConvert_C3R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
	}
	ValueArray values(const T& val0, const T& val1, const T&val3) const
	{
		return ValueArray(val0, val1, val3);
	}
	void doSomething()
	{
	}
};

// mono
template<typename T>
class WImageProcess<T,1>
{
public:
	typedef WInputImageT<T,1> In;
	typedef WOutputImageT<T,1> Out;
	typedef WOutputImageT<T,1> InOut;
	typedef cv::Vec<T,3> ValueArray;

	void salt(InOut image, int n)
	{
		cv::Mat mat = image.matrix();
		QRect roi = image.roi();
		for (int i = 0; i < n; ++i) {
			int x = (qrand() % roi.width()) / 2;
			int y = qrand() % roi.height();
			// gray
			mat.at<T>(y,x) = 255;
		}
	}
	void absDiff(In a, In b, Out c)
	{
		QSize roiSize = c.roiSize();
		if (c.canOperateFrom(a,b))
		{
			IPPIP::ippiAbsDiff_C1R(a, a.step(),
								   b, b.step(),
								   c, c.step(), c.ippRoiSize());
		}
	}
	void abs(In a, In b, Out c)
	{
		QSize roiSize = b.roiSize();
		if (b.canOperateFrom(a))
		{
			IPPIP::ippiAbs_C1R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
		}
	}
	void addC(InOut a, T value, int scaleFator)
	{
		IPPIP::ippiAdd_C1R(&ValueArray(value)[0], a, a.step(), a.ippRoiSize(), scaleFator);
	}
	void addC(InOut a, const ValueArray& value, int scaleFator)
	{
		IPPIP::ippiAdd_C1R(value[0], a, a.step(), a.ippRoiSize(), scaleFator);
	}
	template<typename T1>
	void convertTo(In a, WOutputImageT<T1,1> b)
	{
		IPPIP::ippiConvert_C1R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
	}
	ValueArray values(const T& val0) const
	{
		return ValueArray(val0);
	}
};
