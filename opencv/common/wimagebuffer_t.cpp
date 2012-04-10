#include "wimage_t.h"
#include "wimageprocessor.h"

// 1. same format = copy constructor
#define COPY_CONSTRUCTOR(TYPE, C)							\
	template<>												\
	WImageBufferT<TYPE, C>::WImageBufferT(const WImageBufferT<TYPE, C>& src)	\
		: WImageBuffer((const WImageBuffer&)src)						\
	{														\
	}

COPY_CONSTRUCTOR(uchar,  1)
COPY_CONSTRUCTOR(ushort, 1)
COPY_CONSTRUCTOR(float,  1)
COPY_CONSTRUCTOR(uchar,  3)
COPY_CONSTRUCTOR(ushort, 3)
COPY_CONSTRUCTOR(float,  3)

// 2. same channel count conversion
#define DEPTH_CONVERT_CONSTRUCTOR(TYPE_FROM, TYPE_TO, C)						\
	template<>															\
	WImageBufferT<TYPE_TO, C>::WImageBufferT(const WImageBufferT<TYPE_FROM, C>& src)		\
		: WImageBuffer(src.height(), src.width(),								\
		  CV_MAKETYPE(Trait::openCvMatDepth, C))						\
	{																	\
		WImageBufferT<TYPE_FROM, C>::Processor().convertTo(src, *this); \
	}

DEPTH_CONVERT_CONSTRUCTOR(uchar, float, 1)
DEPTH_CONVERT_CONSTRUCTOR(uchar, float, 3)
DEPTH_CONVERT_CONSTRUCTOR(uchar, ushort, 1)
DEPTH_CONVERT_CONSTRUCTOR(uchar, ushort, 3)


// 아래 목록은 해당하는 convertT<> 함수가 없음.(해당 ipp함수가
// 없음. opencv함수를 경유하도록 구현)
//
// DEPTH_CONVERT_CONSTRUCTOR(float, uchar, 1)
// DEPTH_CONVERT_CONSTRUCTOR(float, uchar, 3)
#define DEPTH_CONVERT_CONSTRUCTOR_OPENCV(TYPE_FROM, TYPE_TO, C)				\
	template<>															\
	WImageBufferT<TYPE_TO, C>::WImageBufferT(const WImageBufferT<TYPE_FROM, C>&src)		\
	{																	\
		src->convertTo(*this, CV_MAKETYPE(Trait::openCvMatDepth,C));	\
	}

DEPTH_CONVERT_CONSTRUCTOR_OPENCV(float, uchar, 1)
DEPTH_CONVERT_CONSTRUCTOR_OPENCV(float, ushort, 1)
DEPTH_CONVERT_CONSTRUCTOR_OPENCV(float, uchar, 3)
DEPTH_CONVERT_CONSTRUCTOR_OPENCV(float, ushort, 3)


// 3. color to mono conversion
// for 'CODE' see "opencv2/imgproc/types_c.h"
#define COLOR_CONVERT(TYPE, C_FROM, C_TO, CODE)						\
	template<>														\
	WImageBufferT<TYPE, C_TO>::WImageBufferT(const WImageBufferT<TYPE, C_FROM>& src)	\
		: WImageBuffer(src.height(), src.width(),							\
				 CV_MAKETYPE(Trait::openCvMatDepth,1))				\
	{																\
		cv::cvtColor(src, *this, CODE);								\
	}

COLOR_CONVERT(uchar, 3, 1, CV_RGB2GRAY)
COLOR_CONVERT(ushort,3, 1, CV_RGB2GRAY)
COLOR_CONVERT(float, 3, 1, CV_RGB2GRAY)
COLOR_CONVERT(uchar, 1, 3, CV_GRAY2RGB)
COLOR_CONVERT(ushort,1, 3, CV_GRAY2RGB)
COLOR_CONVERT(float, 1, 3, CV_GRAY2RGB)


// assignment operator

