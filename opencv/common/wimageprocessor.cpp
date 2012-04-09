#include "wimageprocessor.h"

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

} // nonamed namespace

// [signature naming convention]
// O : Out
// I : In
// P : Inout
// M : IppRoundMode
// K : Constant value (single value despite of channel count!)
// V : Constant value array(considering channel count!)
// S : ScaleFactor 2^(-n) used in IPP
// F : special float buffer with same channel count = WImageT<float,C>
// for example
//   - IIO-->In,In,Out
//   - IP -->In,InOut
//   ...
#define FUNC_IIO(TYPE,CHAN,MEMBER_NAME,IPP_NAME)						\
	template<> void														\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c)			\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(),												\
			 c, c.step(), c.ippRoiSize());								\
	}

// template<> void
// WImageProcess<short,1>::abs(InOut a)
// {
// 	IPPIP::ippiAbs_C1R(a, a.step(), a.ippRoiSize());
// }

#define FUNC_IIOS(TYPE,CHAN,MEMBER_NAME,IPP_NAME)						\
	template<> void														\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c,			\
										  int scaleFactor)				\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(),												\
			 c, c.step(), c.ippRoiSize(),								\
			 scaleFactor);												\
	}

#define FUNC_IIOS_NOSCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)				\
	template<> void														\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c,			\
										  int scaleFactor)				\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(),												\
			 c, c.step(), c.ippRoiSize());								\
	}

#define FUNC_IPS(TYPE,CHAN,MEMBER_NAME,IPP_NAME)						\
	template<> void														\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, InOut b,				\
										  int scaleFactor)				\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize(),								\
			 scaleFactor);												\
	}

#define FUNC_IPS_NOSCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)				\
	template<> void														\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, InOut b,				\
										  int scaleFactor)				\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize());								\
	}

#define FUNC_P(TYPE,CHAN,MEMBER_NAME,IPP_NAME)		\
	template<> void									\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(InOut a)	\
	{												\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R			\
			(a, a.step(), a.ippRoiSize());			\
	}

#define FUNC_IO(TYPE,CHAN,MEMBER_NAME,IPP_NAME)				\
	template<>												\
	void WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, Out b)	\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(),									\
			 b, b.step(), b.ippRoiSize());					\
	}

#define FUNC_VP_1(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,1>					\
	::MEMBER_NAME(const ValueArray& a, InOut b)	\
	{											\
		IPPIP::ippi##IPP_NAME##_C1R				\
			(a[0],								\
			 b, b.step(), b.ippRoiSize());		\
	}

#define FUNC_VP_3(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,3>					\
	::MEMBER_NAME(const ValueArray& a, InOut b)	\
	{											\
		IPPIP::ippi##IPP_NAME##_C3R				\
			(&a[0],								\
			 b, b.step(), b.ippRoiSize());		\
	}

#define FUNC_VPS_1(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,1>					\
	::MEMBER_NAME(const ValueArray& a, InOut b,	\
				  int scaleFactor)				\
	{											\
		IPPIP::ippi##IPP_NAME##_C1R				\
			(a[0],								\
			 b, b.step(), b.ippRoiSize(),		\
			 scaleFactor);						\
	}

#define FUNC_VPS_3(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,3>					\
	::MEMBER_NAME(const ValueArray& a, InOut b,	\
				  int scaleFactor)				\
	{											\
		IPPIP::ippi##IPP_NAME##_C3R				\
			(&a[0],								\
			 b, b.step(), b.ippRoiSize(),		\
			 scaleFactor);						\
	}


#define FUNC_VPS_1_NOSCALE(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,1>					\
	::MEMBER_NAME(const ValueArray& a, InOut b,	\
				  int scaleFactor)				\
	{											\
		IPPIP::ippi##IPP_NAME##_C1R				\
			(a[0],								\
			 b, b.step(), b.ippRoiSize());		\
	}

#define FUNC_VPS_3_NOSCALE(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,3>					\
	::MEMBER_NAME(const ValueArray& a, InOut b,	\
				  int scaleFactor)				\
	{											\
		IPPIP::ippi##IPP_NAME##_C3R				\
			(&a[0],								\
			 b, b.step(), b.ippRoiSize());		\
	}

