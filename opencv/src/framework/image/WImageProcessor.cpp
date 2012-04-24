#include "image/WImageProcessor.h"
#include "WImageProcessorMacros.h"
#include "ippi_ext.hpp"

namespace {

IppiAxis Dir2IppAxis(Wf::Direction dir)
{
	switch (dir)
	{
	case Wf::Horizontal:
		return ippAxsHorizontal;
	case Wf::Vertical:
		return ippAxsVertical;
	case Wf::Both:
		return ippAxsBoth;
	default:
		Q_ASSERT(FALSE);
		return ippAxsBoth;
	}
}

IppRoundMode RoundMode2IppRoundMode(Wf::RoundMode mode)
{
	switch (mode)
	{
	case Wf::RoundDown:
		return ippRndZero;
	case Wf::RoundNear:
		return ippRndNear;
	case Wf::RoundAccurate:
		return ippRndFinancial;
	default:
		Q_ASSERT(FALSE);
		return ippRndZero;
	}
}

int interpolationMode2Cv(Wf::InterpolationMode mode)
{
	switch (mode)
	{
	case Wf::InterNearest:
		return cv::INTER_NEAREST;
	case Wf::InterLinear:
		return cv::INTER_LINEAR;
	case Wf::InterCubic:
		return cv::INTER_CUBIC;
	case Wf::InterSuper:
		return cv::INTER_AREA;
	case Wf::InterLanczos:
		return cv::INTER_LANCZOS4;
	default:
		Q_ASSERT(FALSE);
		return cv::INTER_LINEAR;
	}
}

} // nonamed namespace

// static bool abs(InOut a)
FUNC_INOUT(short, 1, abs, Abs)
FUNC_INOUT(float, 1, abs, Abs)
FUNC_INOUT(short, 3, abs, Abs)
FUNC_INOUT(float, 3, abs, Abs)

// static bool abs(In a, Out b);
FUNC_IN_OUT(short, 1, abs, Abs)
FUNC_IN_OUT(float, 1, abs, Abs)
FUNC_IN_OUT(short, 3, abs, Abs)
FUNC_IN_OUT(float, 3, abs, Abs)

// static bool absDiff(In a, In b, Out c);
FUNC_IN_IN_OUT(uchar, 1, absDiff, AbsDiff)
FUNC_IN_IN_OUT(uchar, 3, absDiff, AbsDiff)

// static bool add(In a, In b, Out c, int scaleFactor=0);
FUNC_IN_IN_OUT_SCALE(uchar, 1, add, Add)
FUNC_IN_IN_OUT_SCALE(ushort, 1, add, Add)
FUNC_IN_IN_OUT_SCALE(short, 1, add, Add)
FUNC_IN_IN_OUT_SCALE(uchar, 3, add, Add)
FUNC_IN_IN_OUT_SCALE(ushort, 3, add, Add)
FUNC_IN_IN_OUT_SCALE(short, 3, add, Add)

// static bool add(In a, InOut b, int scaleFactor=0);
FUNC_IN_INOUT_SCALE(uchar, 1, add, Add)
FUNC_IN_INOUT_SCALE(ushort, 1, add, Add)
FUNC_IN_INOUT_SCALE(short, 1, add, Add)
FUNC_IN_INOUT_SCALE(uchar, 3, add, Add)
FUNC_IN_INOUT_SCALE(ushort, 3, add, Add)
FUNC_IN_INOUT_SCALE(short, 3, add, Add)

// static bool add(const PixelValue& a, InOut b, int scaleFator=0);
FUNC_CVALUE_INOUT_SCALE(uchar, 1, add, Add)
FUNC_CVALUE_INOUT_SCALE(ushort, 1, add, Add)
FUNC_CVALUE_INOUT_SCALE(short, 1, add, Add)
FUNC_CVALUE_INOUT_SCALE(float, 1, add, Add)
FUNC_CVALUE_INOUT_SCALE(uchar, 3, add, Add)
FUNC_CVALUE_INOUT_SCALE(ushort, 3, add, Add)
FUNC_CVALUE_INOUT_SCALE(short, 3, add, Add)
FUNC_CVALUE_INOUT_SCALE(float, 3, add, Add)

