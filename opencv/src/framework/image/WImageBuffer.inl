#include <QtCore/qmath.h>

inline
WImageBuffer::WImageBuffer()
{
	d = new WImageBufferPrivate;
}

inline
WImageBuffer::WImageBuffer(const WImageBuffer& source)
{
	d = source.d;
}

inline
WImageBuffer::WImageBuffer(const cv::Mat& source)
{
	d = new WImageBufferPrivate(source);
}

inline
WImageBuffer::WImageBuffer(int _rows, int _cols, int _type)
{
	d = new WImageBufferPrivate(_rows, _cols, _type);
}

inline
WImageBuffer::WImageBuffer(cv::Size _size, int _type)
{
	d = new WImageBufferPrivate(_size, _type);
}

inline
WImageBuffer::WImageBuffer(int _rows, int _cols, int _type, const cv::Scalar& _s)
{
	d = new WImageBufferPrivate(_rows, _cols, _type, _s);
}

inline WImageBuffer::WImageBuffer(cv::Size _size, int _type, const cv::Scalar& _s)
{
	d = new WImageBufferPrivate(_size, _type, _s);
}

inline
WImageBuffer::WImageBuffer(int _ndims, const int* _sizes, int _type)
{
	d = new WImageBufferPrivate(_ndims, _sizes, _type);
}

inline
WImageBuffer::WImageBuffer(int _ndims, const int* _sizes, int _type, const cv::Scalar& _s)
{
	d = new WImageBufferPrivate(_ndims, _sizes, _type, _s);
}

inline
WImageBuffer::WImageBuffer(int _rows, int _cols, int _type, void* _data, size_t _step)
{
	d = new WImageBufferPrivate(_rows, _cols, _type, _data, _step);
}

inline
WImageBuffer::WImageBuffer(cv::Size _size, int _type, void* _data, size_t _step)
{
	d = new WImageBufferPrivate(_size, _type, _data, _step);
}

inline
WImageBuffer::WImageBuffer(int _ndims, const int* _sizes, int _type, void* _data, const size_t* _steps)
{
	d = new WImageBufferPrivate(_ndims, _sizes, _type, _data, _steps);
}

inline
WImageBuffer::WImageBuffer(const WImageBuffer& m, const cv::Range& rowRange, const cv::Range& colRange)
{
	d = new WImageBufferPrivate(m.d->m_buffer, rowRange, colRange);
}

inline
WImageBuffer::WImageBuffer(const WImageBuffer& m, const cv::Rect& roi)
{
	d = new WImageBufferPrivate(m.d->m_buffer, roi);
}

inline
WImageBuffer::WImageBuffer(const WImageBuffer& m, const cv::Range* ranges)
{
	d = new WImageBufferPrivate(m.d->m_buffer, ranges);
}

inline
WImageBuffer::WImageBuffer(const CvMat* m, bool copyData)
{
	d = new WImageBufferPrivate(m, copyData);
}

inline
WImageBuffer::WImageBuffer(const CvMatND* m, bool copyData)
{
	d = new WImageBufferPrivate(m, copyData);
}

inline
WImageBuffer::WImageBuffer(const IplImage* img, bool copyData)
{
	d = new WImageBufferPrivate(img, copyData);
}

inline
void WImageBuffer::create(int width, int height, int type)
{
	d = new WImageBufferPrivate(height/*rows*/, width/*cols*/, type);
}

inline
void WImageBuffer::create(int width, int height, int type, const cv::Scalar& s)
{
	d = new WImageBufferPrivate(height/*rows*/, width/*cols*/, type, s);
}

inline
int WImageBuffer::width() const
{
	return d->m_buffer.cols;
}

inline
int WImageBuffer::height() const
{
	return d->m_buffer.rows;
}

inline
QSize WImageBuffer::size() const
{
	const cv::Mat& mat = d->m_buffer;
	QSize size_(mat.cols, mat.rows);
	return size_;
}

inline
cv::Size WImageBuffer::sizeCv() const
{
	const cv::Mat& mat = d->m_buffer;
	cv::Size size_(mat.cols, mat.rows);
	return size_;
}

inline
QPointF WImageBuffer::center() const
{
	const cv::Mat& mat = d->m_buffer;
	double x = qFloor(mat.cols / 2.);
	double y = qFloor(mat.rows / 2.);
	return QPointF(x, y);
}

inline
cv::Point2f WImageBuffer::centerCv() const
{
	const cv::Mat& mat = d->m_buffer;
	float x = qFloor(mat.cols / 2.);
	float y = qFloor(mat.rows / 2.);
	return cv::Point2f(x, y);
}