#define FUNC_IVOS_1(TYPE,MEMBER_NAME,IPP_NAME)		\
	template<>										\
	void WImageProcess<TYPE,1>						\
	::MEMBER_NAME(In a, const ValueArray& v, Out b,	\
				  int scaleFactor)					\
	{												\
		IPPIP::ippi##IPP_NAME##_C1R					\
			(a, a.step(), 							\
			 v[0],									\
			 b, b.step(), b.ippRoiSize(),			\
			 scaleFactor);							\
	}

#define FUNC_IVOS_1_NOSCALE(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>										\
	void WImageProcess<TYPE,1>						\
	::MEMBER_NAME(In a, const ValueArray& v, Out b,	\
				  int scaleFactor)					\
	{												\
		IPPIP::ippi##IPP_NAME##_C1R					\
			(a, a.step(), 							\
			 v[0],									\
			 b, b.step(), b.ippRoiSize());			\
	}

#define FUNC_IVOS_3(TYPE,MEMBER_NAME,IPP_NAME)		\
	template<>										\
	void WImageProcess<TYPE,3>						\
	::MEMBER_NAME(In a, const ValueArray& v, Out b,	\
				  int scaleFactor)					\
	{												\
		IPPIP::ippi##IPP_NAME##_C3R					\
			(a, a.step(),							\
			 &v[0],									\
			 b, b.step(), b.ippRoiSize(),			\
			 scaleFactor);							\
	}

#define FUNC_IVOS_3_NOSCALE(TYPE,MEMBER_NAME,IPP_NAME)	\
	template<>										\
	void WImageProcess<TYPE,3>						\
	::MEMBER_NAME(In a, const ValueArray& v, Out b,	\
				  int scaleFactor)					\
	{												\
		IPPIP::ippi##IPP_NAME##_C3R					\
			(a, a.step(), 							\
			 &v[0],									\
			 b, b.step(), b.ippRoiSize());			\
	}


#define FUNC_IP(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>									\
	void WImageProcess<TYPE,CHAN>				\
	::MEMBER_NAME(In a, InOut b)				\
	{											\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R		\
			(a, a.step(),						\
			 b, b.step(), b.ippRoiSize());		\
	}

// static void abs(In a, In b, Out c);
FUNC_P(short, 1, abs, Abs)
FUNC_P(float, 1, abs, Abs)
FUNC_P(short, 3, abs, Abs)
FUNC_P(float, 3, abs, Abs)
FUNC_IO(short, 1, abs, Abs)
FUNC_IO(float, 1, abs, Abs)
FUNC_IO(short, 3, abs, Abs)
FUNC_IO(float, 3, abs, Abs)

// static void absDiff(In a, In b, Out c);
FUNC_IIO(uchar, 1, absDiff, AbsDiff)
FUNC_IIO(uchar, 3, absDiff, AbsDiff)

// static void add(In a, In b, Out c);
FUNC_IP(float, 1, add, Add)
FUNC_IP(float, 3, add, Add)

// static void add(In a, In b, Out c, int scaleFactor=0);
FUNC_IIOS(uchar, 1, add, Add)
FUNC_IIOS(ushort, 1, add, Add)
FUNC_IIOS(short, 1, add, Add)
FUNC_IIOS(uchar, 3, add, Add)
FUNC_IIOS(ushort, 3, add, Add)
FUNC_IIOS(short, 3, add, Add)

// static void add(In a, In b, Out c, int scaleFactor=0);
FUNC_IPS(uchar, 1, add, Add)
FUNC_IPS(ushort, 1, add, Add)
FUNC_IPS(short, 1, add, Add)
FUNC_IPS(uchar, 3, add, Add)
FUNC_IPS(ushort, 3, add, Add)
FUNC_IPS(short, 3, add, Add)

// static void add(const ValueArray& a, InOut b, int scaleFator=0);
FUNC_VPS_1(uchar, add, Add)
FUNC_VPS_1(ushort, add, Add)
FUNC_VPS_1(short, add, Add)
FUNC_VPS_1_NOSCALE(float, add, Add)
FUNC_VPS_3(uchar, add, Add)
FUNC_VPS_3(ushort, add, Add)
FUNC_VPS_3(short, add, Add)
FUNC_VPS_3_NOSCALE(float, add, Add)

