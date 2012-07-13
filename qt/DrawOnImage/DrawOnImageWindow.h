#pragma once

#include <QWidget>
#include <QImage>

class DrawOnImageWindow : public QWidget
{
    Q_OBJECT
public:
    DrawOnImageWindow(QWidget* parent=0);
    virtual ~DrawOnImageWindow();
signals:
public slots:
protected:
	virtual void paintEvent(QPaintEvent* event);

	QImage* image;
};
