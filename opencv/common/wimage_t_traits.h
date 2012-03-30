#pragma once

#include <opencv2/opencv.hpp>
#include <ipp.h>

// #define CV_8U   0
// #define CV_8S   1
// #define CV_16U  2
// #define CV_16S  3
// #define CV_32S  4
// #define CV_32F  5
// #define CV_64F  6

// char -> signed 8 bit
// uchar -> unsigned 8 bit
// short -> signed 16 bit
// ushort -> unsigned 16 bit
// float -> signed 32 bit
// double -> signed 64 bit

template<typename T>
struct WImageTypeTrait
{
	enum
	{
		bitDepth = 0,
		openCvMatDepth = 0,
	};
	typedef typename T::IppBufferType IppBufferType;
};

#define DEFINE_TRAIT(T, CVID, IPPTYPE)									\
	template<>															\
	struct WImageTypeTrait<T>											\
	{																	\
		enum															\
		{																\
			bitDepth = sizeof(T),										\
			openCvMatDepth = CVID,										\
		};																\
		typedef IPPTYPE IppBufferType;									\
	};

DEFINE_TRAIT(uchar, CV_8U, Ipp8u)
DEFINE_TRAIT(ushort, CV_16U, Ipp16u)
DEFINE_TRAIT(float, CV_32F, Ipp32f)
