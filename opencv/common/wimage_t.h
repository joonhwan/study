#pragma once

#include "wimagebuffer_t.h"

class QRect;

template<typename T, int C>
class WImageT : public WConstImageT<T,C>
{
	WImageT(); // cannot use this ctor
public:
	typedef WImageBufferT<T,C> ImageType;
	WImageT(ImageType& _image, const QRect& _roi)
		: WConstImageT<T,C>(_image, _roi)
	{
	}
	WImageT(ImageType& _image)
		: WConstImageT<T,C>(_image)
	{
	}
	operator T* ()
	{
		//  NOTE : y=row, x=col
		return m_matrix.ptr<T>(m_roi.y(),m_roi.x());
	}
	bool canOperateFrom(const WConstImageT<T,C>& i0) const
	{
		return i0.canExpandTo(m_roi.size());
	}
	bool canOperateFrom(const WConstImageT<T,C>& i0, const WConstImageT<T,C>& i1) const
	{
		QSize size = m_roi.size();
		return i0.canExpandTo(size)
			&& i1.canExpandTo(size);
	}
	operator cv::_OutputArray()
	{
		return cv::_OutputArray(m_matrix);
	}
	operator cv::Mat()
	{
		return m_matrix;
	}
};