// static bool copy(In a, Out b);
FUNC_IN_OUT(uchar, 1, copy, Copy)
FUNC_IN_OUT(short, 1, copy, Copy)
FUNC_IN_OUT(ushort, 1, copy, Copy)
FUNC_IN_OUT(float, 1, copy, Copy)
FUNC_IN_OUT(int, 1, copy, Copy)


FUNC_COPYSUBPIXEL(uchar, 1, copySubpixel, CopySubpix) // ippi+.hpp
FUNC_COPYSUBPIXEL(ushort, 1, copySubpixel, CopySubpix)
FUNC_COPYSUBPIXEL(float, 1, copySubpixel, CopySubpix)
// no color'd version


// static bool copySubpixelToFloatBuffer(In a, WImageT<float,1> b);
FUNC_COPYSUBPIXEL_F(uchar, 1, copySubpixelToFloatBuffer, CopySubpix) // special case.
// no color'd version

// static bool div(const PixelValue& divisor, InOut b, int scaleFactor=0);
FUNC_CVALUE_INOUT_SCALE(uchar, 1, div, Div)
FUNC_CVALUE_INOUT_SCALE(short, 1, div, Div)
FUNC_CVALUE_INOUT_SCALE(ushort, 1, div, Div)
FUNC_CVALUE_INOUT_SCALE(uchar, 3, div, Div)
FUNC_CVALUE_INOUT_SCALE(short, 3, div, Div)
FUNC_CVALUE_INOUT_SCALE(ushort, 3, div, Div)

