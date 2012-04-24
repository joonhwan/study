#include "WImageViewerPixelItem.h"

#include <QFont>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>

namespace {

const QSizeF pixelSize(40, 40);

}

WImageViewerPixelItem::WImageViewerPixelItem(int x, int y, const QRgb& color)
	: m_color(color)
{
	setPos(x,y);
	setFlags(0);
	setAcceptsHoverEvents(true);
}

//virtual
WImageViewerPixelItem::~WImageViewerPixelItem()
{
}

//virtual
QRectF WImageViewerPixelItem::boundingRect() const
{
	return QRectF(QPoint(0,0), pixelSize);
}

//virtual
void WImageViewerPixelItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
								  QWidget* widget)
{
	painter->setClipRect(option->exposedRect);
	const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
	QRectF br = boundingRect();
	// painter->fillRect(br, m_color);
	if (lod < 0.6) {
		return;
	}

	QFont font("Arial", 10);
	font.setStyleStrategy(QFont::ForceOutline);
	QFont oldFont = painter->font();
	painter->setFont(font);
	painter->drawText(QPointF(0,0), m_color.name());
	painter->setFont(oldFont);
}

