#include "image/WImageBuffer.h"

#include <QString>

template<>
WImageBufferPrivate* QSharedDataPointer<WImageBufferPrivate>::clone()
{
	cv::Mat cloned;
	d->m_buffer.copyTo(cloned);
	return new WImageBufferPrivate(cloned);
}

cv::Mat WImageBuffer::operator()(const QRect& _roi) const
{
	cv::Rect roi(
		_roi.x(),
		_roi.y(),
		_roi.width(),
		_roi.height()
		);
	return d->m_buffer(roi);
}

void WImageBuffer::copyFrom(const WImageBuffer& source)
{
	((const cv::Mat&)source).copyTo(*this);
}

void WImageBuffer::loadFromFile(const QString& filePathName)
{
	d->m_buffer = cv::imread(filePathName.toLocal8Bit().data());
}

