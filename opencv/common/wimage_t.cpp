#include "wimage_t.h"
#include "wimageipp.h"

// 1. same format = copy constructor
#define COPY_CONSTRUCTOR(TYPE, C)							\
	template<>												\
	WImageT<TYPE, C>::WImageT(const WImageT<TYPE, C>& src)	\
		: WImage((const WImage&)src)						\
	{														\
	}

COPY_CONSTRUCTOR(uchar,  1)
COPY_CONSTRUCTOR(ushort, 1)
COPY_CONSTRUCTOR(float,  1)
COPY_CONSTRUCTOR(uchar,  3)
COPY_CONSTRUCTOR(ushort, 3)
COPY_CONSTRUCTOR(float,  3)

// 2. same channel count conversion
#define CONVERT_CONSTRUCTOR(TYPE_FROM, TYPE_TO, C)						\
	template<>															\
	WImageT<TYPE_TO, C>::WImageT(const WImageT<TYPE_FROM, C>& src)		\
		: WImage(src.height(), src.width(),								\
		  CV_MAKETYPE(Trait::openCvMatDepth, C))						\
	{																	\
		WImageT<TYPE_FROM, C>::Processor().convertTo<TYPE_TO>(src, *this); \
	}

CONVERT_CONSTRUCTOR(uchar, float, 1)
CONVERT_CONSTRUCTOR(uchar, float, 3)
CONVERT_CONSTRUCTOR(uchar, ushort, 1)
CONVERT_CONSTRUCTOR(uchar, ushort, 3)


// 아래 목록은 해당하는 convertT<> 함수가 없음.(해당 ipp함수가
// 없음. opencv함수를 경유하도록 구현)
//
// CONVERT_CONSTRUCTOR(float, uchar, 1)
// CONVERT_CONSTRUCTOR(float, uchar, 3)
#define CONVERT_CONSTRUCTOR_OPENCV(TYPE_FROM, TYPE_TO, C)				\
	template<>															\
	WImageT<TYPE_TO, C>::WImageT(const WImageT<TYPE_FROM, C>&src)		\
	{																	\
		src->convertTo(*this, CV_MAKETYPE(Trait::openCvMatDepth,C));	\
	}

CONVERT_CONSTRUCTOR_OPENCV(float, uchar, 1)
CONVERT_CONSTRUCTOR_OPENCV(float, ushort, 1)
CONVERT_CONSTRUCTOR_OPENCV(float, uchar, 3)
CONVERT_CONSTRUCTOR_OPENCV(float, ushort, 3)


// 3. color to mono conversion
// for 'CODE' see "opencv2/imgproc/types_c.h"
#define COLOR_CONVERT(TYPE, C_FROM, C_TO, CODE)						\
	template<>														\
	WImageT<TYPE, C_TO>::WImageT(const WImageT<TYPE, C_FROM>& src)	\
		: WImage(src.height(), src.width(),							\
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
