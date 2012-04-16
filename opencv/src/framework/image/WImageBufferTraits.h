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
struct WImageBufferTypeTrait;

#define DEFINE_TRAIT(T, CVID, IPPTYPE)									\
	template<>															\
	struct WImageBufferTypeTrait<T>										\
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
DEFINE_TRAIT(short, CV_16S, Ipp16s)
DEFINE_TRAIT(int, CV_32S, Ipp32s)
DEFINE_TRAIT(float, CV_32F, Ipp32f)
DEFINE_TRAIT(double, CV_64F, Ipp64f)

template<typename T, int C>
struct WImageDimensionTrait;

#define DEFINE_IOTRAIT(T, C,FLAG,PIXELTYPE)								\
	template<>															\
	struct WImageDimensionTrait<T, C>									\
	{																	\
		enum															\
		{																\
			loadFlag = FLAG,											\
		};																\
		typedef PIXELTYPE cv_pixel_type;								\
		typedef cv::Mat_< PIXELTYPE >::const_iterator cv_const_iterator; \
		typedef cv::Mat_< PIXELTYPE >::iterator cv_iterator;			\
	};																	\

template<>
struct WImageDimensionTrait<uchar, 1>
{
	enum
	{
		loadFlag = CV_LOAD_IMAGE_GRAYSCALE,
	};
	typedef uchar cv_pixel_type;
	typedef cv::Mat_< uchar >::const_iterator cv_const_iterator;
	typedef cv::Mat_< uchar >::iterator cv_iterator;
};

// DEFINE_IOTRAIT(uchar,1,CV_LOAD_IMAGE_GRAYSCALE, uchar)
DEFINE_IOTRAIT(uchar,3,CV_LOAD_IMAGE_COLOR, cv::Vec3b )
DEFINE_IOTRAIT(ushort,1,CV_LOAD_IMAGE_GRAYSCALE, ushort)
DEFINE_IOTRAIT(ushort,3,CV_LOAD_IMAGE_COLOR, cv::Vec3w )
DEFINE_IOTRAIT(short,1,CV_LOAD_IMAGE_GRAYSCALE, short)
DEFINE_IOTRAIT(short,3,CV_LOAD_IMAGE_COLOR, cv::Vec3s )
DEFINE_IOTRAIT(int,1,CV_LOAD_IMAGE_GRAYSCALE, int)
DEFINE_IOTRAIT(int,3,CV_LOAD_IMAGE_COLOR, cv::Vec3i )
DEFINE_IOTRAIT(float,1,CV_LOAD_IMAGE_GRAYSCALE, float)
DEFINE_IOTRAIT(float,3,CV_LOAD_IMAGE_COLOR, cv::Vec3f )
