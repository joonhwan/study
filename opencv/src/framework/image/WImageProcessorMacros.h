
#define CHECK_BUFFER(a)													\
	if (!a.isValid()) {													\
		Q_ASSERT_X(a.isValid(), "buffer [" #a "]", "invalid buffer");	\
		return false;													\
	}																	\

#define CHECK_BUFFER_2(a,b)						\
	CHECK_BUFFER(a);							\
	CHECK_BUFFER(b);

#define CHECK_BUFFER_3(a,b,c)					\
	CHECK_BUFFER(a);							\
	CHECK_BUFFER(b);							\
	CHECK_BUFFER(c);

#define IPP_DEBUG(ippcall)								\
	{													\
		IppStatus __status = IPPIP::ippcall;			\
		if (__status == ippStsNoErr) {					\
			return true;								\
		} else {										\
			Q_ASSERT_X(__status==ippStsNoErr,			\
					   #ippcall,						\
					   ippGetStatusString(__status));	\
			return false;								\
		}												\
	}


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
// INTER : Interpolcation Mode
#define FUNC_IN_VALUE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelValue& value)				\
	{													\
		CHECK_BUFFER(a);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a, a.step(), a.ippRoiSize(),			\
				   value.getDataPtr()));				\
	}

#define FUNC_IN_IN_OUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)			\
	template<> bool												\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c)	\
	{															\
		CHECK_BUFFER_3(a, b, c);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R					\
				  (a, a.step(),									\
				   b, b.step(),									\
				   c, c.step(), c.ippRoiSize()));				\
	}

#define FUNC_IN_IN_OUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> bool												\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, In b, Out c,	\
										  int scaleFactor)		\
	{															\
		CHECK_BUFFER_3(a, b, c);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R					\
				  (a, a.step(),									\
				   b, b.step(),									\
				   c, c.step(), c.ippRoiSize(),					\
				   scaleFactor));								\
	}

#define FUNC_IN_OUT_INTER_CVRESIZE(TYPE,CHAN,MEMBER_NAME)				\
	template<> bool														\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, Out b,					\
										  Wf::InterpolationMode mode)	\
	{																	\
		CHECK_BUFFER_2(a, b);											\
		cv::resize(a, b,												\
				   qSizeToCvSize(b.roiSize()),							\
				   interpolationMode2Cv(mode));							\
		return true;													\
	}																	\

#define FUNC_IN_OUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)			\
	template<>												\
	bool WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, Out b)	\
	{														\
		CHECK_BUFFER_2(a, b);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R				\
				  (a, a.step(),								\
				   b, b.step(), b.ippRoiSize()));			\
	}

#define FUNC_IN_OUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> bool											\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, Out b,		\
										  int scaleFactor)	\
	{														\
		CHECK_BUFFER_2(a, b);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R				\
				  (a, a.step(),								\
				   b, b.step(), b.ippRoiSize(),				\
				   scaleFactor));							\
	}

#define FUNC_IN_INOUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>						\
	::MEMBER_NAME(In a, InOut b)						\
	{													\
		CHECK_BUFFER_2(a, b);							\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a, a.step(),							\
				   b, b.step(), b.ippRoiSize()));		\
	}

#define FUNC_IN_INOUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> bool											\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(In a, InOut b,	\
										  int scaleFactor)	\
	{														\
		CHECK_BUFFER_2(a, b);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R				\
				  (a, a.step(),								\
				   b, b.step(), b.ippRoiSize(),				\
				   scaleFactor));							\
	}


#define FUNC_INOUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<> bool									\
	WImageProcess<TYPE,CHAN>::MEMBER_NAME(InOut a)	\
	{												\
		CHECK_BUFFER(a);							\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R		\
				  (a, a.step(), a.ippRoiSize()));	\
	}

#define FUNC_INOUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)		\
	template<> bool												\
		WImageProcess<TYPE,CHAN>::MEMBER_NAME(InOut a,			\
											  int scaleFactor)	\
	{															\
		CHECK_BUFFER(a);										\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R					\
				  (a, a.step(), a.ippRoiSize(),					\
				   scaleFactor));								\
	}

#define FUNC_CVALUE_INOUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	bool WImageProcess<TYPE,CHAN>							\
		::MEMBER_NAME(const PixelValue& a, InOut b)			\
	{														\
		CHECK_BUFFER(b);									\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R				\
				  (a.getDataRef(),							\
				   b, b.step(), b.ippRoiSize()));			\
	}

