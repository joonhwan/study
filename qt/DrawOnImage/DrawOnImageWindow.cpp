#include "DrawOnImageWindow.h"
#include <QPainter>

DrawOnImageWindow::DrawOnImageWindow(QWidget* parent)
	: QWidget(parent)
	, image(0)
{
	image = new QImage(":/road.jpg");
	QPainter painter(image);
	painter.fillRect(QRectF(10,10,5,10), QBrush(Qt::red));
}

//virtual
DrawOnImageWindow::~DrawOnImageWindow()
{
	delete image;
}

//virtual
void DrawOnImageWindow::paintEvent(QPaintEvent* event)
{
	QRect r(0,0,image->width(),image->height());

	QPainter painter(this);
	painter.drawImage(r, *image);
}
