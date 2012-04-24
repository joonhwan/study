#include "WImageViewer.h"
#include "WImageViewerPixelItem.h"
#include <QToolButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QtCore/qmath.h>

namespace {

const int MAXZOOM = 500;

}


class WImageViewerGraphicsScene : public QGraphicsScene
{
public:
	WImageViewerGraphicsScene(WImageViewer* viewer)
		: QGraphicsScene(viewer)
		, m_viewer(viewer)
	{
	}
protected:
	WImageViewer* m_viewer;
	virtual void drawBackground(QPainter* painter, const QRectF& rect)
	{
		QGraphicsScene::drawBackground(painter, rect);
		m_viewer->drawImage(painter, rect);
	}
};

WImageViewer::WImageViewer(QWidget* parent)
	: QFrame(parent)
{
	m_scene = new WImageViewerGraphicsScene(this);

	setFrameStyle(Sunken | StyledPanel);

	m_graphicsView = new QGraphicsView(this);
    m_graphicsView->setRenderHint(QPainter::Antialiasing, false);
    m_graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    m_graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	m_graphicsView->setScene(m_scene);

	QToolButton *zoomInButton = new QToolButton;
    zoomInButton->setAutoRepeat(true);
    zoomInButton->setAutoRepeatInterval(33);
    zoomInButton->setAutoRepeatDelay(0);
	zoomInButton->setText(tr("+"));
    // zoomInButton->setIcon(QPixmap(":/zoomin.png"));
    // zoomInButton->setIconSize(iconSize);
    QToolButton *zoomOutButton = new QToolButton;
    zoomOutButton->setAutoRepeat(true);
    zoomOutButton->setAutoRepeatInterval(33);
    zoomOutButton->setAutoRepeatDelay(0);
	zoomOutButton->setText(tr("-"));
    // zoomOutButton->setIcon(QPixmap(":/zoomout.png"));
    // zoomOutButton->setIconSize(iconSize);
    m_zoomResetButton = new QToolButton;
    m_zoomResetButton->setText(tr("0"));
    m_zoomResetButton->setEnabled(false);

    m_zoomSlider = new QSlider(Qt::Horizontal);
    m_zoomSlider->setMinimum(0);
    m_zoomSlider->setMaximum(MAXZOOM);
    m_zoomSlider->setValue(MAXZOOM/2);
    m_zoomSlider->setTickPosition(QSlider::TicksRight);

	connect(zoomInButton, SIGNAL(clicked()), SLOT(zoomIn()));
	connect(zoomOutButton, SIGNAL(clicked()), SLOT(zoomOut()));
	connect(m_zoomResetButton, SIGNAL(clicked()), SLOT(zoomReset()));
	connect(m_zoomSlider, SIGNAL(valueChanged(int)), SLOT(setupMatrix()));

	QHBoxLayout* zoomLayout = new QHBoxLayout;
	zoomLayout->addWidget(zoomInButton);
	zoomLayout->addWidget(zoomOutButton);
	zoomLayout->addWidget(m_zoomResetButton);
	zoomLayout->addWidget(m_zoomSlider);

	QGridLayout* layout = new QGridLayout;
	layout->addLayout(zoomLayout, 0, 0);
	layout->addWidget(m_graphicsView, 1, 0);
	setLayout(layout);
}

//virtual
WImageViewer::~WImageViewer()
{
}

void WImageViewer::setPixmap(const QPixmap& pixmap)
{
	//m_scene->setImage(pixmap.toImage());
	m_image = pixmap.toImage();
	m_scene->setSceneRect(QRectF(QPointF(0,0), m_image.size()));
	zoomReset();
	m_scene->update();

	// QList<QGraphicsItem*> allItems = m_scene->items();
	// foreach(QGraphicsItem* item, allItems) {
	// 	m_scene->removeItem(item);
	// 	delete item;
	// }

	// // QList<WImageViewerPixelItem*> items;
	// QImage image = pixmap.toImage();
	// QSize size = image.size();
	// for (int y = 0; y < size.height(); ++y) {
	// 	for (int x = 0; x < size.width(); ++x) {
	// 		// items.push_back(new WImageViewerPixelItem(x,y,image.pixel(x,y)));
	// 		m_scene->addItem(new WImageViewerPixelItem(x,y,image.pixel(x,y)));
	// 	}
	// }
	// // foreach(WImageViewerPixelItem* item, items) {
	// // 	delete item;
	// // }
}

void WImageViewer::zoomIn(int level)
{
	m_zoomSlider->setValue(m_zoomSlider->value() + level);
}

