#pragma once

#include <QWidget>

class WIntensityProfileWidget : public QWidget
{
    Q_OBJECT
public:
    WIntensityProfileWidget(QWidget* parent=0);
    virtual ~WIntensityProfileWidget();
signals:
public slots:
	void setProfile(const QList<int>& profile);
protected:
	virtual void paintEvent(QPaintEvent* e);
private:
	QList<int> m_profile;
};
