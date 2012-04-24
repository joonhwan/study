#include "WIntensityProfileWidget.h"
#include <QPainter>

WIntensityProfileWidget::WIntensityProfileWidget(QWidget* parent)
{
}

//virtual
WIntensityProfileWidget::~WIntensityProfileWidget()
{
}

void WIntensityProfileWidget::setProfile(const QList<int>& profile)
{
	m_profile = profile;
	if (profile.size()) {
		
	}
	update();
}

//virtual
void WIntensityProfileWidget::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.setBrush(Qt::red);
	painter.drawRect(QRect(QPoint(0,0),
						   size()));
	if (m_profile.empty()) {
		return;
	}

	painter.setWindow(QRect(QPoint(0,0),
							QSize(m_profile.size(),0xff*3)));
	for (int x = 0; x < m_profile.size(); ++x) {
		painter.drawRect(x, 0, 1, m_profile[x]);
	}
}
