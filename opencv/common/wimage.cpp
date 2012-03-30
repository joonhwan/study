#include "wimage.h"

template<>
WImagePrivate* QSharedDataPointer<WImagePrivate>::clone()
{
	cv::Mat cloned;
	d->m_buffer.copyTo(cloned);
	return new WImagePrivate(cloned);
}

cv::Mat WImage::operator()(const QRect& _roi) const
{
	cv::Rect roi(
		_roi.x(),
		_roi.y(),
		_roi.width(),
		_roi.height()
		);
	return d->m_buffer(roi);
}
