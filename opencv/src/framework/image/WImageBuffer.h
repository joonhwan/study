#pragma once

#include "image/WImageBufferPrivate.h"
#include <opencv2/opencv.hpp>
#include <QSharedDataPointer>
#include <QRect>
#include <string>

class QString;

// Shared cv::Mat class
// using Qt's QSharedDataPointer
class WImageBuffer
{
public:
	WImageBuffer();
	WImageBuffer(const WImageBuffer& source);
	WImageBuffer(const cv::Mat& source);
	// ----- from old cv::Mat constructor -----
	//! constructs 2D matrix of the specified size and type
    // (_type is CV_8UC1, CV_64FC3, CV_32SC(12) etc.)
    WImageBuffer(int _rows, int _cols, int _type);
    WImageBuffer(cv::Size _size, int _type);
    //! constucts 2D matrix and fills it with the specified value _s.
    WImageBuffer(int _rows, int _cols, int _type, const cv::Scalar& _s);
    WImageBuffer(cv::Size _size, int _type, const cv::Scalar& _s);
    //! constructs n-dimensional matrix
    WImageBuffer(int _ndims, const int* _sizes, int _type);
    WImageBuffer(int _ndims, const int* _sizes, int _type, const cv::Scalar& _s);
    //! constructor for matrix headers pointing to user-allocated data
    WImageBuffer(int _rows, int _cols, int _type, void* _data, size_t _step=cv::Mat::AUTO_STEP);
    WImageBuffer(cv::Size _size, int _type, void* _data, size_t _step=cv::Mat::AUTO_STEP);
    WImageBuffer(int _ndims, const int* _sizes, int _type, void* _data, const size_t* _steps=0);
    //! creates a matrix header for a part of the bigger matrix
    WImageBuffer(const WImageBuffer& m, const cv::Range& rowRange, const cv::Range& colRange=cv::Range::all());
    WImageBuffer(const WImageBuffer& m, const cv::Rect& roi);
    WImageBuffer(const WImageBuffer& m, const cv::Range* ranges);
    //! converts old-style CvMat to the new matrix; the data is not copied by default
    WImageBuffer(const CvMat* m, bool copyData=false);
    //! converts old-style CvMatND to the new matrix; the data is not copied by default
    WImageBuffer(const CvMatND* m, bool copyData=false);
    //! converts old-style IplImage to the new matrix; the data is not copied by default
    WImageBuffer(const IplImage* img, bool copyData=false);
	~WImageBuffer() // should be virtual?
	{
	}
	void create(int width, int height, int type);
	void create(int width, int height, int type, const cv::Scalar& s);
	int width() const;
	int height() const;
	QSize size() const;
	cv::Size sizeCv() const;
	QPointF center() const;
	cv::Point2f centerCv() const;
	void convertFrom(const WImageBuffer& source);
	void copyFrom(const WImageBuffer& source);
	void loadFromFile(const QString& filePathName);

	// origianl cv::Mat accessor
	// to call function like image->matrix().depth()
	// or (*image)->depth()
	// or (*image).matrix().depth()
	// ...
	//
	// 주의 : pixel wise하게 접근하는 경우, refcount확인 루틴이
	// overhead.
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
	bool isValid() const
	{
		return d->m_buffer.data;
	}
	WImageBuffer& operator = (const WImageBuffer& rhs)
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
	QSharedDataPointer<WImageBufferPrivate> d;
};

template<>
WImageBufferPrivate* QSharedDataPointer<WImageBufferPrivate>::clone();

#include "image/WImageBuffer.inl"
