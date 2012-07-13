#include "WGraphicsArrowItem.h"
#include "WGraphicsUtil.h"
#include <QPainter>
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

WGraphicsArrowItem::WGraphicsArrowItem(QGraphicsItem* startNode,
									   QGraphicsItem* endNode,
									   QGraphicsItem* parent)
	: QGraphicsItem(parent)
	, m_startNode(startNode)
	, m_endNode(endNode)
{
	setDefaultParameter();

	setAcceptedMouseButtons(0);
    adjust();
}

WGraphicsArrowItem::WGraphicsArrowItem(const QPointF& startPos,
									   const QPointF& endPos,
									   QGraphicsItem* parent)
	: QGraphicsItem(parent)
	, m_startNode(0)
	, m_endNode(0)
	, m_line(startPos, endPos)
{
	setDefaultParameter();
}

WGraphicsArrowItem::WGraphicsArrowItem(const QLineF& line,
									   QGraphicsItem* parent)
	: QGraphicsItem(parent)
	, m_startNode(0)
	, m_endNode(0)
	, m_line(line)
{
	setDefaultParameter();
}

void WGraphicsArrowItem::adjust()
{
    if (!m_startNode || !m_endNode)
        return;

    QLineF line(mapFromItem(m_startNode, 0, 0), mapFromItem(m_endNode, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > m_minDisplayableSize) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        m_line.setP1(line.p1() + edgeOffset);
        m_line.setP2(line.p2() - edgeOffset);
    } else {
        m_line.setPoints(line.p1(), line.p1());
    }
}

QRectF WGraphicsArrowItem::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = (penWidth + m_arrowSize) / 2.0;

    return QRectF(m_line.p1(), QSizeF(m_line.dx(),// m_endPos.x() - m_startPos.x(),
									  m_line.dy())) //m_endPos.y() - m_startPos.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void WGraphicsArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    const QLineF& line = m_line;

    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(m_pen);
    painter->drawLine(line);

    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

	painter->setBrush(Qt::black);

	QPointF startPos = m_line.p1();
	QPointF endPos = m_line.p2();
	if (!m_uniDirectedArrow) {
		// QPointF startNodeArrowP1 = startPos + QPointF(sin(angle + Pi / 3) * m_arrowSize,
		// 											  cos(angle + Pi / 3) * m_arrowSize);
		// QPointF startNodeArrowP2 = startPos + QPointF(sin(angle + Pi - Pi / 3) * m_arrowSize,
		// 											  cos(angle + Pi - Pi / 3) * m_arrowSize);
		// painter->drawPolygon(QPolygonF() << line.p1() << startNodeArrowP1 << startNodeArrowP2);
		QLineF arrowPoints = Wf::getArrowPoints(endPos, startPos, m_arrowSize);
		painter->drawPolygon(QPolygonF() << line.p1() << arrowPoints.p1() << arrowPoints.p2());
	}

	{
		// QPointF endNodeArrowP1 = endPos + QPointF(sin(angle - Pi / 3) * m_arrowSize,
		// 										  cos(angle - Pi / 3) * m_arrowSize);
		// QPointF endNodeArrowP2 = endPos + QPointF(sin(angle - Pi + Pi / 3) * m_arrowSize,
		// 										  cos(angle - Pi + Pi / 3) * m_arrowSize);
		// painter->drawPolygon(QPolygonF() << line.p2() << endNodeArrowP1 << endNodeArrowP2);
		QLineF arrowPoints = Wf::getArrowPoints(startPos, endPos, m_arrowSize);
		painter->drawPolygon(QPolygonF() << line.p2() << arrowPoints.p1() << arrowPoints.p2());
	}
}

void WGraphicsArrowItem::setDefaultParameter()
{
	m_arrowSize = 10;
	m_minDisplayableSize = 20.;
	m_uniDirectedArrow = true;
}