// static bool div(In a, const PixelValue& divsior, Out b);
FUNC_IN_CVALUE_OUT_SCALE(uchar, 1, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(short, 1, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(ushort, 1, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(float, 1, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(uchar, 3, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(short, 3, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(ushort, 3, div, Div)
FUNC_IN_CVALUE_OUT_SCALE(float, 3, div, Div)

// static bool div(In a, In b, Out c);
FUNC_IN_IN_OUT_SCALE(uchar, 1, div, Div)
FUNC_IN_IN_OUT_SCALE(short, 1, div, Div)
FUNC_IN_IN_OUT_SCALE(ushort, 1, div, Div)
FUNC_IN_IN_OUT_SCALE(float, 1, div, Div)
FUNC_IN_IN_OUT_SCALE(uchar, 3, div, Div)
FUNC_IN_IN_OUT_SCALE(short, 3, div, Div)
FUNC_IN_IN_OUT_SCALE(ushort, 3, div, Div)
FUNC_IN_IN_OUT_SCALE(float, 3, div, Div)

// static bool filter(In a, const Kernel3x3& b, Out c);
FILTER_IN_IKERNEL_OUT(uchar, 1, 3)
FILTER_IN_IKERNEL_OUT(ushort, 1, 3)
FILTER_IN_IKERNEL_OUT(short, 1, 3)
FILTER_IN_IKERNEL_OUT(uchar, 3, 3)
FILTER_IN_IKERNEL_OUT(ushort, 3, 3)
FILTER_IN_IKERNEL_OUT(short, 3, 3)

// static bool filter(In a, const Kernel5x5& b, Out c);
FILTER_IN_IKERNEL_OUT(uchar, 1, 5)
FILTER_IN_IKERNEL_OUT(ushort, 1, 5)
FILTER_IN_IKERNEL_OUT(short, 1, 5)
FILTER_IN_IKERNEL_OUT(uchar, 3, 5)
FILTER_IN_IKERNEL_OUT(ushort, 3, 5)
FILTER_IN_IKERNEL_OUT(short, 3, 5)

// static bool findMaxIntensity(In a, PixelPosPosition& value);
FUNC_IN_POS(uchar, 1, findMaxIntensity, MaxIndx)
FUNC_IN_POS(ushort, 1, findMaxIntensity, MaxIndx)
FUNC_IN_POS(short, 1, findMaxIntensity, MaxIndx)
FUNC_IN_POS(float, 1, findMaxIntensity, MaxIndx)
FUNC_IN_POS(uchar, 3, findMaxIntensity, MaxIndx)
FUNC_IN_POS(ushort, 3, findMaxIntensity, MaxIndx)
FUNC_IN_POS(short, 3, findMaxIntensity, MaxIndx)
FUNC_IN_POS(float, 3, findMaxIntensity, MaxIndx)

// static bool findMinIntensity(In a, PixelPosition& value);
FUNC_IN_POS(uchar, 1, findMinIntensity, MinIndx)
FUNC_IN_POS(ushort, 1, findMinIntensity, MinIndx)
FUNC_IN_POS(short, 1, findMinIntensity, MinIndx)
FUNC_IN_POS(float, 1, findMinIntensity, MinIndx)
FUNC_IN_POS(uchar, 3, findMinIntensity, MinIndx)
FUNC_IN_POS(ushort, 3, findMinIntensity, MinIndx)
FUNC_IN_POS(short, 3, findMinIntensity, MinIndx)
FUNC_IN_POS(float, 3, findMinIntensity, MinIndx)

// static bool calculateHistogram(In a, HistogramParameter& parameter, IntHistogramResult& result);
template<>
bool WImageProcess<uchar, 3>::calculateHistogram(In a,
												 IppHistogramParameter<3>& parameter,
												 WHistogramResult<int, 3>& result)
{
	result.resize(parameter.levelsCount());

	WImageBufferT<uchar, 3> inBuffer(640,480);
	WConstImageT<uchar, 3> inImage = inBuffer;
	IppHistogramParameter<3> ippParam = parameter;

	IPP_DEBUG(ippiHistogramRange_C3R(a, a.step(), a.ippRoiSize(),
									 result.getDataRef(),
									 ippParam.levels(),
									 ippParam.levelsCount()));
}

FUNC_RAMP(signed char, 1)
FUNC_RAMP(uchar, 1)
FUNC_RAMP(short, 1)
FUNC_RAMP(ushort, 1)
FUNC_RAMP(float, 1)
FUNC_RAMP(signed char, 3)
FUNC_RAMP(uchar, 3)
FUNC_RAMP(short, 3)
FUNC_RAMP(ushort, 3)
FUNC_RAMP(float, 3)

// static bool lut(InOut a, const LutData& data, Wf::LutMode mode=Linear);
FUNC_INOUT_LUT(uchar,1)
FUNC_INOUT_LUT(ushort,1)
FUNC_INOUT_LUT(short,1)
FUNC_INOUT_LUT(float,1)
FUNC_INOUT_LUT(uchar,3)
FUNC_INOUT_LUT(ushort,3)
FUNC_INOUT_LUT(short,3)
FUNC_INOUT_LUT(float,3)

// static bool lut(In a, Out b, const LutData& data, Wf::LutMode mode=Linear);
FUNC_IO_LUT(uchar, 1)
FUNC_IO_LUT(ushort, 1)
FUNC_IO_LUT(short, 1)
FUNC_IO_LUT(float, 1)
FUNC_IO_LUT(uchar, 3)
FUNC_IO_LUT(ushort, 3)
FUNC_IO_LUT(short, 3)
FUNC_IO_LUT(float, 3)

// static bool logical_and(In a, In b, Out c);
FUNC_IN_IN_OUT(uchar, 1, logical_and, And)
FUNC_IN_IN_OUT(ushort, 1, logical_and, And)
FUNC_IN_IN_OUT(int, 1, logical_and, And)
FUNC_IN_IN_OUT(uchar, 3, logical_and, And)
FUNC_IN_IN_OUT(ushort, 3, logical_and, And)
FUNC_IN_IN_OUT(int, 3, logical_and, And)

// static bool logical_and(T value, InOut b);
FUNC_CVALUE_INOUT(uchar, 1, logical_and, And)
FUNC_CVALUE_INOUT(ushort, 1, logical_and, And)
FUNC_CVALUE_INOUT(int, 1, logical_and, And)
FUNC_CVALUE_INOUT(uchar, 3, logical_and, And)
FUNC_CVALUE_INOUT(ushort, 3, logical_and, And)
FUNC_CVALUE_INOUT(int, 3, logical_and, And)

// static bool logical_and(In a, InOut b);
FUNC_IN_INOUT(uchar, 1, logical_and, And)
FUNC_IN_INOUT(ushort, 1, logical_and, And)
FUNC_IN_INOUT(int, 1, logical_and, And)
FUNC_IN_INOUT(uchar, 3, logical_and, And)
FUNC_IN_INOUT(ushort, 3, logical_and, And)
FUNC_IN_INOUT(int, 3, logical_and, And)

// static bool logical_or(In a, In b, Out c);
FUNC_IN_IN_OUT(uchar, 1, logical_or, Or)
FUNC_IN_IN_OUT(ushort, 1, logical_or, Or)
FUNC_IN_IN_OUT(int, 1, logical_or, Or)
FUNC_IN_IN_OUT(uchar, 3, logical_or, Or)
FUNC_IN_IN_OUT(ushort, 3, logical_or, Or)
FUNC_IN_IN_OUT(int, 3, logical_or, Or)

// static bool logical_or(T value, InOut b);
FUNC_CVALUE_INOUT(uchar, 1, logical_or, Or)
FUNC_CVALUE_INOUT(ushort, 1, logical_or, Or)
FUNC_CVALUE_INOUT(int, 1, logical_or, Or)
FUNC_CVALUE_INOUT(uchar, 3, logical_or, Or)
FUNC_CVALUE_INOUT(ushort, 3, logical_or, Or)
FUNC_CVALUE_INOUT(int, 3, logical_or, Or)

// static bool logical_or(In a, InOut b);
FUNC_IN_INOUT(uchar, 1, logical_or, Or)
FUNC_IN_INOUT(ushort, 1, logical_or, Or)
FUNC_IN_INOUT(int, 1, logical_or, Or)
FUNC_IN_INOUT(uchar, 3, logical_or, Or)
FUNC_IN_INOUT(ushort, 3, logical_or, Or)
FUNC_IN_INOUT(int, 3, logical_or, Or)

// static bool max(In a, PixelValue& value, max, Max);
FUNC_IN_VALUE(uchar, 1, max, Max)
FUNC_IN_VALUE(ushort, 1, max, Max)
FUNC_IN_VALUE(short, 1, max, Max)
FUNC_IN_VALUE(float, 1, max, Max)
FUNC_IN_VALUE(uchar, 3, max, Max)
FUNC_IN_VALUE(ushort, 3, max, Max)
FUNC_IN_VALUE(short, 3, max, Max)
FUNC_IN_VALUE(float, 3, max, Max)

// static bool maxEvery(In a, InOut b);
FUNC_IN_INOUT(uchar, 1, maxEvery, MaxEvery)
FUNC_IN_INOUT(ushort, 1, maxEvery, MaxEvery)
FUNC_IN_INOUT(float, 1, maxEvery, MaxEvery)
FUNC_IN_INOUT(uchar, 3, maxEvery, MaxEvery)
FUNC_IN_INOUT(ushort, 3, maxEvery, MaxEvery)
FUNC_IN_INOUT(float, 3, maxEvery, MaxEvery)

//static bool mean(In a, RealValue& value);
FUNC_IN_REAL(uchar, 1, mean, Mean)
FUNC_IN_REAL(ushort, 1, mean, Mean)
FUNC_IN_REAL(short, 1, mean, Mean)
FUNC_IN_REAL(float, 1, mean, Mean)
FUNC_IN_REAL(uchar, 3, mean, Mean)
FUNC_IN_REAL(ushort, 3, mean, Mean)
FUNC_IN_REAL(short, 3, mean, Mean)
FUNC_IN_REAL(float, 3, mean, Mean)

// static bool min(In a, PixelValue& value);
FUNC_IN_VALUE(uchar, 1, min, Min)
FUNC_IN_VALUE(ushort, 1, min, Min)
FUNC_IN_VALUE(short, 1, min, Min)
FUNC_IN_VALUE(float, 1, min, Min)
FUNC_IN_VALUE(uchar, 3, min, Min)
FUNC_IN_VALUE(ushort, 3, min, Min)
FUNC_IN_VALUE(short, 3, min, Min)
FUNC_IN_VALUE(float, 3, min, Min)

// static bool minEvery(In a, InOut b);
FUNC_IN_INOUT(uchar, 1, minEvery, MinEvery)
FUNC_IN_INOUT(ushort, 1, minEvery, MinEvery)
FUNC_IN_INOUT(float, 1, minEvery, MinEvery)
FUNC_IN_INOUT(uchar, 3, minEvery, MinEvery)
FUNC_IN_INOUT(ushort, 3, minEvery, MinEvery)
FUNC_IN_INOUT(float, 3, minEvery, MinEvery)

//static bool minMax(In a, PixelValueRange& value);
FUNC_IN_RANGE(uchar, 1, minMax, MinMax)
FUNC_IN_RANGE(ushort, 1, minMax, MinMax)
FUNC_IN_RANGE(short, 1, minMax, MinMax)
FUNC_IN_RANGE(float, 1, minMax, MinMax)
FUNC_IN_RANGE(uchar, 3, minMax, MinMax)
FUNC_IN_RANGE(ushort, 3, minMax, MinMax)
FUNC_IN_RANGE(short, 3, minMax, MinMax)
FUNC_IN_RANGE(float, 3, minMax, MinMax)

//static bool mirror(InOut a, Wf::Direction direction);
FUNC_INOUT_DIR(uchar, 1, mirror, Mirror)
FUNC_INOUT_DIR(ushort, 1, mirror, Mirror)
FUNC_INOUT_DIR(short, 1, mirror, Mirror)
FUNC_INOUT_DIR(int, 1, mirror, Mirror)
FUNC_INOUT_DIR(float, 1, mirror, Mirror)
FUNC_INOUT_DIR(uchar, 3, mirror, Mirror)
FUNC_INOUT_DIR(ushort, 3, mirror, Mirror)
FUNC_INOUT_DIR(short, 3, mirror, Mirror)
FUNC_INOUT_DIR(int, 3, mirror, Mirror)
FUNC_INOUT_DIR(float, 3, mirror, Mirror)

// static bool mul(const PixelValue& multiplier, InOut b, int scaleFactor=0);
FUNC_CVALUE_INOUT_SCALE(uchar, 1, mul, Mul)
FUNC_CVALUE_INOUT_SCALE(short, 1, mul, Mul)
FUNC_CVALUE_INOUT_SCALE(ushort, 1, mul, Mul)
FUNC_CVALUE_INOUT_SCALE(uchar, 3, mul, Mul)
FUNC_CVALUE_INOUT_SCALE(short, 3, mul, Mul)
FUNC_CVALUE_INOUT_SCALE(ushort, 3, mul, Mul)

// static bool mul(In a, const PixelValue& multiplier, Out b);
FUNC_IN_CVALUE_OUT_SCALE(uchar, 1, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(short, 1, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(ushort, 1, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(float, 1, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(uchar, 3, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(short, 3, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(ushort, 3, mul, Mul)
FUNC_IN_CVALUE_OUT_SCALE(float, 3, mul, Mul)

// static bool mul(In a, In b, Out c);
FUNC_IN_IN_OUT_SCALE(uchar, 1, mul, Mul)
FUNC_IN_IN_OUT_SCALE(short, 1, mul, Mul)
FUNC_IN_IN_OUT_SCALE(ushort, 1, mul, Mul)
FUNC_IN_IN_OUT_SCALE(float, 1, mul, Mul)
FUNC_IN_IN_OUT_SCALE(uchar, 3, mul, Mul)
FUNC_IN_IN_OUT_SCALE(short, 3, mul, Mul)
FUNC_IN_IN_OUT_SCALE(ushort, 3, mul, Mul)
FUNC_IN_IN_OUT_SCALE(float, 3, mul, Mul)

// static bool resize(In a, Out c)
FUNC_IN_OUT_INTER_CVRESIZE(uchar, 1, resize)
FUNC_IN_OUT_INTER_CVRESIZE(short, 1, resize)
FUNC_IN_OUT_INTER_CVRESIZE(ushort, 1, resize)
FUNC_IN_OUT_INTER_CVRESIZE(float, 1, resize)
FUNC_IN_OUT_INTER_CVRESIZE(uchar, 3, resize)
FUNC_IN_OUT_INTER_CVRESIZE(short, 3, resize)
FUNC_IN_OUT_INTER_CVRESIZE(ushort, 3, resize)
FUNC_IN_OUT_INTER_CVRESIZE(float, 3, resize)

// static bool set(const PixelValue& a, Out b);
FUNC_CVALUE_OUT(uchar, 1, set, Set)
FUNC_CVALUE_OUT(ushort, 1, set, Set)
FUNC_CVALUE_OUT(short, 1, set, Set)
FUNC_CVALUE_OUT(int, 1, set, Set)
FUNC_CVALUE_OUT(float, 1, set, Set)
FUNC_CVALUE_OUT(uchar, 3, set, Set)
FUNC_CVALUE_OUT(ushort, 3, set, Set)
FUNC_CVALUE_OUT(short, 3, set, Set)
FUNC_CVALUE_OUT(int, 3, set, Set)
FUNC_CVALUE_OUT(float, 3, set, Set)

// static bool sqr(In a, Out b, int scaleFactor=0);
FUNC_IN_OUT_SCALE(uchar, 1, sqr, Sqr)
FUNC_IN_OUT_SCALE(ushort, 1, sqr, Sqr)
FUNC_IN_OUT_SCALE(short, 1, sqr, Sqr)
FUNC_IN_OUT_SCALE(float, 1, sqr, Sqr)
FUNC_IN_OUT_SCALE(uchar, 3, sqr, Sqr)
FUNC_IN_OUT_SCALE(ushort, 3, sqr, Sqr)
FUNC_IN_OUT_SCALE(short, 3, sqr, Sqr)
FUNC_IN_OUT_SCALE(float, 3, sqr, Sqr)

// static bool sqr(InOut a, int scaleFactor=0);
FUNC_INOUT_SCALE(uchar, 1, sqr, Sqr)
FUNC_INOUT_SCALE(ushort, 1, sqr, Sqr)
FUNC_INOUT_SCALE(short, 1, sqr, Sqr)
FUNC_INOUT_SCALE(float, 1, sqr, Sqr)
FUNC_INOUT_SCALE(uchar, 3, sqr, Sqr)
FUNC_INOUT_SCALE(ushort, 3, sqr, Sqr)
FUNC_INOUT_SCALE(short, 3, sqr, Sqr)
FUNC_INOUT_SCALE(float, 3, sqr, Sqr)

// static bool sqrt(In a, Out b, int scaleFactor=0);
FUNC_IN_OUT_SCALE(uchar, 1, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(ushort, 1, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(short, 1, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(float, 1, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(uchar, 3, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(ushort, 3, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(short, 3, sqrt, Sqrt)
FUNC_IN_OUT_SCALE(float, 3, sqrt, Sqrt)

// static bool sqrt(InOut a, int scaleFactor=0);
FUNC_INOUT_SCALE(uchar, 1, sqrt, Sqrt)
FUNC_INOUT_SCALE(ushort, 1, sqrt, Sqrt)
FUNC_INOUT_SCALE(short, 1, sqrt, Sqrt)
FUNC_INOUT_SCALE(float, 1, sqrt, Sqrt)
FUNC_INOUT_SCALE(uchar, 3, sqrt, Sqrt)
FUNC_INOUT_SCALE(ushort, 3, sqrt, Sqrt)
FUNC_INOUT_SCALE(short, 3, sqrt, Sqrt)
FUNC_INOUT_SCALE(float, 3, sqrt, Sqrt)

// static bool sub(In a, In b, Out c, int scaleFactor);
FUNC_IN_IN_OUT_SCALE(uchar, 1, sub, Sub)
FUNC_IN_IN_OUT_SCALE(ushort, 1, sub, Sub)
FUNC_IN_IN_OUT_SCALE(short, 1, sub, Sub)
FUNC_IN_IN_OUT_SCALE(uchar, 3, sub, Sub)
FUNC_IN_IN_OUT_SCALE(ushort, 3, sub, Sub)
FUNC_IN_IN_OUT_SCALE(short, 3, sub, Sub)

// static bool sub(In a, InOut b, int scaleFactor=0);
FUNC_IN_INOUT_SCALE(uchar, 1, sub, Sub)
FUNC_IN_INOUT_SCALE(ushort, 1, sub, Sub)
FUNC_IN_INOUT_SCALE(short, 1, sub, Sub)
FUNC_IN_INOUT_SCALE(uchar, 3, sub, Sub)
FUNC_IN_INOUT_SCALE(ushort, 3, sub, Sub)
FUNC_IN_INOUT_SCALE(short, 3, sub, Sub)

// static bool sub(const PixelValue& valueToBeSubtracted, InOut b, int scaleFator=0);
FUNC_CVALUE_INOUT_SCALE(uchar, 1, subValueFromImage, Sub)
FUNC_CVALUE_INOUT_SCALE(ushort, 1, subValueFromImage, Sub)
FUNC_CVALUE_INOUT_SCALE(short, 1, subValueFromImage, Sub)
FUNC_CVALUE_INOUT_SCALE(uchar, 3, subValueFromImage, Sub)
FUNC_CVALUE_INOUT_SCALE(ushort, 3, subValueFromImage, Sub)
FUNC_CVALUE_INOUT_SCALE(short, 3, subValueFromImage, Sub)

// static bool sum(In a, RealValue& value);
FUNC_IN_REAL(uchar, 1, sum, Sum)
FUNC_IN_REAL(ushort, 1, sum, Sum)
FUNC_IN_REAL(short, 1, sum, Sum)
FUNC_IN_REAL(float, 1, sum, Sum)
FUNC_IN_REAL(uchar, 3, sum, Sum)
FUNC_IN_REAL(ushort, 3, sum, Sum)
FUNC_IN_REAL(short, 3, sum, Sum)
FUNC_IN_REAL(float, 3, sum, Sum)

// @@@

// NOTE: among ipp's image format conversion. following conversion functions are NOT USED
//       TODO IMPORVE ME
// ippiConvert_C1R( unsigned int pSrcDst, int srcDstStep, IppiSize roi, IppRoundMode roundMode, int scaleFactor)
// ippiConvert_C1R(uchar, uchar pDst, int dstStep, int dstBitOffset, IppiSize roiSize, Ipp8u threshold)
// ippiConvert_C1R(uchar, int srcBitOffset, uchar)
// ippiConvert_C1Rs(short, ushort)
// ippiConvert_C1Rs(short, unsigned int)
// ippiConvert_C1Rs(int, unsigned int)
// ippiConvert_C1Rs(signed char, ushort)
// ippiConvert_C1Rs(signed char, unsigned int)
// ippiConvert_C1Rs(signed char, uchar)

FUNC_CONVERT(int,float,1,convertTo,Convert)
FUNC_CONVERT(int,signed char,1,convertTo,Convert)
FUNC_CONVERT(int,signed char,3,convertTo,Convert)
FUNC_CONVERT(int,uchar,1,convertTo,Convert)
FUNC_CONVERT(int,uchar,3,convertTo,Convert)
FUNC_CONVERT(short,float,1,convertTo,Convert)
FUNC_CONVERT(short,float,3,convertTo,Convert)
FUNC_CONVERT(short,int,1,convertTo,Convert)
FUNC_CONVERT(short,int,3,convertTo,Convert)
FUNC_CONVERT(short,uchar,1,convertTo,Convert)
FUNC_CONVERT(short,uchar,3,convertTo,Convert)
FUNC_CONVERT(signed char,float,1,convertTo,Convert)
FUNC_CONVERT(signed char,float,3,convertTo,Convert)
FUNC_CONVERT(signed char,int,1,convertTo,Convert)
FUNC_CONVERT(signed char,int,3,convertTo,Convert)
FUNC_CONVERT(signed char,short,1,convertTo,Convert)
FUNC_CONVERT(uchar,float,1,convertTo,Convert)
FUNC_CONVERT(uchar,float,3,convertTo,Convert)
FUNC_CONVERT(uchar,int,1,convertTo,Convert)
FUNC_CONVERT(uchar,int,3,convertTo,Convert)
FUNC_CONVERT(uchar,short,1,convertTo,Convert)
FUNC_CONVERT(uchar,short,3,convertTo,Convert)
FUNC_CONVERT(uchar,ushort,1,convertTo,Convert)
FUNC_CONVERT(uchar,ushort,3,convertTo,Convert)
FUNC_CONVERT(unsigned int,float,1,convertTo,Convert)
FUNC_CONVERT(ushort,float,1,convertTo,Convert)
FUNC_CONVERT(ushort,float,3,convertTo,Convert)
FUNC_CONVERT(ushort,int,1,convertTo,Convert)
FUNC_CONVERT(ushort,int,3,convertTo,Convert)
FUNC_CONVERT(ushort,uchar,1,convertTo,Convert)
FUNC_CONVERT(ushort,uchar,3,convertTo,Convert)
FUNC_CONVERT(ushort,unsigned int,1,convertTo,Convert)

FUNC_CONVERT_ROUND(float, int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, short, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, signed char, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, uchar, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, unsigned int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, ushort, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, float, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, short, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, signed char, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, uchar, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, ushort, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, float, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, signed char, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, uchar, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(signed char, float, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(signed char, int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(signed char, short, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, float, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, short, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, signed char, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, ushort, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(unsigned int, float, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(unsigned int, int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(unsigned int, short, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(unsigned int, signed char, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(unsigned int, uchar, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(unsigned int, ushort, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, float, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, short, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, signed char, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, uchar, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, unsigned int, 1, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, short, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, signed char, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, uchar, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(float, ushort, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, signed char, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(int, uchar, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, float, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, int, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(short, uchar, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(signed char, float, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(signed char, int, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, float, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, int, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, short, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(uchar, ushort, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, float, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, int, 3, convertTo, Convert__)
FUNC_CONVERT_ROUND(ushort, uchar, 3, convertTo, Convert__)

FUNC_CONVERT_ROUND_SCALE( short, signed char, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( ushort, short, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( ushort, signed char, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( float, short, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( float, ushort, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( float, int, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( float, unsigned int, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( float, signed char, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( float, uchar, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( int, short, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( int, ushort, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( unsigned int, short, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( unsigned int, ushort, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( unsigned int, int, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( unsigned int, signed char, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( unsigned int, uchar, 1, convertTo, Convert)
FUNC_CONVERT_ROUND_SCALE( uchar, signed char, 1, convertTo, Convert)
