#pragma once

#include <QIcon>
#include <QImage>

class QColor;

class ColorIcon : public QIcon
{
public:
    ColorIcon(int w, int h,
			  const QColor& color,
			  int borderWidth = 1,
			  const QColor& borderColor = Qt::black);
    virtual ~ColorIcon();
	void setColor(const QColor& color);
	void setBorderColor(const QColor& borderColor);
	const QColor& color() const;
	const QColor& borderColor() const;
protected:
	QImage m_image;
	QColor m_color;
	int m_borderWidth;
	QColor m_borderColor;
};
