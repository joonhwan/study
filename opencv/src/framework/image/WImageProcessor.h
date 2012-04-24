#pragma once

#include "image/WImageGlobal.h"
#include "image/WImageT.h"
#include "image/WLookupTable.h"
#include "image/wpixel.h"
#include "image/WIppKernel.h"
#include "image/WHistogram.h"

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

enum InterpolationMode
{
	InterNearest = 0,
	InterLinear,
	InterCubic,
	InterSuper,
	InterLanczos,
}; // namespace wf

};

#include <QThreadStorage>
class WImageLastError
{
public:
	struct ErrorInfo
	{
		int code;
		QString description;
	};
	typedef QThreadStorage<ErrorInfo> LastError;
	static QString lastError();
	static int lastErrorCode();
};

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

	struct PixelValueRange
	{
		PixelValue min;
		PixelValue max;
	};
	// typedef WCvKernel CvKernel;
	static bool abs(InOut a);
	static bool abs(In a, Out b);
	static bool absDiff(In a, In b, Out c);
	static bool add(In a, In b, Out c, int scaleFactor=0);
	static bool add(In a, InOut b, int scaleFactor=0);
	static bool add(const PixelValue& a, InOut b, int scaleFator=0);
	static bool copy(In a, Out b);
	static bool copySubpixel(In a, Out b);
	static bool copySubpixelToFloatBuffer(In a, WImageT<float,1> b);
	static bool div(const PixelValue& a, InOut b, int scaleFactor=0);
	static bool div(In a, const PixelValue& b, Out c, int scaleFactor=0);
	static bool div(In a, In b, Out c, int scaleFactor=0);
	static bool filter(In a, const IntKernel3x3& b, Out c);
	static bool filter(In a, const IntKernel5x5& b, Out c);
	// static bool filter(In a, const CvKernel& b, Out c);
	static bool findMaxIntensity(In a, PixelPosition& value);
	static bool findMinIntensity(In a, PixelPosition& value);
    static bool calculateHistogram(In a, IppHistogramParameter<C>& parameter, WHistogramResult<int, C>& result);
	// static bool calculateHistogram(In a, CvHistogramParameter<C>& parameter, CvHistogramResult& result);
	// static bool calculateHistogram(In a, HistogramParameter& parameter, FloatHistogramResult& result);
	static bool ramp(Out c, float offset, float slope, Wf::Direction direction);
	static bool lut(InOut a, const LutData& data, Wf::LutMode mode=Linear);
	static bool lut(In a, Out b, const LutData& data, Wf::LutMode mode=Linear);
	static bool logical_and(In a, In b, Out c);
	static bool logical_and(const PixelValue& a, InOut b);
	static bool logical_and(In a, InOut b);
	static bool logical_or(In a, In b, Out c);
	static bool logical_or(const PixelValue& a, InOut b);
	static bool logical_or(In a, InOut b);
	static bool max(In a, PixelValue& value);
	static bool maxEvery(In a, InOut b);
	static bool mean(In a, RealValue& value);
	static bool min(In a, PixelValue& value);
	static bool minEvery(In a, InOut b);
	static bool minMax(In a, PixelValueRange& value);
	static bool mirror(InOut a, Wf::Direction direction);
	static bool mul(const PixelValue& a, InOut b, int scaleFactor=0);
	static bool mul(In a, const PixelValue& b, Out c, int scaleFactor=0);
	static bool mul(In a, In b, Out c, int scaleFactor=0);
	static bool resize(In a, Out c, Wf::InterpolationMode mode=Wf::InterLinear);
	static bool set(const PixelValue& a, Out b);
	static bool sqr(In a, Out b, int scaleFactor=0);
	static bool sqr(InOut a, int scaleFactor=0);
	static bool sqrt(In a, Out b, int scaleFactor=0);
	static bool sqrt(InOut a, int scaleFactor=0);
	static bool sub(In a, In b, Out c, int scaleFactor=0);
	static bool sub(In a, InOut b, int scaleFactor=0);
	static bool subValueFromImage(const PixelValue& v, InOut b, int scaleFator=0);
	static bool sum(In a, RealValue& value);
	static bool convertTo(In a, WImageT<uchar,C> b);
	static bool convertTo(In a, WImageT<signed char,C> b);
	static bool convertTo(In a, WImageT<ushort,C> b);
	static bool convertTo(In a, WImageT<short,C> b);
	static bool convertTo(In a, WImageT<int,C> b);
	static bool convertTo(In a, WImageT<unsigned int,C> b);
	static bool convertTo(In a, WImageT<float,C> b);
	static bool convertTo(In a, WImageT<uchar,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<signed char,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<ushort,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<short,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<int,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<unsigned int,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<float,C> b, Wf::RoundMode mode);
	static bool convertTo(In a, WImageT<uchar,C> b, Wf::RoundMode mode, int scaleFactor);
	static bool convertTo(In a, WImageT<signed char,C> b, Wf::RoundMode mode, int scaleFactor);
	static bool convertTo(In a, WImageT<short,C> b, Wf::RoundMode mode, int scaleFactor);
	static bool convertTo(In a, WImageT<ushort,C> b, Wf::RoundMode mode, int scaleFactor);
	static bool convertTo(In a, WImageT<int,C> b, Wf::RoundMode mode, int scaleFactor);
	static bool convertTo(In a, WImageT<unsigned int,C> b, Wf::RoundMode mode, int scaleFactor);

	// static void convertTo(In a, WImageT<TO,C> b, RoundMode mode, int scaleFactor);
protected:
};
