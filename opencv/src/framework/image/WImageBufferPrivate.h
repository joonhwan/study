#pragma once

#include <opencv2/opencv.hpp>
#include <QSharedData>
#include <vector>

class WImageBufferPrivate : public QSharedData
{
public:
    WImageBufferPrivate()
	{
	}
	//! constructs 2D matrix of the specified size and type
    // (_type is CV_8UC1, CV_64FC3, CV_32SC(12) etc.)
    WImageBufferPrivate(int _rows, int _cols, int _type)
		: m_buffer(_rows, _cols, _type)
	{
	}
    WImageBufferPrivate(cv::Size _size, int _type)
		: m_buffer(_size, _type)
	{
	}
    //! constucts 2D matrix and fills it with the specified value _s.
    WImageBufferPrivate(int _rows, int _cols, int _type, const cv::Scalar& _s)
		: m_buffer(_rows, _cols, _type, _s)
	{
	}
    WImageBufferPrivate(cv::Size _size, int _type, const cv::Scalar& _s)
		: m_buffer(_size, _type, _s)
	{
	}
    //! constructs n-dimensional matrix
    WImageBufferPrivate(int _ndims, const int* _sizes, int _type)
		: m_buffer(_ndims, _sizes, _type)
	{
	}
    WImageBufferPrivate(int _ndims, const int* _sizes, int _type, const cv::Scalar& _s)
		: m_buffer(_ndims, _sizes, _type, _s)
	{
	}
    WImageBufferPrivate(const cv::Mat& m)
		: m_buffer(m)
	{
	}
    //! constructor for matrix headers pointing to user-allocated data
    WImageBufferPrivate(int _rows, int _cols, int _type, void* _data, size_t _step=cv::Mat::AUTO_STEP)
		: m_buffer(_rows, _cols, _type, _data, _step)
	{
	}
    WImageBufferPrivate(cv::Size _size, int _type, void* _data, size_t _step=cv::Mat::AUTO_STEP)
		: m_buffer(_size, _type, _data, _step)
	{
	}
    WImageBufferPrivate(int _ndims, const int* _sizes, int _type, void* _data, const size_t* _steps=0)
		: m_buffer(_ndims, _sizes, _type, _data, _steps)
	{
	}
    //! creates a matrix header for a part of the bigger matrix
    WImageBufferPrivate(const cv::Mat& m, const cv::Range& rowRange, const cv::Range& colRange=cv::Range::all())
		: m_buffer(m, rowRange, colRange)
	{
	}
    WImageBufferPrivate(const cv::Mat& m, const cv::Rect& roi)
		: m_buffer(m, roi)
	{
	}
    WImageBufferPrivate(const cv::Mat& m, const cv::Range* ranges)
		: m_buffer(m, ranges)
	{
	}
    //! converts old-style Cvcv::Mat to the new matrix; the data is not copied by default
    WImageBufferPrivate(const CvMat* m, bool copyData=false)
		: m_buffer(m, copyData)
	{
	}
    //! converts old-style CvMatND to the new matrix; the data is not copied by default
    WImageBufferPrivate(const CvMatND* m, bool copyData=false)
		: m_buffer(m, copyData)
	{
	}
    //! converts old-style IplImage to the new matrix; the data is not copied by default
    WImageBufferPrivate(const IplImage* img, bool copyData=false)
		: m_buffer(img, copyData)
	{
	}
    //! builds matrix from std::vector with or without copying the data
    template<typename _Tp> explicit WImageBufferPrivate(const std::vector<_Tp>& vec, bool copyData=false)
		: m_buffer(vec, copyData)
	{
	}
    //! builds matrix from cv::Vec; the data is copied by default
    template<typename _Tp, int n> explicit WImageBufferPrivate(const cv::Vec<_Tp, n>& vec,
														 bool copyData=true)
		: m_buffer(vec, copyData)
	{
	}
    //! builds matrix from cv::Matx; the data is copied by default
    template<typename _Tp, int m, int n> explicit WImageBufferPrivate(const cv::Matx<_Tp, m, n>& mtx,
																bool copyData=true)
		: m_buffer(mtx, copyData)
	{
	}
    //! builds matrix from a 2D point
    template<typename _Tp> explicit WImageBufferPrivate(const cv::Point_<_Tp>& pt, bool copyData=true)
		: m_buffer(pt, copyData)
	{
	}
    //! builds matrix from a 3D point
    template<typename _Tp> explicit WImageBufferPrivate(const cv::Point3_<_Tp>& pt, bool copyData=true)
		: m_buffer(pt, copyData)
	{
	}
    //! builds matrix from comma initializer
    template<typename _Tp> explicit WImageBufferPrivate(const cv::MatCommaInitializer_<_Tp>& commaInitializer)
		: m_buffer(commaInitializer)
	{
	}
    //! download data from GpuMat
    explicit WImageBufferPrivate(const cv::gpu::GpuMat& m)
		: m_buffer(m)
	{
	}
    ~WImageBufferPrivate()
	{
	}
	cv::Mat m_buffer;
};