#define FUNC_CVALUE_INOUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>													\
	bool WImageProcess<TYPE,CHAN>								\
		::MEMBER_NAME(const PixelValue& a, InOut b,				\
					  int scaleFactor)							\
	{															\
		CHECK_BUFFER(b);										\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R					\
				  (a.getDataRef(),								\
				   b, b.step(), b.ippRoiSize(),					\
				   scaleFactor));								\
	}

#define FUNC_CVALUE_OUT(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>						\
	::MEMBER_NAME(const PixelValue& a, Out b)			\
	{													\
		CHECK_BUFFER(b);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a.getDataRef(),						\
				   b, b.step(), b.ippRoiSize()));		\
	}


#define FUNC_IN_CVALUE_OUT_SCALE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>														\
	bool WImageProcess<TYPE,CHAN>									\
	::MEMBER_NAME(In a, const PixelValue& v, Out b,					\
				  int scaleFactor)									\
	{																\
		CHECK_BUFFER_2(a,b);										\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R						\
				  (a, a.step(),										\
				   v.getDataRef(),									\
				   b, b.step(), b.ippRoiSize(),						\
				   scaleFactor));									\
	}


// static bool copySubpixel(In a, Out b);
#define FUNC_COPYSUBPIXEL(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	bool WImageProcess<TYPE,CHAN>							\
	::MEMBER_NAME(In a, Out b)								\
	{														\
		CHECK_BUFFER_2(a,b);								\
		const QPointF& fractional							\
			= a.roiTopLeftFractionalPart();					\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R				\
				  (a, a.step(),								\
				   b, b.step(), b.ippRoiSize(),				\
				   fractional.x(), fractional.y()));		\
	}


#define FUNC_COPYSUBPIXEL_F(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>												\
	bool WImageProcess<TYPE,CHAN>							\
	::MEMBER_NAME(In a, WImageT<float,CHAN> b)				\
	{														\
		CHECK_BUFFER_2(a,b);								\
		const QPointF& fractional							\
			= a.roiTopLeftFractionalPart();					\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R				\
				  (a, a.step(),								\
				   b, b.step(), b.ippRoiSize(),				\
				   fractional.x(), fractional.y()));		\
	}


#define FUNC_IN_POS(TYPE,CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelPosition& value)				\
	{													\
		CHECK_BUFFER(a);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a, a.step(), a.ippRoiSize(),			\
				   value.getDataPtr(),					\
				   value.getXPtr(),						\
				   value.getYPtr()));					\
	}


//static bool ramp(Out a, float offset, float slope, IppiAxis axis);
#define FUNC_RAMP(TYPE,CHAN)					\
	template<>									\
	bool WImageProcess<TYPE,CHAN>::				\
	ramp(Out a, float offset, float slope,		\
		 Wf::Direction dir)						\
	{											\
		CHECK_BUFFER(a);						\
		IppiAxis axis = Dir2IppAxis(dir);		\
		IPP_DEBUG(ippiImageRamp_C##CHAN##R		\
				  (a, a.step(), a.ippRoiSize(),	\
				   offset, slope, axis));		\
	}


#define FUNC_INOUT_LUT(TYPE,CHAN)									\
	template<>														\
	bool WImageProcess<TYPE,CHAN>::									\
	lut(InOut a, const LutData& data, Wf::LutMode mode)				\
	{																\
		CHECK_BUFFER(a);											\
		LutData::ValueArrayType levels; data.getValuesIn(levels);	\
		LutData::ValueArrayType values; data.getValuesOut(values);	\
		LutData::CountArrayType counts; data.getCount(counts);		\
		switch (mode)												\
		{															\
		case Wf::Plain:												\
			IPP_DEBUG(ippiLUT_C##CHAN##R							\
					  (a, a.step(), a.ippRoiSize(),					\
					   levels, values, counts));					\
			break;													\
		case Wf::Linear:											\
			IPP_DEBUG(ippiLUT_Linear_C##CHAN##R						\
					  (a, a.step(), a.ippRoiSize(),					\
					   levels, values, counts));					\
			break;													\
		case Wf::Cubic:												\
			IPP_DEBUG(ippiLUT_Cubic_C##CHAN##R						\
					  (a, a.step(), a.ippRoiSize(),					\
					   levels, values, counts));					\
			break;													\
		}															\
		return false;												\
	}


