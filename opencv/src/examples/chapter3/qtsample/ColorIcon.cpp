#include "ColorIcon.h"

#include <QPainter>
#include <QRect>

ColorIcon::ColorIcon(int w, int h,
					 const QColor& color,
					 int borderWidth,
					 const QColor& borderColor)
	: m_color(color)
	, m_borderColor(borderColor)
	, m_borderWidth(borderWidth)
	, m_image(w,h,QImage::Format_RGB888)
{
	setColor(color);
}

//virtual
ColorIcon::~ColorIcon()
{
}

void ColorIcon::setColor(const QColor& color)
{
	{
		QPainter painter(&m_image);
		QRect rect(QPoint(0,0), m_image.size());
		painter.fillRect(rect, m_color);
		painter.setPen(m_borderColor);
		painter.drawRect(rect.adjusted(m_borderWidth,
									   m_borderWidth,
									   -m_borderWidth,
									   -m_borderWidth));
	}
	QPixmap pixmap;
	pixmap.convertFromImage(m_image);
	this->swap(QIcon(pixmap));
}

const QColor& ColorIcon::color() const
{
	return m_color;
}

const QColor& ColorIcon::borderColor() const
{
	return m_borderColor;
}