// 1. same type
#define ASSIGN_SAME_TYPE(TYPE, C)										\
	template<>															\
	WImageBufferT<TYPE, C>&													\
	WImageBufferT<TYPE, C>::operator=(const WImageBufferT<TYPE, C>& src)			\
	{																	\
		(WImageBuffer&)(*this) = (const WImageBuffer&)(src);						\
		return *this;													\
	}

ASSIGN_SAME_TYPE(uchar, 1)
ASSIGN_SAME_TYPE(ushort, 1)
ASSIGN_SAME_TYPE(float, 1)
ASSIGN_SAME_TYPE(uchar, 3)
ASSIGN_SAME_TYPE(ushort, 3)
ASSIGN_SAME_TYPE(float, 3)

// 2. same channel count conversion
#define ASSIGN_DEPTH_CONVERT(TYPE_FROM, TYPE_TO, C)						\
	template<>															\
	WImageBufferT<TYPE_TO, C>&											\
	WImageBufferT<TYPE_TO, C>::operator=(const WImageBufferT<TYPE_FROM, C>& src) \
	{																	\
		WImageBufferT<TYPE_FROM, C>::Processor().						\
			convertTo(src, *this);										\
		return *this;													\
	}

ASSIGN_DEPTH_CONVERT(uchar, float, 1)
ASSIGN_DEPTH_CONVERT(uchar, ushort, 1)
ASSIGN_DEPTH_CONVERT(ushort, uchar, 1)
ASSIGN_DEPTH_CONVERT(ushort, float, 1)
ASSIGN_DEPTH_CONVERT(uchar, float, 3)
ASSIGN_DEPTH_CONVERT(uchar, ushort, 3)
ASSIGN_DEPTH_CONVERT(ushort, uchar, 3)
ASSIGN_DEPTH_CONVERT(ushort, float, 3)

#define ASSIGN_DEPTH_CHANGE_OPENCV(TYPE_FROM, TYPE_TO, C)				\
	template<>															\
	WImageBufferT<TYPE_TO, C>&												\
	WImageBufferT<TYPE_TO, C>::operator=(const WImageBufferT<TYPE_FROM, C>& src)	\
	{																	\
		(cv::Mat&)(*this) = (const cv::Mat&)src;						\
		return *this;													\
	}

ASSIGN_DEPTH_CHANGE_OPENCV(float, uchar, 1)
ASSIGN_DEPTH_CHANGE_OPENCV(float, ushort, 1)
ASSIGN_DEPTH_CHANGE_OPENCV(float, uchar, 3)
ASSIGN_DEPTH_CHANGE_OPENCV(float, ushort, 3)


#define PIXEL_VALUE_C1(TYPE)											\
	template<>															\
	WImageBufferT<TYPE,1>::PixelValue WImageBufferT<TYPE,1>::pixel(int x, int y) const \
	{																	\
		const cv::Mat& mat = this->matrix();							\
		WImageBufferT<TYPE,1>::PixelValue value(mat.at<TYPE>(y, x));								\
		return value;													\
	}

PIXEL_VALUE_C1(uchar)
PIXEL_VALUE_C1(ushort)
PIXEL_VALUE_C1(short)
PIXEL_VALUE_C1(float)

#define PIXEL_VALUE_C3(TYPE)							\
	template<>											\
	WPixelValue<TYPE,3>									\
	WImageBufferT<TYPE,3>::pixel(int _x, int y) const	\
	{													\
		int x = _x * 3;									\
		const cv::Mat& mat = this->matrix();			\
		PixelValue value(mat.at<TYPE>(y, x),			\
						 mat.at<TYPE>(y, x+1),			\
						 mat.at<TYPE>(y, x+2));			\
		return value;									\
	}

PIXEL_VALUE_C3(uchar)
PIXEL_VALUE_C3(ushort)
PIXEL_VALUE_C3(short)
PIXEL_VALUE_C3(float)
