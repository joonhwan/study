#pragma once

#include "wimage_p.h"
#include <opencv2/opencv.hpp>
#include <QSharedDataPointer>
#include <QRect>
#include <string>

// Shared cv::Mat class
// using Qt's QSharedDataPointer
class WImage
{
public:
	WImage();
	WImage(const WImage& source);
	WImage(const cv::Mat& source);
	//! constructs 2D matrix of the specified size and type
    // (_type is CV_8UC1, CV_64FC3, CV_32SC(12) etc.)
    WImage(int _rows, int _cols, int _type);
    WImage(cv::Size _size, int _type);
    //! constucts 2D matrix and fills it with the specified value _s.
    WImage(int _rows, int _cols, int _type, const cv::Scalar& _s);
    WImage(cv::Size _size, int _type, const cv::Scalar& _s);
    //! constructs n-dimensional matrix
    WImage(int _ndims, const int* _sizes, int _type);
    WImage(int _ndims, const int* _sizes, int _type, const cv::Scalar& _s);
    //! constructor for matrix headers pointing to user-allocated data
    WImage(int _rows, int _cols, int _type, void* _data, size_t _step=cv::Mat::AUTO_STEP);
    WImage(cv::Size _size, int _type, void* _data, size_t _step=cv::Mat::AUTO_STEP);
    WImage(int _ndims, const int* _sizes, int _type, void* _data, const size_t* _steps=0);
    //! creates a matrix header for a part of the bigger matrix
    WImage(const WImage& m, const cv::Range& rowRange, const cv::Range& colRange=cv::Range::all());
    WImage(const WImage& m, const cv::Rect& roi);
    WImage(const WImage& m, const cv::Range* ranges);
    //! converts old-style CvMat to the new matrix; the data is not copied by default
    WImage(const CvMat* m, bool copyData=false);
    //! converts old-style CvMatND to the new matrix; the data is not copied by default
    WImage(const CvMatND* m, bool copyData=false);
    //! converts old-style IplImage to the new matrix; the data is not copied by default
    WImage(const IplImage* img, bool copyData=false);
	~WImage() // should be virtual?
	{
	}
	void create(int width, int height, int type);
	void create(int width, int height, int type, const cv::Scalar& s);
	int width() const;
	int height() const;
	QSize size() const;
	void convertFrom(const WImage& source);

	// origianl cv::Mat accessor
	// to call function like image->matrix().depth()
	// or (*image)->depth()
	// or (*image).matrix().depth()
	// ...
	//
	// 주의 : pixel wise하게 접근하는 경우, refcount확인 루틴이
	// overhead. 이 경우를 위한 visitor pattern의 도입
	cv::Mat* operator->()
	{
		return &d->m_buffer;
	}
	const cv::Mat* operator->() const
	{
		return &d->m_buffer;
	}
	cv::Mat& matrix()
	{
		return d->m_buffer;
	}
	const cv::Mat& matrix() const
	{
		return d->m_buffer;
	}
	operator cv::Mat&()
	{
		return d->m_buffer;
	}
	operator const cv::Mat&() const
	{
		return d->m_buffer;
	}
	operator cv::_InputArray() const
	{
		return cv::_InputArray(d->m_buffer);
	}
	operator cv::_OutputArray()
	{
		return cv::_OutputArray(d->m_buffer);
	}
	operator cv::_OutputArray() const
	{
		return cv::_OutputArray(d->m_buffer);
	}
	operator bool () const
	{
		return d->m_buffer.data;
	}
	WImage& operator = (const WImage& rhs)
	{
		d = rhs.d;
		return *this;
	}
	void doConstThing() const
	{
	}
	void doNonConstThing()
	{
	}
	cv::Mat operator()( const QRect& roi ) const;
private:
	QSharedDataPointer<WImagePrivate> d;
};

template<>
WImagePrivate* QSharedDataPointer<WImagePrivate>::clone();

#include "wimage.inl"
