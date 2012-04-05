#pragma once

#include "wimage_t.h"
#include "ippi+.hpp"

template<typename T, int C>
class WImageProcess
{
public:
	// no declaration is needed ?

	// typedef WInputImageT<T,C> In;
	// typedef WOutputImageT<T,C> Out;
	// typedef WOutputImageT<T,C> InOut;
	// typedef cv::Vec<T,C> ValueArray;

	// static void salt(InOut image, int n);
	// static void absDiff(In a, In b, Out c);
	// static void abs(In a, In b, Out c);
	// static void add(InOut a, T value, int scaleFator);
	// static void add(InOut a, ValueArray& value, int scaleFator);
	// static void add(InOut a, T value, int scaleFator);
	// template<typename T1, int C>
	// static void convertTo(In a, WOutputImageT<T1,C> b);
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

	static void salt(InOut image, int n)
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
	static void absDiff(In a, In b, Out c)
	{
		QSize roiSize = c.roiSize();
		IPPIP::ippiAbsDiff_C3R(a, a.step(),
							   b, b.step(),
							   c, c.step(), c.ippRoiSize());
	}
	static void abs(In a, Out b)
	{
		QSize roiSize = b.roiSize();
		IPPIP::ippiAbs_C3R(a, a.step(),
						   b, b.step(), b.ippRoiSize());
	}
	static void add(InOut a, T value, int scaleFator)
	{
		IPPIP::ippiAdd_C3R(&values(value,value,value)[0],
						   a, a.step(), a.ippRoiSize(), scaleFator);
	}
	static void add(InOut a, T value)
	{
		IPPIP::ippiAdd_C3R(&values(value,value,value)[0],
						   a, a.step(), a.ippRoiSize());
	}
	static void add(InOut a, const ValueArray& value, int scaleFator)
	{
		IPPIP::ippiAdd_C3R(&value[0], a, a.step(), a.ippRoiSize(), scaleFator);
	}
	static void logical_and(InOut a, T r, T g, T b)
	{
		T value[3] = {
			b,
			g,
			r
		}
		IPPIP::ippiAnd_C3R(&value[0],
						   a, a.step(), a.ippRoiSize());
	}

// hijacked from log4cxx.
// see apache-log4cxx-x.y.z/src/main/include/log4cxx/spi/location/locationinfo.h
#if !defined(WLOG_LOCATION)
#if defined(_MSC_VER)
#if _MSC_VER >= 1300
#define __WLOG_FUNC__ __FUNCSIG__
#endif
#else
#if defined(__GNUC__)
#define __WLOG_FUNC__ __PRETTY_FUNCTION__
#endif
#endif
#if !defined(__WLOG_FUNC__)
#define __WLOG_FUNC__ ""
#endif
#define WLOG_LOCATION __FILE__,__WLOG_FUNC__,__LINE__
#endif

	static void logical_and(In a, T r, T g, T b, Out c)
	{
		IPPIP::ippiAnd_C3R(a, a.step(),
						   &values(b, g, r)[0],
						   c, c.step(), c.ippRoiSize());
	}
	static void logical_and(In a, In b, Out c)
	{
		IPPIP::ippiAnd_C3R(a, a.step,
						   b, b.step(),
						   c, c.step(), c.ippRoiSize());
	}
	template<typename T1>
	static void convertTo(In a, WOutputImageT<T1,3> b)
	{
		IPPIP::ippiConvert_C3R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
	}
	static ValueArray values(const T& val0, const T& val1, const T&val3)
	{
		return ValueArray(val0, val1, val3);
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

	static void salt(InOut image, int n)
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
	static void absDiff(In a, In b, Out c)
	{
		QSize roiSize = c.roiSize();
		IPPIP::ippiAbsDiff_C1R(a, a.step(),
							   b, b.step(),
							   c, c.step(), c.ippRoiSize());
	}
	static void abs(In a, In b, Out c)
	{
		QSize roiSize = b.roiSize();
		IPPIP::ippiAbs_C1R(a, a.step(),
						   b, b.step(), b.ippRoiSize());
	}
	static void add(InOut a, T value, int scaleFator)
	{
		IPPIP::ippiAdd_C1R(&ValueArray(value)[0],
						   a, a.step(), a.ippRoiSize(), scaleFator);
	}
	static void add(InOut a, T value)
	{
		IPPIP::ippiAdd_C1R(&ValueArray(value)[0], a, a.step(), a.ippRoiSize());
	}
	static void add(InOut a, const ValueArray& value, int scaleFator)
	{
		IPPIP::ippiAdd_C1R(value[0], a, a.step(), a.ippRoiSize(), scaleFator);
	}
	static void sub(In a, In b, InOut c)
	{
		IPPIP::ippiSub_C1R(a, a.step(),
						   b, b.step(),
						   c, c.step(), c.ippRoiSize(), 0);
	}
	static void subC(T b, InOut a)
	{
		IPPIP::ippiSub_C1R(b,
						   a, a.step(), a.ippRoiSize(), 0);
	}
	static void minEvery(In a, InOut b)
	{
		IPPIP::ippiMinEvery_C1R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
	}
	static void logical_and(InOut a, T b)
	{
		IPPIP::ippiAnd_C1R(b,
						   a, a.step(), a.ippRoiSize());
	}
	static void logical_and(In a, T b, Out c)
	{
		IPPIP::ippiAnd_C1R(a, a.step(),
						   b,
						   c, c.step(), c.ippRoiSize());
	}
	static void logical_and(In a, In b, Out c)
	{
		IPPIP::ippiAnd_C1R(a, a.step(),
						   b, b.step(),
						   c, c.step(), c.ippRoiSize());
	}
	static void copySubpixel(In a, Out b, float x, float y)
	{
		IPPIP::ippiCopySubpix_C1R(a, a.step(),
								  b, b.step(), b.ippRoiSize(),
								  x, y);
	}
	static void copySubpixel(In a, WOutputImageT<float,1> b, float x, float y)
	{
		IPPIP::ippiCopySubpix_C1R(a, a.step(),
								  b, b.step(), b.ippRoiSize(),
								  x, y);
	}
	template<typename T1>
	static void convertTo(In a, WOutputImageT<T1,1> b)
	{
		IPPIP::ippiConvert_C1R(a, a.step(),
							   b, b.step(), b.ippRoiSize());
	}
	static ValueArray values(const T& val0)
	{
		return ValueArray(val0);
	}
};
