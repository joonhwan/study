#pragma once

#include "wimage_t.h"
#include "ippi+.hpp"
#include "wlookuptable.h"
#include "wpixel.h"

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

class WImageHistogram;

namespace Wf
{
	enum LutMode
	{
		Plain = 0,
		Linear,
		Cubic,
	};
	enum Direction
	{
		Horizontal = 0,
		Vertical,
		Both,
	};
} // namespace wf

template<typename T, int C>
class WImageProcess
{
public:
	typedef WConstImageT<T,C> In;
	typedef WImageT<T,C> Out;
	typedef WImageT<T,C> InOut;
	typedef cv::Vec<T,C> ValueArray;
	typedef WLookupTable<T,C> LutData;
	typedef WPixelValue<T,C> PixelValue;
	typedef WPixelPosition<T,C> PixelPosition;
	typedef WPixelValue<double, C> MeanValue;
	struct PixelValueRange
	{
		PixelValue min;
		PixelValue max;
	};
	static void abs(InOut a);
	static void abs(In a, Out b);
	static void absDiff(In a, In b, Out c);
	static void add(In a, InOut b);
	static void add(In a, In b, Out c, int scaleFactor);
	static void add(In a, InOut b, int scaleFactor=0);
	static void add(const ValueArray& a, InOut b, int scaleFator=0);
	static void copy(In a, Out b);
	static void copySubpixel(In a, Out b);
	static void copySubpixelToFloatBuffer(In a, WImageT<float,1> b);
	static void div(const ValueArray& divisor, InOut b, int scaleFactor=0);
	static void div(In a, const ValueArray& divsior, Out b, int scaleFactor=0);
	static void div(In a, In b, Out c, int scaleFactor=0);
	static void findMaxIntensity(In a, PixelPosition& value);
	static void findMinIntensity(In a, PixelPosition& value);
	static void ramp(Out c, float offset, float slope, Wf::Direction direction);
	static void lut(InOut a, const LutData& data, Wf::LutMode mode=Linear);
	static void lut(In a, Out b, const LutData& data, Wf::LutMode mode=Linear);
	static void logical_and(In a, In b, Out c);
	static void logical_and(const ValueArray& a, InOut b);
	static void logical_and(In a, InOut b);
	static void logical_or(In a, In b, Out c);
	static void logical_or(const ValueArray& a, InOut b);
	static void logical_or(In a, InOut b);
	static void max(In a, PixelValue& value);
	static void maxEvery(In a, InOut b);
	static void mean(In a, MeanValue& value);
	static void min(In a, PixelValue& value);
	static void minEvery(In a, InOut b);
	static void minMax(In a, PixelValueRange& value);
	static void mirror(InOut a, Wf::Direction direction);
	static void mul(const ValueArray& a, InOut b, int scaleFactor=0);
	static void mul(In a, const ValueArray& b, Out c, int scaleFactor=0);
	static void mul(In a, In b, Out c, int scaleFactor=0);
	static void sub(In a, In b, Out c, int scaleFactor=0);
	static void sub(In a, InOut b, int scaleFactor=0);
	static void subValueFromImage(const ValueArray& v, InOut b, int scaleFator=0);
	static void convertTo(In a, WImageT<uchar,C> b);
	static void convertTo(In a, WImageT<signed char,C> b);
	static void convertTo(In a, WImageT<ushort,C> b);
	static void convertTo(In a, WImageT<short,C> b);
	static void convertTo(In a, WImageT<int,C> b);
	static void convertTo(In a, WImageT<float,C> b);
	static void convertTo(In a, WImageT<uchar,C> b, IppRoundMode mode);
	static void convertTo(In a, WImageT<signed char,C> b, IppRoundMode mode);
	static void convertTo(In a, WImageT<ushort,C> b, IppRoundMode mode);
	static void convertTo(In a, WImageT<short,C> b, IppRoundMode mode);
	static void convertTo(In a, WImageT<int,C> b, IppRoundMode mode);
	static void convertTo(In a, WImageT<float,C> b, IppRoundMode mode);
	// static void convertTo(In a, WImageT<TO,C> b, IppRoundMode mode, int scaleFactor);
};

