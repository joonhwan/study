#pragma once

#include "image/WImageBufferT.h"
#include "image/WImageUtils.h"
#include "image/wpixel.h"
#include <QRect>
#include <QSize>
#include <ippi.h>

template<typename T, int C>
class WImageBufferT;

template<typename T, int C>
class WConstImageT
{
	WConstImageT(); // cannot use thi ctor
public:
	typedef const WImageBufferT<T,C> BufferType;
	typedef WPixelValue<T,C> PixelValue;
	typedef WPixelPosition<T,C> PixelPosition;

	WConstImageT(const BufferType& _const_buffer,
				 const QPoint& _topLeft)
		: m_roi(_topLeft, QSize(0,0))
		, m_roiTopLeftFractionalPart(0,0)
	{
		const cv::Mat& mat = (const cv::Mat&)_const_buffer;
		m_roi.setRight(mat.cols-1);
		m_roi.setBottom(mat.rows-1);
		m_matrix = mat(qRectToCvRect(m_roi));
	}
	WConstImageT(const BufferType& _const_buffer,
				 const QRect& roi)
		: m_roi(roi)
		, m_roiTopLeftFractionalPart(0,0)
	{
		const cv::Mat& mat = (const cv::Mat&)_const_buffer;
		m_matrix = mat(qRectToCvRect(m_roi));
	}
	WConstImageT(const BufferType& _const_buffer,
				 const QPointF& topLeftF,
				 const QSize& size)
	{
		QPoint topLeft(int(topLeftF.x()),
					   int(topLeftF.y()));
		m_roi = QRect(topLeft, size);
		m_roiTopLeftFractionalPart = topLeftF - topLeft;

		const cv::Mat& mat = (const cv::Mat&)_const_buffer;
		m_matrix = mat(qRectToCvRect(m_roi));
	}
	WConstImageT(const BufferType& _const_buffer)
		: m_roiTopLeftFractionalPart(0,0)
	{
		// full roi
		const cv::Mat& mat = (const cv::Mat&)_const_buffer;
		m_roi = QRect(0,0,mat.cols,mat.rows);
		m_matrix = mat(qRectToCvRect(m_roi));
	}
	WConstImageT(cv::Mat& matrix, const QRect& roi)
		: m_roi(roi)
		, m_roiTopLeftFractionalPart(0,0)
	{
		m_matrix = matrix(qRectToCvRect(roi));
	}
	WConstImageT(cv::Mat& matrix)
		: m_matrix(matrix)
		, m_roiTopLeftFractionalPart(0,0)
	{
		m_roi = QRect(0,0,m_matrix.cols,m_matrix.rows);
	}
	cv::Mat matrix(int width, int height) const
	{
		QRect roi(m_roi.x(), m_roi.y(),
				  width, height);
		// generated object will be copied in a shallow way.
		return matrix(roi);
	}
	cv::Mat matrix(const QSize& roiSize) const
	{
		return matrix(QRect(m_roi.topLeft(),
							roiSize));
	}
	cv::Mat matrix(const QRect& roi) const
	{
		// shallow copy by +1 to refCount
		return m_matrix(qRectToCvRect(roi));
	}
	cv::Mat matrix() const
	{
		// shallow copy by +1 to refCount
		return m_matrix;
	}
	operator const T* () const
	{
		//  NOTE : y=row, x=col
		return m_matrix.ptr<T>(m_roi.y(), m_roi.x());
	}
	operator cv::Mat() const
	{
		return matrix();
	}
	operator cv::_InputArray() const
	{
		return cv::_InputArray(m_matrix);
	}
	int channels() const
	{
		// return C;
		return m_matrix.channels();
	}
	int step() const
	{
		return m_matrix.step;
	}
	bool isValid() const
	{
		const cv::Mat& mat = (const cv::Mat&)m_matrix;
		return mat.dims == 2
			&& mat.cols > 0
			&& mat.rows > 0
			&& mat.data
			&& QRect(0,0,mat.cols,mat.rows).canInclude(m_roi);
	}
	// dimension 에 대한 check도 canInclude로 된다.(side effect).
	// 2차원인경우에만, rows > 0 , cols > 0 이다.
	bool canInclude(const QRect& roi) const
	{
		const cv::Mat& mat = (const cv::Mat&)m_matrix;
		return QRect(0,0,mat.cols,mat.rows).contains(m_roi)
	}
	bool canExpandTo(const QSize& roiSize) const
	{
		return canInclude(QRect(m_roi.topLeft(), roiSize));
	}
	bool hasSameChannelWith(const WConstImageT<T,C>& i0) const
	{
		return m_matrix.channels() == i0.m_matrix.channels();
	}
	bool hasSameChannelWith(const WConstImageT<T,C>& i0, const WConstImageT<T,C>& i1) const
	{
		// C ?
		int channel = m_matrix.channels();
		return channel == i0.m_matrix.channels()
			&& channel == i1.m_matrix.channels();
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
	const QPointF& roiTopLeftFractionalPart() const
	{
		return m_roiTopLeftFractionalPart;
	}
protected:
	cv::Mat m_matrix;
	QRect m_roi;
	// to support ipp's copySubpix() in a more natural way.
	QPointF m_roiTopLeftFractionalPart;
};
