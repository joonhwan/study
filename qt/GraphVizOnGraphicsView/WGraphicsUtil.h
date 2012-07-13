#pragma once

#include <QLineF>
#include <QPointF>
#include <QtGlobal>

namespace Wf {

QLineF getArrowPoints(const QPointF& start,
					  const QPointF& end,
					  double size,
					  double arrowAngleDegree = 30.);

}