// template<typename T>
// class WImageProcess<T,1>
// {
// public:
// 	template<typename TO>
// 	static void convertTo(In a, WImageT<TO,1> b)
// 	{
// 		IPPIP::ippiConvert_C1R(a, a.step(),
// 							   b, b.step(), b.ippRoiSize());
// 	}
// };

// // for color processing
// template<typename T>
// class WImageProcess<T,3>
// {
// public:
// 	typedef WConstImageT<T,3> In;
// 	typedef WImageT<T,3> Out;
// 	typedef WImageT<T,3> InOut;
// 	typedef cv::Vec<T,3> ValueArray;
// 	static void salt(InOut image, int n)
// 	{
// 		cv::Mat mat = image.matrix();
// 		QRect roi = image.roi();
// 		for (int i = 0; i < n; ++i) {
// 			int x = (qrand() % roi.width()) / 2;
// 			int y = qrand() % roi.height();
// 			// color
// 			// NOTE : (y, x) 의 순서에 주의
// 			mat.at< cv::Vec<T,3> >(y, x)[0] = 255;
// 			mat.at< cv::Vec<T,3> >(y, x)[1] = 255;
// 			mat.at< cv::Vec<T,3> >(y, x)[2] = 255;
// 		}
// 	}
// 	static void absDiff(In a, In b, Out c)
// 	{
// 		QSize roiSize = c.roiSize();
// 		IPPIP::ippiAbsDiff_C3R(a, a.step(),
// 							   b, b.step(),
// 							   c, c.step(), c.ippRoiSize());
// 	}
// 	static void abs(In a, Out b)
// 	{
// 		QSize roiSize = b.roiSize();
// 		IPPIP::ippiAbs_C3R(a, a.step(),
// 						   b, b.step(), b.ippRoiSize());
// 	}
// 	static void add(In a, In b, Out c, int scaleFactor=0)
// 	{
// 		IPPIP::ippiAdd_C3R(a, a.step(),
// 						   b, b.step(),
// 						   c, c.step(), c.ippRoiSize(), scaleFactor);
// 	}
// 	static void add(InOut a, T value, int scaleFator=0)
// 	{
// 		IPPIP::ippiAdd_C3R(&values(value,value,value)[0],
// 						   a, a.step(), a.ippRoiSize(), scaleFator);
// 	}
// 	static void add(InOut a, T value)
// 	{
// 		IPPIP::ippiAdd_C3R(&values(value,value,value)[0],
// 						   a, a.step(), a.ippRoiSize());
// 	}
// 	static void add(InOut a, const ValueArray& value, int scaleFator)
// 	{
// 		IPPIP::ippiAdd_C3R(&value[0], a, a.step(), a.ippRoiSize(), scaleFator);
// 	}
// 	static void logical_and(InOut a, T r, T g, T b)
// 	{
// 		T value[3] = {
// 			b,
// 			g,
// 			r
// 		}
// 		IPPIP::ippiAnd_C3R(&value[0],
// 						   a, a.step(), a.ippRoiSize());
// 	}
// 	static void logical_and(In a, T r, T g, T b, Out c)
// 	{
// 		IPPIP::ippiAnd_C3R(a, a.step(),
// 						   &values(b, g, r)[0],
// 						   c, c.step(), c.ippRoiSize());
// 	}
// 	static void logical_and(In a, In b, Out c)
// 	{
// 		IPPIP::ippiAnd_C3R(a, a.step,
// 						   b, b.step(),
// 						   c, c.step(), c.ippRoiSize());
// 	}
// 	template<typename TO>
// 	static void convertTo(In a, WImageT<TO,3> b)
// 	{
// 		IPPIP::ippiConvert_C3R(a, a.step(),
// 							   b, b.step(), b.ippRoiSize());
// 	}
// 	static ValueArray values(const T& val0, const T& val1, const T&val3)
// 	{
// 		return ValueArray(val0, val1, val3);
// 	}
// };
// // mono
// template<typename T>
// class WImageProcess<T,1>
// {
// public:
// 	typedef WConstImageT<T,1> In;
// 	typedef WImageT<T,1> Out;
// 	typedef WImageT<T,1> InOut;
// 	typedef cv::Vec<T,3> ValueArray;
// 	static void salt(InOut image, int n)
// 	{
// 		cv::Mat mat = image.matrix();
// 		QRect roi = image.roi();
// 		for (int i = 0; i < n; ++i) {
// 			int x = (qrand() % roi.width()) / 2;
// 			int y = qrand() % roi.height();
// 			// gray
// 			mat.at<T>(y,x) = 255;
// 		}
// 	}
// 	static void absDiff(In a, In b, Out c)
// 	{
// 		QSize roiSize = c.roiSize();
// 		IPPIP::ippiAbsDiff_C1R(a, a.step(),
// 							   b, b.step(),
// 							   c, c.step(), c.ippRoiSize());
// 	}
// 	static void abs(In a, In b, Out c)
// 	{
// 		QSize roiSize = b.roiSize();
// 		IPPIP::ippiAbs_C1R(a, a.step(),
// 						   b, b.step(), b.ippRoiSize());
// 	}
// 	static void add(In a, In b, Out c, int scaleFactor=0)
// 	{
// 		IPPIP::ippiAdd_C1R(a, a.step(),
// 						   b, b.step(),
// 						   c, c.step(), c.ippRoiSize(), scaleFactor);
// 	}
// 	static void add(InOut a, T value, int scaleFator)
// 	{
// 		IPPIP::ippiAdd_C1R(&ValueArray(value)[0],
// 						   a, a.step(), a.ippRoiSize(), scaleFator);
// 	}
// 	static void add(InOut a, T value)
// 	{
// 		IPPIP::ippiAdd_C1R(&ValueArray(value)[0], a, a.step(), a.ippRoiSize());
// 	}
// 	static void add(InOut a, const ValueArray& value, int scaleFator)
// 	{
// 		IPPIP::ippiAdd_C1R(value[0], a, a.step(), a.ippRoiSize(), scaleFator);
// 	}
// 	static void sub(In a, In b, InOut c)
// 	{
// 		IPPIP::ippiSub_C1R(a, a.step(),
// 						   b, b.step(),
// 						   c, c.step(), c.ippRoiSize(), 0);
// 	}
// 	static void subC(T b, InOut a)
// 	{
// 		IPPIP::ippiSub_C1R(b,
// 						   a, a.step(), a.ippRoiSize(), 0);
// 	}
// 	static void minEvery(In a, InOut b)
// 	{
// 		IPPIP::ippiMinEvery_C1R(a, a.step(),
// 							   b, b.step(), b.ippRoiSize());
// 	}
// 	static void logical_and(InOut a, T b)
// 	{
// 		IPPIP::ippiAnd_C1R(b,
// 						   a, a.step(), a.ippRoiSize());
// 	}
// 	static void logical_and(In a, T b, Out c)
// 	{
// 		IPPIP::ippiAnd_C1R(a, a.step(),
// 						   b,
// 						   c, c.step(), c.ippRoiSize());
// 	}
// 	static void logical_and(In a, In b, Out c)
// 	{
// 		IPPIP::ippiAnd_C1R(a, a.step(),
// 						   b, b.step(),
// 						   c, c.step(), c.ippRoiSize());
// 	}
// 	static void copySubpixel(In a, Out b)
// 	{
// 		const QPointF& fractional = a.roiTopLeftFractionalPart();
// 		IPPIP::ippiCopySubpix_C1R(a, a.step(),
// 								  b, b.step(), b.ippRoiSize(),
// 								  fractional.x(), fractional.y());
// 	}
// 	static void copySubpixel(In a, WImageT<float,1> b)
// 	{
// 		const QPointF& fractional = a.roiTopLeftFractionalPart();
// 		IPPIP::ippiCopySubpix_C1R(a, a.step(),
// 								  b, b.step(), b.ippRoiSize(),
// 								  fractional.x(), fractional.y());
// 	}
// 	template<typename TO>
// 	static void convertTo(In a, WImageT<TO,1> b)
// 	{
// 		IPPIP::ippiConvert_C1R(a, a.step(),
// 							   b, b.step(), b.ippRoiSize());
// 	}
// 	static ValueArray values(const T& val0)
// 	{
// 		return ValueArray(val0);
// 	}
// };
