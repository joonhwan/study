#include "WGraphicsUtil.h"
#include <math.h>

namespace {

const double Pi = 3.14159265358979323846264338327950288419717;
const double TwoPi = 2.0 * Pi;
const double RadianPerDegree = Pi/2./90.;
}

namespace Wf {

QLineF getArrowPoints(const QPointF& start,
					  const QPointF& end,
					  double size,
					  double arrowAngleDegree)
{
	QLineF line(start, end);
	double angle = ::acos(line.dx() / line.length());
	if (line.dy() >= 0) {
		angle = TwoPi - angle;
	}

	arrowAngleDegree = fmod(arrowAngleDegree, 90.);
	qreal modAngle = RadianPerDegree * (90-arrowAngleDegree);
	QPointF p1 = QPointF(sin(angle - modAngle)*size,
						 cos(angle - modAngle)*size);
	QPointF p2 = QPointF(sin(angle - Pi + modAngle)*size,
						 cos(angle - Pi + modAngle)*size);
	return QLineF(p1+end, p2+end);
}

} // namespace Wf