void WImageViewer::zoomOut(int level)
{
	m_zoomSlider->setValue(m_zoomSlider->value() - level);
}

void WImageViewer::zoomReset()
{
	m_zoomSlider->setValue(MAXZOOM/2);
	m_zoomResetButton->setEnabled(false);
}

void WImageViewer::setupMatrix()
{
	qreal scale = this->scale();
	QMatrix matrix;
	matrix.scale(scale, scale);
	m_graphicsView->setMatrix(matrix);
	m_zoomResetButton->setEnabled(true);
}

void WImageViewer::drawImage(QPainter* painter, const QRectF& rect)
{
	qreal scale = this->scale();
	if (scale >= 36) {
		// font.setStyleStrategy(QFont::ForceOutline);
		// QRectF textBox(0, 0, 2., 2.);
		// while (1)
		// {
		// 	QFontMetricsF metrics(font);
		// 	textBox = metrics.boundingRect("255");
		// 	if (textBox.width() < 1. &&
		// 		textBox.height() < 1/3.) {
		// 		break;
		// 	}
		// 	fontSizeF *= 0.8;
		// 	font.setPointSizeF(fontSizeF);
		// }
		// font.setPointSizeF(3);
		qreal fontScale = 0.02;
		QFont font = painter->font();
		painter->save();
		painter->scale(fontScale, fontScale);

		QSize imageSize = m_image.size();
		QPoint from = QPointF(rect.topLeft() - QPointF(0.5,0.5)).toPoint();
		QPoint to = QPointF(rect.bottomRight() + QPointF(0.5,0.5)).toPoint();
		qreal outlineThreshold = 180.;
		QPointF pixelCorner[5];

		qDebug() << "draw pixel info (x " << scale << ")  : " << from << " - " << to;
		for (int x = from.x(); x < to.x(); ++x) {
			for (int y = from.y(); y < to.y(); ++y) {
				if (x < 0
					|| x >= imageSize.width()
					|| y < 0
					|| y >= imageSize.height()) {
					continue;
				}

				QColor value = m_image.pixel(x,y);
				// painter->drawText(QRectF(x,y+1,1,1)/fontScale, Qt::AlignCenter, value.name());

				QRectF pixelBox(x/fontScale, y/fontScale, 1./fontScale, 1./fontScale);
				pixelCorner[0] = pixelBox.topLeft();
				pixelCorner[1] = pixelBox.topRight();
				pixelCorner[2] = pixelBox.bottomRight();
				pixelCorner[3] = pixelBox.bottomLeft();
				pixelCorner[4] = pixelBox.topLeft();
				painter->setPen(Qt::black);
				painter->setBrush(value);
				painter->drawPolygon(pixelCorner, 4);

				QRectF textRect = pixelBox;
				textRect.setHeight(pixelBox.height() / 3.);

				if (scale >= outlineThreshold) {
					painter->setPen(Qt::black);
					painter->setBrush(Qt::red);
					drawTextPath(painter, font, textRect, QString("%1").arg(value.red(), 3));
				} else {
					painter->setPen(Qt::red);
					painter->drawText(textRect, Qt::AlignCenter, QString("%1").arg(value.red(), 3));
				}

				textRect.translate(0, pixelBox.height()/3.);
				if (scale >= outlineThreshold) {
					painter->setBrush(Qt::green);
					drawTextPath(painter, font, textRect, QString("%1").arg(value.green(), 3));
				} else {
					painter->setPen(Qt::green);
					painter->drawText(textRect, Qt::AlignCenter, QString("%1").arg(value.green(), 3));
				}

				textRect.translate(0, pixelBox.height()/3.);
				if (scale >=outlineThreshold) {
					painter->setBrush(Qt::blue);
					drawTextPath(painter, font, textRect, QString("%1").arg(value.blue(), 3));
				} else {
					painter->setPen(Qt::blue);
					painter->drawText(textRect, Qt::AlignCenter, QString("%1").arg(value.blue(), 3));
				}
			}
		}
		painter->restore();
		// painter->setFont(oldFont);
	} else {
		painter->drawImage(0, 0, m_image);
	}
}

void WImageViewer::drawTextPath(QPainter* painter, const QFont& font, const QRectF& rect, const QString& text)
{
	QPainterPath path;
	path.addText(0, 0, font, text);
	QRectF bound = path.boundingRect();
	path.translate(rect.center() - bound.center());
	painter->drawPath(path);
}

qreal WImageViewer::scale() const
{
	return qPow(2., (m_zoomSlider->value()-MAXZOOM/2.) / (MAXZOOM/50.) );
}