// static void copy(In a, Out b);
FUNC_IO(uchar, 1, copy, Copy)
FUNC_IO(short, 1, copy, Copy)
FUNC_IO(ushort, 1, copy, Copy)
FUNC_IO(float, 1, copy, Copy)
FUNC_IO(int, 1, copy, Copy)

// static void copySubpixel(In a, Out b);
#define FUNC_COPYSUBPIXEL(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	void WImageProcess<TYPE,CHAN>							\
	::MEMBER_NAME(In a, Out b)								\
	{														\
		const QPointF& fractional							\
			= a.roiTopLeftFractionalPart();					\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(),									\
			 b, b.step(), b.ippRoiSize(),					\
			 fractional.x(), fractional.y());				\
	}

FUNC_COPYSUBPIXEL(uchar, 1, copySubpixel, CopySubpix) // ippi+.hpp
FUNC_COPYSUBPIXEL(ushort, 1, copySubpixel, CopySubpix)
FUNC_COPYSUBPIXEL(float, 1, copySubpixel, CopySubpix)
// no color'd version

#define FUNC_COPYSUBPIXEL_F(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	void WImageProcess<TYPE,CHAN>							\
	::MEMBER_NAME(In a, WImageT<float,CHAN> b)				\
	{														\
		const QPointF& fractional							\
			= a.roiTopLeftFractionalPart();					\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(),									\
			 b, b.step(), b.ippRoiSize(),					\
			 fractional.x(), fractional.y());				\
	}

// static void copySubpixelToFloatBuffer(In a, WImageT<float,1> b);
FUNC_COPYSUBPIXEL_F(uchar, 1, copySubpixelToFloatBuffer, CopySubpix) // special case.
// no color'd version

// static void div(const ValueArray& divisor, InOut b, int scaleFactor=0);
FUNC_VPS_1(uchar, div, Div)
FUNC_VPS_1(short, div, Div)
FUNC_VPS_1(ushort, div, Div)
FUNC_VPS_3(uchar, div, Div)
FUNC_VPS_3(short, div, Div)
FUNC_VPS_3(ushort, div, Div)

// static void div(In a, const ValueArray& divsior, Out b);
FUNC_IVOS_1(uchar, div, Div)
FUNC_IVOS_1(short, div, Div)
FUNC_IVOS_1(ushort, div, Div)
FUNC_IVOS_1_NOSCALE(float, div, Div)
FUNC_IVOS_3(uchar, div, Div)
FUNC_IVOS_3(short, div, Div)
FUNC_IVOS_3(ushort, div, Div)
FUNC_IVOS_3_NOSCALE(float, div, Div)

// static void div(In a, In b, Out c);
FUNC_IIOS(uchar, 1, div, Div)
FUNC_IIOS(short, 1, div, Div)
FUNC_IIOS(ushort, 1, div, Div)
FUNC_IIOS_NOSCALE(float, 1, div, Div)
FUNC_IIOS(uchar, 3, div, Div)
FUNC_IIOS(short, 3, div, Div)
FUNC_IIOS(ushort, 3, div, Div)
FUNC_IIOS_NOSCALE(float, 3, div, Div)

#define FUNC_I_PIXELPOS(TYPE,CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>												\
	void WImageProcess<TYPE,CHAN>::							\
	MEMBER_NAME(In a, PixelPosition& value)					\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(), a.ippRoiSize(),					\
			 value.getDataPtr(),							\
			 value.getXPtr(),								\
			 value.getYPtr());								\
	}

