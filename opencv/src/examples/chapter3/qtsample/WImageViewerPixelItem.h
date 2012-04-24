#pragma once

#include <QGraphicsItem>
#include <QColor>

class WImageViewerPixelItem : public QGraphicsItem
{
public:
	enum {
		Type = UserType + 1
	};
    WImageViewerPixelItem(int x, int y, const QRgb& color);
    virtual ~WImageViewerPixelItem();
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
					   QWidget* widget);
    virtual int type() const
    {
        return Type;
    }
protected:
	QColor m_color;
};
