inline
WImage::WImage()
{
	d = new WImagePrivate;
}

inline
WImage::WImage(const WImage& source)
{
	d = source.d;
}

inline
WImage::WImage(const cv::Mat& source)
{
	d = new WImagePrivate(source);
}

inline
WImage::WImage(int _rows, int _cols, int _type)
{
	d = new WImagePrivate(_rows, _cols, _type);
}

inline
WImage::WImage(cv::Size _size, int _type)
{
	d = new WImagePrivate(_size, _type);
}

inline
WImage::WImage(int _rows, int _cols, int _type, const cv::Scalar& _s)
{
	d = new WImagePrivate(_rows, _cols, _type, _s);
}

inline WImage::WImage(cv::Size _size, int _type, const cv::Scalar& _s)
{
	d = new WImagePrivate(_size, _type, _s);
}

inline
WImage::WImage(int _ndims, const int* _sizes, int _type)
{
	d = new WImagePrivate(_ndims, _sizes, _type);
}

inline
WImage::WImage(int _ndims, const int* _sizes, int _type, const cv::Scalar& _s)
{
	d = new WImagePrivate(_ndims, _sizes, _type, _s);
}

inline
WImage::WImage(int _rows, int _cols, int _type, void* _data, size_t _step)
{
	d = new WImagePrivate(_rows, _cols, _type, _data, _step);
}

inline
WImage::WImage(cv::Size _size, int _type, void* _data, size_t _step)
{
	d = new WImagePrivate(_size, _type, _data, _step);
}

inline
WImage::WImage(int _ndims, const int* _sizes, int _type, void* _data, const size_t* _steps)
{
	d = new WImagePrivate(_ndims, _sizes, _type, _data, _steps);
}

inline
WImage::WImage(const WImage& m, const cv::Range& rowRange, const cv::Range& colRange)
{
	d = new WImagePrivate(m.d->m_buffer, rowRange, colRange);
}

inline
WImage::WImage(const WImage& m, const cv::Rect& roi)
{
	d = new WImagePrivate(m.d->m_buffer, roi);
}

inline
WImage::WImage(const WImage& m, const cv::Range* ranges)
{
	d = new WImagePrivate(m.d->m_buffer, ranges);
}

inline
WImage::WImage(const CvMat* m, bool copyData)
{
	d = new WImagePrivate(m, copyData);
}

inline
WImage::WImage(const CvMatND* m, bool copyData)
{
	d = new WImagePrivate(m, copyData);
}

inline
WImage::WImage(const IplImage* img, bool copyData)
{
	d = new WImagePrivate(img, copyData);
}