// static void findMaxIntensity(In a, PixelPosPosition& value);
FUNC_I_PIXELPOS(uchar, 1, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(ushort, 1, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(short, 1, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(float, 1, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(uchar, 3, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(ushort, 3, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(short, 3, findMaxIntensity, MaxIndx)
FUNC_I_PIXELPOS(float, 3, findMaxIntensity, MaxIndx)

// static void findMinIntensity(In a, PixelPosition& value);
FUNC_I_PIXELPOS(uchar, 1, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(ushort, 1, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(short, 1, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(float, 1, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(uchar, 3, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(ushort, 3, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(short, 3, findMinIntensity, MinIndx)
FUNC_I_PIXELPOS(float, 3, findMinIntensity, MinIndx)


//static void ramp(Out a, float offset, float slope, IppiAxis axis);
#define FUNC_RAMP(TYPE,CHAN)					\
	template<>									\
	void WImageProcess<TYPE,CHAN>::				\
	ramp(Out a, float offset, float slope,		\
		 Wf::Direction dir)						\
	{											\
		IppiAxis axis = Dir2IppAxis(dir);		\
		IPPIP::ippiImageRamp_C##CHAN##R			\
			(a, a.step(), a.ippRoiSize(),		\
			 offset, slope, axis);				\
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

#define FUNC_P_LUT(TYPE,CHAN)											\
	template<>															\
		void WImageProcess<TYPE,CHAN>::									\
	lut(InOut a, const LutData& data, Wf::LutMode mode)					\
	{																	\
		LutData::ValueArrayType levels; data.getValuesIn(levels);		\
		LutData::ValueArrayType values; data.getValuesOut(values);		\
		LutData::CountArrayType counts; data.getCount(counts);			\
		switch (mode)													\
		{																\
		case Wf::Plain:													\
			IPPIP::ippiLUT_C##CHAN##R									\
				(a, a.step(), a.ippRoiSize(),							\
				 levels, values, counts);								\
			break;														\
		case Wf::Linear:												\
			IPPIP::ippiLUT_Linear_C##CHAN##R							\
				(a, a.step(), a.ippRoiSize(),							\
				 levels, values, counts);								\
			break;														\
		case Wf::Cubic:													\
			IPPIP::ippiLUT_Cubic_C##CHAN##R								\
				(a, a.step(), a.ippRoiSize(),							\
				 levels, values, counts);								\
			break;														\
		}																\
	}

// static void lut(InOut a, const LutData& data, Wf::LutMode mode=Linear);
FUNC_P_LUT(uchar,1)
FUNC_P_LUT(ushort,1)
FUNC_P_LUT(short,1)
FUNC_P_LUT(float,1)
FUNC_P_LUT(uchar,3)
FUNC_P_LUT(ushort,3)
FUNC_P_LUT(short,3)
FUNC_P_LUT(float,3)

#define FUNC_IO_LUT(TYPE,CHAN)										\
	template<>														\
	void WImageProcess<TYPE,CHAN>::									\
	lut(In a, Out b, const LutData& data, Wf::LutMode mode)			\
	{																\
		LutData::ValueArrayType levels; data.getValuesIn(levels);	\
		LutData::ValueArrayType values; data.getValuesOut(values);	\
		LutData::CountArrayType counts; data.getCount(counts);		\
		switch (mode)												\
		{															\
		case Wf::Plain:												\
			IPPIP::ippiLUT_C##CHAN##R								\
				(a, a.step(),										\
				 b, b.step(), b.ippRoiSize(),						\
				 levels, values, counts);							\
				break;												\
		case Wf::Linear:											\
			IPPIP::ippiLUT_Linear_C##CHAN##R						\
				(a, a.step(),										\
				 b, b.step(), b.ippRoiSize(),						\
				 levels, values, counts);							\
				break;												\
		case Wf::Cubic:												\
			IPPIP::ippiLUT_Cubic_C##CHAN##R							\
				(a, a.step(),										\
				 b, b.step(), b.ippRoiSize(),						\
				 levels, values, counts);							\
				break;												\
		}															\
	}

// static void lut(In a, Out b, const LutData& data, Wf::LutMode mode=Linear);
FUNC_IO_LUT(uchar, 1)
FUNC_IO_LUT(ushort, 1)
FUNC_IO_LUT(short, 1)
FUNC_IO_LUT(float, 1)
FUNC_IO_LUT(uchar, 3)
FUNC_IO_LUT(ushort, 3)
FUNC_IO_LUT(short, 3)
FUNC_IO_LUT(float, 3)

// static void logical_and(In a, In b, Out c);
FUNC_IIO(uchar, 1, logical_and, And)
FUNC_IIO(ushort, 1, logical_and, And)
FUNC_IIO(int, 1, logical_and, And)
FUNC_IIO(uchar, 3, logical_and, And)
FUNC_IIO(ushort, 3, logical_and, And)
FUNC_IIO(int, 3, logical_and, And)

// static void logical_and(T value, InOut b);
FUNC_VP_1(uchar, logical_and, And)
FUNC_VP_1(ushort, logical_and, And)
FUNC_VP_1(int, logical_and, And)
FUNC_VP_3(uchar, logical_and, And)
FUNC_VP_3(ushort, logical_and, And)
FUNC_VP_3(int, logical_and, And)

// static void logical_and(In a, InOut b);
FUNC_IP(uchar, 1, logical_and, And)
FUNC_IP(ushort, 1, logical_and, And)
FUNC_IP(int, 1, logical_and, And)
FUNC_IP(uchar, 3, logical_and, And)
FUNC_IP(ushort, 3, logical_and, And)
FUNC_IP(int, 3, logical_and, And)

// static void logical_or(In a, In b, Out c);
FUNC_IIO(uchar, 1, logical_or, Or)
FUNC_IIO(ushort, 1, logical_or, Or)
FUNC_IIO(int, 1, logical_or, Or)
FUNC_IIO(uchar, 3, logical_or, Or)
FUNC_IIO(ushort, 3, logical_or, Or)
FUNC_IIO(int, 3, logical_or, Or)

// static void logical_or(T value, InOut b);
FUNC_VP_1(uchar, logical_or, Or)
FUNC_VP_1(ushort, logical_or, Or)
FUNC_VP_1(int, logical_or, Or)
FUNC_VP_3(uchar, logical_or, Or)
FUNC_VP_3(ushort, logical_or, Or)
FUNC_VP_3(int, logical_or, Or)

// static void logical_or(In a, InOut b);
FUNC_IP(uchar, 1, logical_or, Or)
FUNC_IP(ushort, 1, logical_or, Or)
FUNC_IP(int, 1, logical_or, Or)
FUNC_IP(uchar, 3, logical_or, Or)
FUNC_IP(ushort, 3, logical_or, Or)
FUNC_IP(int, 3, logical_or, Or)


#define FUNC_I_PIXEL(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelValue& value)				\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(), a.ippRoiSize(),				\
			 value.getDataPtr());						\
	}

// static void max(In a, PixelValue& value, max, Max);
FUNC_I_PIXEL(uchar, 1, max, Max)
FUNC_I_PIXEL(ushort, 1, max, Max)
FUNC_I_PIXEL(short, 1, max, Max)
FUNC_I_PIXEL(float, 1, max, Max)
FUNC_I_PIXEL(uchar, 3, max, Max)
FUNC_I_PIXEL(ushort, 3, max, Max)
FUNC_I_PIXEL(short, 3, max, Max)
FUNC_I_PIXEL(float, 3, max, Max)

// static void maxEvery(In a, InOut b);
FUNC_IP(uchar, 1, maxEvery, MaxEvery)
FUNC_IP(ushort, 1, maxEvery, MaxEvery)
FUNC_IP(float, 1, maxEvery, MaxEvery)
FUNC_IP(uchar, 3, maxEvery, MaxEvery)
FUNC_IP(ushort, 3, maxEvery, MaxEvery)
FUNC_IP(float, 3, maxEvery, MaxEvery)

#define FUNC_I_DBL(TYPE,CHAN)									\
	template<>													\
	void WImageProcess<TYPE,CHAN>::mean(In a, MeanValue& value)	\
	{															\
		IPPIP::ippiMean_C##CHAN##R								\
			(a, a.step(), a.ippRoiSize(),						\
			 value.getDataPtr());								\
	}

//static void mean(In a, MeanValue& value);
FUNC_I_DBL(uchar, 1)
FUNC_I_DBL(ushort, 1)
FUNC_I_DBL(short, 1)
FUNC_I_DBL(float, 1)
FUNC_I_DBL(uchar, 3)
FUNC_I_DBL(ushort, 3)
FUNC_I_DBL(short, 3)
FUNC_I_DBL(float, 3)

// static void min(In a, PixelValue& value);
FUNC_I_PIXEL(uchar, 1, min, Min)
FUNC_I_PIXEL(ushort, 1, min, Min)
FUNC_I_PIXEL(short, 1, min, Min)
FUNC_I_PIXEL(float, 1, min, Min)
FUNC_I_PIXEL(uchar, 3, min, Min)
FUNC_I_PIXEL(ushort, 3, min, Min)
FUNC_I_PIXEL(short, 3, min, Min)
FUNC_I_PIXEL(float, 3, min, Min)

// static void minEvery(In a, InOut b);
FUNC_IP(uchar, 1, minEvery, MinEvery)
FUNC_IP(ushort, 1, minEvery, MinEvery)
FUNC_IP(float, 1, minEvery, MinEvery)
FUNC_IP(uchar, 3, minEvery, MinEvery)
FUNC_IP(ushort, 3, minEvery, MinEvery)
FUNC_IP(float, 3, minEvery, MinEvery)

#define FUNC_I_PIXELRANGE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	void WImageProcess<TYPE,CHAN>::							\
	MEMBER_NAME(In a, PixelValueRange& range)				\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(), a.ippRoiSize(),					\
			 range.min.getDataPtr(),						\
			 range.max.getDataPtr());						\
	}														\

//static void minMax(In a, PixelValueRange& value);
FUNC_I_PIXELRANGE(uchar, 1, minMax, MinMax)
FUNC_I_PIXELRANGE(ushort, 1, minMax, MinMax)
FUNC_I_PIXELRANGE(short, 1, minMax, MinMax)
FUNC_I_PIXELRANGE(float, 1, minMax, MinMax)
FUNC_I_PIXELRANGE(uchar, 3, minMax, MinMax)
FUNC_I_PIXELRANGE(ushort, 3, minMax, MinMax)
FUNC_I_PIXELRANGE(short, 3, minMax, MinMax)
FUNC_I_PIXELRANGE(float, 3, minMax, MinMax)

#define FUNC_P_DIR(TYPE,CHAN,MEMBER_NAME, IPP_NAME)	\
	template<>										\
	void WImageProcess<TYPE,CHAN>::					\
	MEMBER_NAME(InOut a, Wf::Direction dir)			\
	{												\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R			\
			(a, a.step(), a.ippRoiSize(),			\
			 Dir2IppAxis(dir));						\
	}												\

//static void mirror(InOut a, Wf::Direction direction);
FUNC_P_DIR(uchar, 1, mirror, Mirror)
FUNC_P_DIR(ushort, 1, mirror, Mirror)
FUNC_P_DIR(short, 1, mirror, Mirror)
FUNC_P_DIR(int, 1, mirror, Mirror)
FUNC_P_DIR(float, 1, mirror, Mirror)
FUNC_P_DIR(uchar, 3, mirror, Mirror)
FUNC_P_DIR(ushort, 3, mirror, Mirror)
FUNC_P_DIR(short, 3, mirror, Mirror)
FUNC_P_DIR(int, 3, mirror, Mirror)
FUNC_P_DIR(float, 3, mirror, Mirror)

// static void mul(const ValueArray& multiplier, InOut b, int scaleFactor=0);
FUNC_VPS_1(uchar, mul, Mul)
FUNC_VPS_1(short, mul, Mul)
FUNC_VPS_1(ushort, mul, Mul)
FUNC_VPS_3(uchar, mul, Mul)
FUNC_VPS_3(short, mul, Mul)
FUNC_VPS_3(ushort, mul, Mul)

// static void mul(In a, const ValueArray& multiplier, Out b);
FUNC_IVOS_1(uchar, mul, Mul)
FUNC_IVOS_1(short, mul, Mul)
FUNC_IVOS_1(ushort, mul, Mul)
FUNC_IVOS_1_NOSCALE(float, mul, Mul)
FUNC_IVOS_3(uchar, mul, Mul)
FUNC_IVOS_3(short, mul, Mul)
FUNC_IVOS_3(ushort, mul, Mul)
FUNC_IVOS_3_NOSCALE(float, mul, Mul)

// static void mul(In a, In b, Out c);
FUNC_IIOS(uchar, 1, mul, Mul)
FUNC_IIOS(short, 1, mul, Mul)
FUNC_IIOS(ushort, 1, mul, Mul)
FUNC_IIOS_NOSCALE(float, 1, mul, Mul)
FUNC_IIOS(uchar, 3, mul, Mul)
FUNC_IIOS(short, 3, mul, Mul)
FUNC_IIOS(ushort, 3, mul, Mul)
FUNC_IIOS_NOSCALE(float, 3, mul, Mul)

// static void set(const ValueArray& a, Out b);


// static void sub(In a, In b, Out c, int scaleFactor);
FUNC_IIOS(uchar, 1, sub, Sub)
FUNC_IIOS(ushort, 1, sub, Sub)
FUNC_IIOS(short, 1, sub, Sub)
FUNC_IIOS(uchar, 3, sub, Sub)
FUNC_IIOS(ushort, 3, sub, Sub)
FUNC_IIOS(short, 3, sub, Sub)

// static void sub(In a, In b, Out c, int scaleFactor);
FUNC_IPS(uchar, 1, sub, Sub)
FUNC_IPS(ushort, 1, sub, Sub)
FUNC_IPS(short, 1, sub, Sub)
FUNC_IPS(uchar, 3, sub, Sub)
FUNC_IPS(ushort, 3, sub, Sub)
FUNC_IPS(short, 3, sub, Sub)

// static void sub(const ValueArray& valueToBeSubtracted, InOut b, int scaleFator=0);
FUNC_VPS_1(uchar, subValueFromImage, Sub)
FUNC_VPS_1(ushort, subValueFromImage, Sub)
FUNC_VPS_1(short, subValueFromImage, Sub)
// FUNC_PKS(float, 1, subValueFromImage, Sub)
FUNC_VPS_3(uchar, subValueFromImage, Sub)
FUNC_VPS_3(ushort, subValueFromImage, Sub)
FUNC_VPS_3(short, subValueFromImage, Sub)

#define FUNC_T2_IO(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>														\
	void WImageProcess<TYPE_FROM,CHAN>								\
	::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b)					\
	{																\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R							\
			(a, a.step(),											\
			 b, b.step(), b.ippRoiSize());							\
	}

#define FUNC_T2_IOMS(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>															\
	void template<>WImageProcess<TYPE_FROM,CHAN>						\
	::MEMBER_NAME<TYPE_TO>(In a, Out b,									\
						   IppRoundMode mode,							\
						   int scaleFactor)								\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize(),								\
			 mode, scaleFactor);										\
	}

#define FUNC_T2_IOM(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>															\
	void template<>WImageProcess<TYPE_FROM,CHAN>						\
	::MEMBER_NAME<TYPE_TO>(In a, Out b,									\
						   IppRoundMode mode)							\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize(),								\
			 mode);														\
	}

// @@@

// template<typename TO> static void convertTo(In a, WImage<TO,C> b)
FUNC_T2_IO(int, float, 1, convertTo, Convert)
// FUNC_T2_IO(int, float, 3, convertTo, Convert)
// FUNC_T2_IO(int, short, 1, convertTo, Convert)
// FUNC_T2_IO(int, short, 3, convertTo, Convert)
// FUNC_T2_IO(int, ushort, 1, convertTo, Convert)
// FUNC_T2_IO(int, ushort, 3, convertTo, Convert)
FUNC_T2_IO(int, signed char, 1, convertTo, Convert)
FUNC_T2_IO(int, signed char, 3, convertTo, Convert)
FUNC_T2_IO(int, uchar, 1, convertTo, Convert)
FUNC_T2_IO(int, uchar, 3, convertTo, Convert)

FUNC_T2_IO(short, float, 1, convertTo, Convert)
FUNC_T2_IO(short, float, 3, convertTo, Convert)
FUNC_T2_IO(short, int, 1, convertTo, Convert)
FUNC_T2_IO(short, int, 3, convertTo, Convert)
// FUNC_T2_IO(short, ushort, 1, convertTo, Convert)
// FUNC_T2_IO(short, ushort, 3, convertTo, Convert)
// FUNC_T2_IO(short, signed char, 1, convertTo, Convert)
// FUNC_T2_IO(short, signed char, 3, convertTo, Convert)
FUNC_T2_IO(short, uchar, 1, convertTo, Convert)
FUNC_T2_IO(short, uchar, 3, convertTo, Convert)

FUNC_T2_IO(signed char, float, 1, convertTo, Convert)
FUNC_T2_IO(signed char, float, 3, convertTo, Convert)
FUNC_T2_IO(signed char, int, 1, convertTo, Convert)
FUNC_T2_IO(signed char, int, 3, convertTo, Convert)
// FUNC_T2_IO(signed char, signed char, 1, convertTo, Convert)
// FUNC_T2_IO(signed char, signed char, 3, convertTo, Convert)
// FUNC_T2_IO(signed char, uchar, 1, convertTo, Convert)
// FUNC_T2_IO(signed char, uchar, 3, convertTo, Convert)

FUNC_T2_IO(uchar, float, 1, convertTo, Convert)
FUNC_T2_IO(uchar, float, 3, convertTo, Convert)
FUNC_T2_IO(uchar, int, 1, convertTo, Convert)
FUNC_T2_IO(uchar, int, 3, convertTo, Convert)
FUNC_T2_IO(uchar, short, 1, convertTo, Convert)
FUNC_T2_IO(uchar, short, 3, convertTo, Convert)
FUNC_T2_IO(uchar, ushort, 1, convertTo, Convert)
FUNC_T2_IO(uchar, ushort, 3, convertTo, Convert)
// FUNC_T2_IO(uchar, signed char, 1, convertTo, Convert)
// FUNC_T2_IO(uchar, signed char, 3, convertTo, Convert)

FUNC_T2_IO(ushort, float, 1, convertTo, Convert)
FUNC_T2_IO(ushort, float, 3, convertTo, Convert)
FUNC_T2_IO(ushort, int, 1, convertTo, Convert)
FUNC_T2_IO(ushort, int, 3, convertTo, Convert)
// FUNC_T2_IO(ushort, short, 1, convertTo, Convert)
// FUNC_T2_IO(ushort, short, 3, convertTo, Convert)
// FUNC_T2_IO(ushort, signed char, 1, convertTo, Convert)
// FUNC_T2_IO(ushort, signed char, 3, convertTo, Convert)
FUNC_T2_IO(ushort, uchar, 1, convertTo, Convert)
FUNC_T2_IO(ushort, uchar, 3, convertTo, Convert)

// // template<typename TO> static void convertTo(In a, WImage<TO,C> b, IppRoundMode mode, int scaleFactor)
// FUNC_T2_IOMS(float, int, 1, convertTo, Convert)
// FUNC_T2_IOMS(float, short, 1, convertTo, Convert)
// FUNC_T2_IOMS(float, signed char, 1, convertTo, Convert)
// FUNC_T2_IOMS(float, uchar, 1, convertTo, Convert)
// FUNC_T2_IOMS(float, ushort, 1, convertTo, Convert)
// FUNC_T2_IOMS(float, usigned int, 1, convertTo, Convert)
// FUNC_T2_IOMS(int, short, 1, convertTo, Convert)
// FUNC_T2_IOMS(int, ushort, 1, convertTo, Convert)
// FUNC_T2_IOMS(short, signed char, 1, convertTo, Convert)
// FUNC_T2_IOMS(uchar, signed char, 1, convertTo, Convert)
// FUNC_T2_IOMS(ushort, short, 1, convertTo, Convert)
// FUNC_T2_IOMS(ushort, signed char, 1, convertTo, Convert)
// FUNC_T2_IOMS(usigned int, int, 1, convertTo, Convert)
// FUNC_T2_IOMS(usigned int, short, 1, convertTo, Convert)
// FUNC_T2_IOMS(usigned int, signed char, 1, convertTo, Convert)
// FUNC_T2_IOMS(usigned int, uchar, 1, convertTo, Convert)
// FUNC_T2_IOMS(usigned int, ushort, 1, convertTo, Convert)

// // static void convertTo(In a, WImage<TO,C> b, IppRoundMode mode, int scaleFactor, 1, convertTo, Convert)
// FUNC_T2_IOM(float, short, 1, convertTo, Convert)
// FUNC_T2_IOM(float, ushort, 1, convertTo, Convert)
// FUNC_T2_IOM(float, signed char, 1, convertTo, Convert)
// FUNC_T2_IOM(float, uchar, 1, convertTo, Convert)
// FUNC_T2_IOM(float, short, 3, convertTo, Convert)
// FUNC_T2_IOM(float, ushort, 3, convertTo, Convert)
// FUNC_T2_IOM(float, signed char, 3, convertTo, Convert)
// FUNC_T2_IOM(float, uchar, 3, convertTo, Convert)