#define FUNC_IO_LUT(TYPE,CHAN)										\
	template<>														\
	bool WImageProcess<TYPE,CHAN>::									\
	lut(In a, Out b, const LutData& data, Wf::LutMode mode)			\
	{																\
		CHECK_BUFFER_2(a,b);										\
		LutData::ValueArrayType levels; data.getValuesIn(levels);	\
		LutData::ValueArrayType values; data.getValuesOut(values);	\
		LutData::CountArrayType counts; data.getCount(counts);		\
		switch (mode)												\
		{															\
		case Wf::Plain:												\
			IPP_DEBUG(ippiLUT_C##CHAN##R							\
					  (a, a.step(),									\
					   b, b.step(), b.ippRoiSize(),					\
					   levels, values, counts));					\
			break;													\
		case Wf::Linear:											\
			IPP_DEBUG(ippiLUT_Linear_C##CHAN##R						\
					  (a, a.step(),									\
					   b, b.step(), b.ippRoiSize(),					\
					   levels, values, counts));					\
			break;													\
		case Wf::Cubic:												\
			IPP_DEBUG(ippiLUT_Cubic_C##CHAN##R						\
					  (a, a.step(),									\
					   b, b.step(), b.ippRoiSize(),					\
					   levels, values, counts));					\
			break;													\
		}															\
		return false;												\
	}


#define FUNC_IN_RANGE(TYPE,CHAN,MEMBER_NAME,IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, PixelValueRange& range)			\
	{													\
		CHECK_BUFFER(a);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a, a.step(), a.ippRoiSize(),			\
				   range.min.getDataPtr(),				\
				   range.max.getDataPtr()));			\
	}													\

#define FUNC_INOUT_DIR(TYPE,CHAN,MEMBER_NAME, IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(InOut a, Wf::Direction dir)				\
	{													\
		CHECK_BUFFER(a);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a, a.step(), a.ippRoiSize(),			\
				   Dir2IppAxis(dir)));					\
	}													\


#define FUNC_IN_REAL(TYPE,CHAN,MEMBER_NAME, IPP_NAME)	\
	template<>											\
	bool WImageProcess<TYPE,CHAN>::						\
	MEMBER_NAME(In a, RealValue& value)					\
	{													\
		CHECK_BUFFER(a);								\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R			\
				  (a, a.step(), a.ippRoiSize(),			\
				   value.getDataPtr()));				\
	}


#define FUNC_CONVERT(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>															\
	bool WImageProcess<TYPE_FROM,CHAN>									\
	::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b)						\
	{																	\
		CHECK_BUFFER_2(a, b);											\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R							\
				  (a, a.step(),											\
				   b, b.step(), b.ippRoiSize()));						\
	}

// most generalized version
// see ippi+.hpp funcions that calls to ippiConvert___XXX() (3 underscores!)
#define FUNC_CONVERT_ROUND(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME)	\
	template<>															\
	bool WImageProcess<TYPE_FROM,CHAN>									\
	::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b,						\
					  Wf::RoundMode mode)								\
	{																	\
	 CHECK_BUFFER_2(a, b);												\
	 IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R								\
			   (a, a.step(),											\
					b, b.step(), b.ippRoiSize(),						\
					RoundMode2IppRoundMode(mode)));						\
	 }

#define FUNC_CONVERT_ROUND_SCALE(TYPE_FROM, TYPE_TO, CHAN, MEMBER_NAME, IPP_NAME) \
	template<>															\
	bool WImageProcess<TYPE_FROM,CHAN>									\
		::MEMBER_NAME(In a, WImageT<TYPE_TO,CHAN> b,					\
					  Wf::RoundMode mode,								\
					  int scaleFactor)									\
	{																	\
		CHECK_BUFFER_2(a, b);											\
		IPP_DEBUG(ippi##IPP_NAME##_C##CHAN##R							\
				  (a, a.step(),											\
				   b, b.step(), b.ippRoiSize(),							\
				   RoundMode2IppRoundMode(mode), scaleFactor));			\
	}

#define FILTER_IN_IKERNEL_OUT(TYPE,CHAN,N)							\
	template<>														\
	bool WImageProcess<TYPE, CHAN>::								\
	filter(In a, const IntKernel##N##x##N& b, Out c)				\
	{																\
		CHECK_BUFFER_2(a, c);										\
	    IPP_DEBUG(ippiFilter_C##CHAN##R								\
				  (a, a.step(),										\
				   c, c.step(), c.ippRoiSize(),						\
				   b, b.ippSize(), b.ippAnchor(), b.divisor()));	\
	}
