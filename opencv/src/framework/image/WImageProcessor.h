#pragma once

#include "image/WImageT.h"
#include "image/WLookupTable.h"
#include "image/wpixel.h"
#include "image/WIppKernel.h"

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

namespace Wf {

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

enum RoundMode
{
	RoundDown = 0,
	RoundNear,
	RoundAccurate,
};

} // namespace wf

template<typename T, int C>
class WImageProcess
{
public:
	typedef WConstImageT<T,C> In;
	typedef WImageT<T,C> Out;
	typedef WImageT<T,C> InOut;
	typedef WLookupTable<T,C> LutData;
	typedef WPixelValue<T,C> PixelValue;
	typedef WPixelPosition<T,C> PixelPosition;
	typedef WPixelValue<double, C> RealValue;
	typedef WIppIntKernel<1,3> IntKernel3x3;
	typedef WIppIntKernel<1,5> IntKernel5x5;
	// typedef WCvKernel CvKernel;
	struct PixelValueRange
	{
		PixelValue min;
		PixelValue max;
	};
	static void abs(InOut a);
	static void abs(In a, Out b);
	static void absDiff(In a, In b, Out c);
	static void add(In a, In b, Out c, int scaleFactor=0);
	static void add(In a, InOut b, int scaleFactor=0);
	static void add(const PixelValue& a, InOut b, int scaleFator=0);
	static void copy(In a, Out b);
	static void copySubpixel(In a, Out b);
	static void copySubpixelToFloatBuffer(In a, WImageT<float,1> b);
	static void div(const PixelValue& a, InOut b, int scaleFactor=0);
	static void div(In a, const PixelValue& b, Out c, int scaleFactor=0);
	static void div(In a, In b, Out c, int scaleFactor=0);
	static void filter(In a, const IntKernel3x3& b, Out c);
	static void filter(In a, const IntKernel5x5& b, Out c);
	// static void filter(In a, const CvKernel& b, Out c);
	static void findMaxIntensity(In a, PixelPosition& value);
	static void findMinIntensity(In a, PixelPosition& value);
	static void ramp(Out c, float offset, float slope, Wf::Direction direction);
	static void lut(InOut a, const LutData& data, Wf::LutMode mode=Linear);
	static void lut(In a, Out b, const LutData& data, Wf::LutMode mode=Linear);
	static void logical_and(In a, In b, Out c);
	static void logical_and(const PixelValue& a, InOut b);
	static void logical_and(In a, InOut b);
	static void logical_or(In a, In b, Out c);
	static void logical_or(const PixelValue& a, InOut b);
	static void logical_or(In a, InOut b);
	static void max(In a, PixelValue& value);
	static void maxEvery(In a, InOut b);
	static void mean(In a, RealValue& value);
	static void min(In a, PixelValue& value);
	static void minEvery(In a, InOut b);
	static void minMax(In a, PixelValueRange& value);
	static void mirror(InOut a, Wf::Direction direction);
	static void mul(const PixelValue& a, InOut b, int scaleFactor=0);
	static void mul(In a, const PixelValue& b, Out c, int scaleFactor=0);
	static void mul(In a, In b, Out c, int scaleFactor=0);
	static void set(const PixelValue& a, Out b);
	static void sqr(In a, Out b, int scaleFactor=0);
	static void sqr(InOut a, int scaleFactor=0);
	static void sqrt(In a, Out b, int scaleFactor=0);
	static void sqrt(InOut a, int scaleFactor=0);
	static void sub(In a, In b, Out c, int scaleFactor=0);
	static void sub(In a, InOut b, int scaleFactor=0);
	static void subValueFromImage(const PixelValue& v, InOut b, int scaleFator=0);
	static void sum(In a, RealValue& value);
	static void convertTo(In a, WImageT<uchar,C> b);
	static void convertTo(In a, WImageT<signed char,C> b);
	static void convertTo(In a, WImageT<ushort,C> b);
	static void convertTo(In a, WImageT<short,C> b);
	static void convertTo(In a, WImageT<int,C> b);
	static void convertTo(In a, WImageT<unsigned int,C> b);
	static void convertTo(In a, WImageT<float,C> b);
	static void convertTo(In a, WImageT<uchar,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<signed char,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<ushort,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<short,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<int,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<unsigned int,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<float,C> b, Wf::RoundMode mode);
	static void convertTo(In a, WImageT<uchar,C> b, Wf::RoundMode mode, int scaleFactor);
	static void convertTo(In a, WImageT<signed char,C> b, Wf::RoundMode mode, int scaleFactor);
	static void convertTo(In a, WImageT<short,C> b, Wf::RoundMode mode, int scaleFactor);
	static void convertTo(In a, WImageT<ushort,C> b, Wf::RoundMode mode, int scaleFactor);
	static void convertTo(In a, WImageT<int,C> b, Wf::RoundMode mode, int scaleFactor);
	static void convertTo(In a, WImageT<unsigned int,C> b, Wf::RoundMode mode, int scaleFactor);

	// static void convertTo(In a, WImageT<TO,C> b, RoundMode mode, int scaleFactor);
};
