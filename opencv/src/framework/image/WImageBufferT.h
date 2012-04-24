#pragma once

#include "image/WConstImageT.h"
#include "image/WImageT.h"
#include "image/WImageBufferTraits.h"
#include "image/WImageBuffer.h"
#include "image/WIppKernel.h"
#include "image/WPixel.h"
#include <QPixmap>

class QRect;

template<typename T, int C>
class WImageProcess;

template<typename T, int C>
class WImageT;

template<typename T, int C>
class WImageBufferT : public WImageBuffer
{
public:
	typedef T DataType;
	typedef WImageProcess<T,C> Processor;
	typedef WImageBufferTypeTrait<T> Trait;
	typedef WImageDimensionTrait<T,C> DimTrait;
	typedef WConstImageT<T,C> ConstImage;
	typedef WConstImageT<T,C> In;
	typedef WImageT<T,C> Image;
	typedef WImageT<T,C> Out;
	typedef WImageT<T,C> InOut;
	typedef WPixelValue<T,C> PixelValue;
	typedef WPixelPosition<T,C> PixelPosition;
	typedef WIppIntKernel<1,3> IppKernel3x3;
	typedef WIppIntKernel<1,5> IppKernel5x5;
	typedef typename WImageDimensionTrait<T,C>::cv_const_iterator const_iterator;
	typedef typename WImageDimensionTrait<T,C>::cv_iterator iterator;
	typedef typename WImageDimensionTrait<T,C>::cv_pixel_type pixel_type;
	WImageBufferT()
	{
	}
	WImageBufferT(const cv::Mat& matrix)
		: WImageBuffer(matrix)
	{
	}
	WImageBufferT(const QString& filePathName)
	{
		loadFromFile(filePathName);
	}
	WImageBufferT(const QSize& size)
		: WImageBuffer(size.height()/*rows*/, size.width()/*cols*/,
				 CV_MAKETYPE(Trait::openCvMatDepth,C))
	{
	}
	WImageBufferT(int width, int height)
		: WImageBuffer(height/*rows*/, width/*cols*/,
					   CV_MAKETYPE(Trait::openCvMatDepth,C))
	{
	}
	WImageBufferT(int width, int height, const cv::Scalar& s)
		: WImageBuffer(height/*rows*/, width/*cols*/,
					   CV_MAKETYPE(Trait::openCvMatDepth,C), s)
	{
	}
	WImageBufferT(const WImageBufferT<uchar,1>& src);
	WImageBufferT(const WImageBufferT<ushort,1>& src);
	WImageBufferT(const WImageBufferT<float,1>& src);
	WImageBufferT(const WImageBufferT<uchar,3>& src);
	WImageBufferT(const WImageBufferT<ushort,3>& src);
	WImageBufferT(const WImageBufferT<float,3>& src);
	// TODO CHECKME should be virtual or not?
	// maybe not. see opencv comment on cv::Mat_ class in core.hpp
    ~WImageBufferT()
	{
	}
	WImageBufferT<T, C>& operator=(const WImageBufferT<uchar, 1>& src);
	WImageBufferT<T, C>& operator=(const WImageBufferT<ushort, 1>& src);
	WImageBufferT<T, C>& operator=(const WImageBufferT<float, 1>& src);
	WImageBufferT<T, C>& operator=(const WImageBufferT<uchar, 3>& src);
	WImageBufferT<T, C>& operator=(const WImageBufferT<ushort, 3>& src);
	WImageBufferT<T, C>& operator=(const WImageBufferT<float, 3>& src);
	WImageBufferT<T, C>& operator=(const cv::MatExpr& expr)
	{
		(cv::Mat_<T>&)(this->matrix()) = expr;
		return *this;
	}
	const_iterator begin() const
	{
		return this->matrix().begin<pixel_type>();
	}
	iterator begin()
	{
		return this->matrix().begin<pixel_type>();
	}
	const_iterator end() const
	{
		return this->matrix().end<pixel_type>();
	}
	iterator end()
	{
		return this->matrix().end<pixel_type>();
	}
	PixelValue pixel(int x, int y) const;
	// ConstImage,Image,ImageInOut accessor creation operators
	ConstImage from(const QPoint& topLeft) const
	{
		return ConstImage(*this, topLeft);
	}
	ConstImage from(int x, int y) const
	{
		return ConstImage(*this, QPoint(x,y));
	}
	ConstImage from(const QRect& roi) const
	{
		return ConstImage(*this, roi);
	}
	ConstImage from(int x, int y, int width, int height) const
	{
		return ConstImage(*this, QRect(x,y,width,height));
	}
	ConstImage from(int x, int y, const QSize& size) const
	{
		return ConstImage(*this, QRect(QPoint(x,y),size));
	}
	// for subpixel operation
	ConstImage from(double x, double y, int width, int height) const
	{
		return from(x,y,width,height);
	}
	// for easier handling C2666 error
	ConstImage fromF(double x, double y, int width, int height) const
	{
		return ConstImage(*this, QPointF(x,y), QSize(width,height));
	}
	// for subpixel operation (ex: copySubPixel)
	ConstImage from(double x, double y, const QSize& size) const
	{
		return fromF(x,y,size);
	}
	// for easier handling C2666 error
	ConstImage fromF(double x, double y, const QSize& size) const
	{
		return ConstImage(*this, QPointF(x,y), size);
	}
	// for subpixel operation (ex: copySubPixel)
	ConstImage from(const QPointF& topLeft, const QSize& size) const
	{
		return ConstImage(*this, topLeft, size);
	}
	Image to(const QRect& roi)
	{
		return Image(*this, roi);
	}
	Image to(int x, int y, int width, int height)
	{
		return Image(*this, QRect(x,y,width,height));
	}
	Image to(int x, int y, const QSize& roiSize)
	{
		return Image(*this, QRect(QPoint(x,y),roiSize));
	}
	Image to()
	{
		return Image(*this);
	}
	bool loadFromFile(const QString& filePathName)
	{
		matrix() = cv::imread(filePathName.toLocal8Bit().data(), DimTrait::loadFlag);
		return matrix().total();
	}
	// Qt support
	QPixmap toPixmap() const;
	QImage toImage() const;
};

#include "image/WImageBufferT.inl"
