// [signature naming convention]
// OUT : Out
// IN : In
// INOUT : Inout
// CVALUE : Constant Pixel value
// VALUE : Non-Constnat Pixel value
// SCALE : ScaleFactor 2^(-n) used in IPP
// POS : Non-Constant Pixel value with position info
// RANGE : Non-Constant Pixel Range(min/max pixel value)
// DIR : Direction info(Horizontal, Vertical, Both)
// REAL : Non-Constant Real Pixel Value(double or 64bit-real pixel value)

#define FUNC_IN_VALUE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelValue& value)				\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(), a.ippRoiSize(),				\
			 value.getDataPtr());						\
	}

#define FUNC_IN_IN_OUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)			\
	template<> void												\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c)	\
	{															\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R						\
			(a, a.step(),										\
			 b, b.step(),										\
			 c, c.step(), c.ippRoiSize());						\
	}

#define FUNC_IN_IN_OUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> void												\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c,	\
										  int scaleFactor)		\
	{															\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R						\
			(a, a.step(),										\
			 b, b.step(),										\
			 c, c.step(), c.ippRoiSize(),						\
			 scaleFactor);										\
	}

#define FUNC_IN_OUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)			\
	template<>												\
	void WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, Out b)	\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(),									\
			 b, b.step(), b.ippRoiSize());					\
	}

#define FUNC_IN_OUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> void											\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, Out b,		\
										  int scaleFactor)	\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(),									\
			 b, b.step(), b.ippRoiSize(),					\
			 scaleFactor);									\
	}

#define FUNC_IN_INOUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>						\
	::MEMBER_NAME(In a, InOut b)						\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(),								\
			 b, b.step(), b.ippRoiSize());				\
	}

#define FUNC_IN_INOUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> void											\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, InOut b,	\
										  int scaleFactor)	\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(),									\
			 b, b.step(), b.ippRoiSize(),					\
			 scaleFactor);									\
	}


#define FUNC_INOUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> void									\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(InOut a)	\
	{												\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R			\
			(a, a.step(), a.ippRoiSize());			\
	}

#define FUNC_INOUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> void											\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(InOut a,			\
										  int scaleFactor)	\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a, a.step(), a.ippRoiSize(),					\
			 scaleFactor);									\
	}

#define FUNC_CVALUE_INOUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	void WImageProcess<TYPE,CHAN>							\
	::MEMBER_NAME(const PixelValue& a, InOut b)				\
	{														\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R					\
			(a.getDataRef(),								\
			 b, b.step(), b.ippRoiSize());					\
	}

#define FUNC_CVALUE_INOUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>													\
	void WImageProcess<TYPE,CHAN>								\
	::MEMBER_NAME(const PixelValue& a, InOut b,					\
				  int scaleFactor)								\
	{															\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R						\
			(a.getDataRef(),									\
			 b, b.step(), b.ippRoiSize(),						\
			 scaleFactor);										\
	}

#define FUNC_CVALUE_OUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>						\
	::MEMBER_NAME(const PixelValue& a, Out b)			\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a.getDataRef(),							\
			 b, b.step(), b.ippRoiSize());				\
	}


#define FUNC_IN_CVALUE_OUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>														\
	void WImageProcess<TYPE,CHAN>									\
	::MEMBER_NAME(In a, const PixelValue& v, Out b,					\
				  int scaleFactor)									\
	{																\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R							\
			(a, a.step(),											\
			 v.getDataRef(),										\
			 b, b.step(), b.ippRoiSize(),							\
			 scaleFactor);											\
	}


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


#define FUNC_IN_POS(TYPE,CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelPosition& value)				\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(), a.ippRoiSize(),				\
			 value.getDataPtr(),						\
			 value.getXPtr(),							\
			 value.getYPtr());							\
	}


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


#define FUNC_INOUT_LUT(TYPE,CHAN)									\
	template<>														\
	void WImageProcess<TYPE,CHAN>::									\
	lut(InOut a, const LutData& data, Wf::LutMode mode)				\
	{																\
		LutData::ValueArrayType levels; data.getValuesIn(levels);	\
		LutData::ValueArrayType values; data.getValuesOut(values);	\
		LutData::CountArrayType counts; data.getCount(counts);		\
		switch (mode)												\
		{															\
		case Wf::Plain:												\
			IPPIP::ippiLUT_C##CHAN##R								\
				(a, a.step(), a.ippRoiSize(),						\
				 levels, values, counts);							\
				break;												\
		case Wf::Linear:											\
			IPPIP::ippiLUT_Linear_C##CHAN##R						\
				(a, a.step(), a.ippRoiSize(),						\
				 levels, values, counts);							\
				break;												\
		case Wf::Cubic:												\
			IPPIP::ippiLUT_Cubic_C##CHAN##R							\
				(a, a.step(), a.ippRoiSize(),						\
				 levels, values, counts);							\
				break;												\
		}															\
	}


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


#define FUNC_IN_RANGE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelValueRange& range)			\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(), a.ippRoiSize(),				\
			 range.min.getDataPtr(),					\
			 range.max.getDataPtr());					\
	}													\

#define FUNC_INOUT_DIR(TYPE,CHAN,MEMBER_NAME, IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>::						\
		MEMBER_NAME(InOut a, Wf::Direction dir)			\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(), a.ippRoiSize(),				\
			 Dir2IppAxis(dir));							\
	}													\


#define FUNC_IN_REAL(TYPE,CHAN,MEMBER_NAME, IPP_NAME)	\
	template<>											\
	void WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, RealValue& value)					\
	{													\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R				\
			(a, a.step(), a.ippRoiSize(),				\
			 value.getDataPtr());						\
	}


#define FUNC_CONVERT(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>															\
	void WImageProcess<TYPE_FROM,CHAN>									\
	::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b)						\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize());								\
	}

// most generalized version
// see ippi+.hpp funcions that calls to ippiConvert___XXX() (3 underscores!)
#define FUNC_CONVERT_ROUND(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>															\
	void WImageProcess<TYPE_FROM,CHAN>									\
		::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b,					\
					  Wf::RoundMode mode)								\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize(),								\
			 RoundMode2IppRoundMode(mode));								\
	}

#define FUNC_CONVERT_ROUND_SCALE(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME) \
	template<>															\
	void WImageProcess<TYPE_FROM,CHAN>									\
		::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b,					\
					  Wf::RoundMode mode,								\
					  int scaleFactor)									\
	{																	\
		IPPIP::ippi##IPP_NAME##_C##CHAN##R								\
			(a, a.step(),												\
			 b, b.step(), b.ippRoiSize(),								\
			 RoundMode2IppRoundMode(mode), scaleFactor);				\
	}
