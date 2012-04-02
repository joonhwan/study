#pragma once

#include "wimage.h"
#include "wimage_t_traits.h"
#include <QRect>

template<typename T, int C>
class WImageT;

template<typename T, int C>
class WInputImageT
{
	WInputImageT(); // cannot use thi ctor
public:
	typedef const WImageT<T,C> ImageType;
	WInputImageT(const ImageType& _const_image,
				 const QPoint& _topLeft)
		: m_const_image(_const_image)
		, m_topLeft(_topLeft)
	{
	}
	WInputImageT(const ImageType& _const_image)
		: m_const_image(_const_image)
		, m_topLeft(0,0)
	{
	}
	cv::Mat matrix(int width, int height) const {
		cv::Rect rect(m_topLeft.x(), m_topLeft.y(),
					  width, height);
		// generated object will be copied in a shallow way.
		return ((const cv::Mat&)m_const_image)(rect);
	}
	cv::Mat matrix(const QSize& roiSize) const {
		return matrix(roiSize.width(), roiSize.height());
	}
	cv::Mat matrix(const QRect& roi) const {
		cv::Rect rect(roi.x(), roi.y(),
					  roi.width(), roi.height());
		// generated object will be copied in a shallow way.
		return ((const cv::Mat&)m_const_image)(rect);
	}
	operator const T* () const
	{
		//  NOTE : y=row, x=col
		return m_const_image->ptr<T>(m_topLeft.y(), m_topLeft.x());
	}
	int channels() const
	{
		// return C;
		return m_const_image->channels();
	}
	int step() const
	{
		return m_const_image->step;
	}
	// dimension 에 대한 check도 canInclude로 된다.(side effect).
	// 2차원인경우에만, rows > 0 , cols > 0 이다.
	bool canInclude(const QRect& roi) const
	{
		const cv::Mat& mat = (const cv::Mat&)m_const_image;
		return (mat.rows > 0)
			&& (mat.cols > 0)
			&& ((roi.right()) < mat.cols)
			&& ((roi.bottom()) < mat.rows);
	}
	bool canExpandTo(const QSize& roiSize) const
	{
		return canInclude(QRect(m_topLeft, roiSize));
	}
	bool hasSameChannelWith(const WInputImageT<T,C>& i0)
	{
		return m_const_image->channels() == i0.m_const_image->channels();
	}
	bool hasSameChannelWith(const WInputImageT<T,C>& i0, const WInputImageT<T,C>& i1)
	{
		// C ?
		int channel = m_const_image->channels();
		return channel == i0.m_const_image->channels()
			&& channel == i1.m_const_image->channels();
	}
protected:
	const WImageT<T,C>& m_const_image;
	QPoint m_topLeft;
};


template<typename T, int C>
class WOutputImageT : public WInputImageT<T,C>
{
	WOutputImageT(); // cannot use this ctor
public:
	typedef WImageT<T,C> ImageType;
	WOutputImageT(ImageType& _image,
				  const QRect& _roi)
		: WInputImageT<T,C>(_image,
							_roi.topLeft())
		, m_image(_image)
		, m_roi(_roi)
	{
	}
	WOutputImageT(ImageType& _image)
		: WInputImageT<T,C>(_image)
		, m_image(_image)
	{
		const cv::Mat& mat = (const cv::Mat&)m_image;
		// full roi
		m_roi = QRect(0,0,mat.cols,mat.rows);
	}
	operator T* ()
	{
		//  NOTE : y=row, x=col
		return m_image->ptr<T>(m_roi.y(),m_roi.x());
	}
	cv::Mat matrix() const
	{
		return WInputImageT<T,C>::matrix(m_roi);
	}
	QSize roiSize() const
	{
		return m_roi.size();
	}
	IppiSize ippRoiSize() const
	{
		IppiSize size = {
			m_roi.width(),
			m_roi.height()
		};
		return size;
	}
	const QRect& roi() const
	{
		return m_roi;
	}
	bool canOperateFrom(const WInputImageT<T,C>& i0) const
	{
		return i0.canExpandTo(m_roi.size());
	}
	bool canOperateFrom(const WInputImageT<T,C>& i0, const WInputImageT<T,C>& i1) const
	{
		QSize size = m_roi.size();
		return i0.canExpandTo(size)
			&& i1.canExpandTo(size);
	}
protected:
	ImageType& m_image;
	QRect m_roi;
};

template<typename T, int C>
class WImageProcess;

template<typename T, int C>
class WImageT : public WImage
{
public:
	typedef WImageProcess<T,C> Processor;
	typedef WImageTypeTrait<T> Trait;
	typedef WImageCvIoTrait<T,C> IoTrait;
	WImageT()
	{
	}
	WImageT(const QString& filePathName)
	{
		loadFromFile(filePathName);
	}
	WImageT(int width, int height)
		: WImage(height/*rows*/, width/*cols*/,
				 CV_MAKETYPE(Trait::openCvMatDepth,C))
	{
	}
	WImageT(int width, int height, const cv::Scalar& s)
		: WImage(height/*rows*/, width/*cols*/,
				 CV_MAKETYPE(Trait::openCvMatDepth,C), s)
	{
	}
	WImageT(const WImageT<uchar,1>& src);
	WImageT(const WImageT<ushort,1>& src);
	WImageT(const WImageT<float,1>& src);
	WImageT(const WImageT<uchar,3>& src);
	WImageT(const WImageT<ushort,3>& src);
	WImageT(const WImageT<float,3>& src);
	// TODO CHECKME should be virtual or not?
	// maybe not. see opencv comment on cv::Mat_ class in core.hpp
    ~WImageT()
	{
	}
	WInputImageT<T,C> operator () (const QPoint& topLeft) const
	{
		return WInputImageT<T,C>(*this, topLeft);
	}
	WInputImageT<T,C> of(const QPoint& topLeft) const
	{
		return WInputImageT<T,C>(*this, topLeft);
	}
	WOutputImageT<T,C> operator ()(const QRect& roi)
	{
		return WOutputImageT<T,C>(*this, roi);
	}
	WOutputImageT<T,C> of(const QRect& roi)
	{
		return WOutputImageT<T,C>(*this, roi);
	}
	void loadFromFile(const QString& filePathName)
	{
		matrix() = cv::imread(filePathName.toLocal8Bit().data(), IoTrait::loadFlag);
	}
};
