#pragma once

#include "wimage.h"
#include "wimage_t_traits.h"
#include <QRect>

template<typename T>
class WImageT;

template<typename T>
class WInputImageT
{
	WInputImageT(); // cannot use thi ctor
public:
	typedef const WImageT<T> ImageType;
	WInputImageT(const ImageType& _const_image,
				 const QPoint& _topLeft)
		: m_const_image(_const_image)
		, m_topLeft(_topLeft)
	{
	}
	cv::Mat matrix(const QSize& roiSize) const {
		cv::Rect rect(m_topLeft.x(), m_topLeft.y(),
					  roiSize.width(), roiSize.height());
		return ((const cv::Mat&)m_const_image)(rect);
	}
	cv::Mat matrix(const QRect& roi) const {
		cv::Rect rect(roi.x(), roi.y(),
					  roi.width(), roi.height());
		return ((const cv::Mat&)m_const_image)(rect);
	}
	operator const T* () const
	{
		//  NOTE : y=row, x=col
		return m_const_image->ptr<T>(m_topLeft.y(), m_topLeft.x());
	}
	int channels() const
	{
		return m_const_image->channels();
	}
	int step() const
	{
		return m_const_image->step1();
	}
	// dimension 에 대한 check도 canInclude로 된다.(side effect).
	// 2차원인경우에만, rows > 0 , cols > 0 이다.
	bool canInclude(const QRect& roi) const
	{
		const cv::Mat& mat = (const cv::Mat&)m_const_image;
		return (mat.rows > 0)
			&& (mat.cols > 0)
			&& ((roi.x() + roi.width()) < mat.cols)
			&& ((roi.y() + roi.height()) < mat.rows);
	}
	bool canExpandTo(const QSize& roiSize) const
	{
		return canInclude(QRect(m_topLeft, roiSize));
	}
	bool hasSameChannelWith(const WInputImageT<T>& i0)
	{
		return m_const_image->channels() == i0.m_const_image->channels();
	}
	bool hasSameChannelWith(const WInputImageT<T>& i0, const WInputImageT<T>& i1)
	{
		int channel = m_const_image->channels();
		return channel == i0.m_const_image->channels()
			&& channel == i1.m_const_image->channels();
	}
protected:
	const WImageT<T>& m_const_image;
	QPoint m_topLeft;
};

template<typename T>
class WOutputImageT : public WInputImageT<T>
{
	WOutputImageT(); // cannot use this ctor
public:
	typedef WImageT<T> ImageType;
	WOutputImageT(ImageType& _image,
				  const QRect& _roi)
		: WInputImageT<T>(_image,
						  _roi.topLeft())
		, m_image(_image)
		, m_roi(_roi)
	{
	}
	operator T* ()
	{
		//  NOTE : y=row, x=col
		return m_image->ptr<T>(m_roi.y(),m_roi.x());
	}
	cv::Mat matrix() const
	{
		return WInputImageT<T>::matrix(m_roi);
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
	bool canOperateFrom(const WInputImageT<T>& i0) const
	{
		return i0.canExpandTo(m_roi.size());
	}
	bool canOperateFrom(const WInputImageT<T>& i0, const WInputImageT<T>& i1) const
	{
		QSize size = m_roi.size();
		return i0.canExpandTo(size)
			&& i1.canExpandTo(size);
	}
protected:
	ImageType& m_image;
	QRect m_roi;
};

template<typename T>
class WImageT : public WImage
{
public:
	typedef WImageTypeTrait<T> Trait;
    WImageT(const WImage& source)
	{
		if (Trait::openCvMatDepth==source->depth()) {
			*(WImage*)this = source;
		}
	}
	// TODO CHECKME should be virtual or not?
	// maybe not. see opencv comment on cv::Mat_ class in core.hpp
    ~WImageT()
	{
	}
	operator WInputImageT<T>() const
	{
		return WInputImageT<T>(*this, QPoint(0,0));
	}
	WInputImageT<T> operator () (const QPoint& topLeft) const
	{
		return WInputImageT<T>(*this, topLeft);
	}
	operator WOutputImageT<T>()
	{
		const cv::Mat& mat = (const cv::Mat&)(*this);
		return WOutputImageT<T>(*this, QRect(0,0,mat.cols,mat.cols));
	}
	WOutputImageT<T> operator ()(const QRect& roi)
	{
		return WOutputImageT<T>(*this, roi);
	}
};
