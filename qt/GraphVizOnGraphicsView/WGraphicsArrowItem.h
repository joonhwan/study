#pragma once

#include <QGraphicsItem>
#include <QLineF>
#include <QPen>

class WGraphicsArrowItem : public QGraphicsItem
{
public:
    WGraphicsArrowItem(QGraphicsItem* startNode = 0,
					   QGraphicsItem* target = 0,
					   QGraphicsItem* parent = 0);
	WGraphicsArrowItem(const QPointF& start,
					   const QPointF& end,
					   QGraphicsItem* parent = 0);
	WGraphicsArrowItem(const QLineF& line,
					   QGraphicsItem* parent = 0);
    void adjust();

    enum { Type = UserType + 2 };
    int type() const { return Type; }

	QGraphicsItem* startNode() {
		return m_startNode;
	}
	QGraphicsItem* endNode() {
		return m_endNode;
	}
	QPointF startPos() const {
		return m_line.p1();
	}
	QPointF endPos() const {
		return m_line.p2();
	}
	const QLineF& line() const {
		return m_line;
	}
	void setPen(const QPen& pen) {
		m_pen = pen;
	}
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);
	void setDefaultParameter();
private:
	bool m_uniDirectedArrow;
	QPen m_pen;
    QGraphicsItem* m_startNode;
	QGraphicsItem* m_endNode;
	QLineF m_line;
    qreal m_arrowSize;
	qreal m_minDisplayableSize;
};
