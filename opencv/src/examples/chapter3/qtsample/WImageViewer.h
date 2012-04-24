#pragma once

#include <QFrame>

class QGraphicsScene;
class QGraphicsView;
class QSlider;
class QToolButton;
class WImageViewerGraphicsScene;

class WImageViewer : public QFrame
{
    Q_OBJECT
public:
    WImageViewer(QWidget* parent=0);
    virtual ~WImageViewer();
signals:

public slots:
	void setPixmap(const QPixmap& pixmap);
	void zoomIn(int level=1);
	void zoomOut(int level=1);
	void zoomReset();
private slots:
	void setupMatrix();
private:
	void drawImage(QPainter* painter, const QRectF& rect);
	void drawTextPath(QPainter* painter, const QFont& font, const QRectF& rect, const QString& text);
	qreal scale() const;

	QImage m_image;
	QGraphicsView* m_graphicsView;
	WImageViewerGraphicsScene* m_scene;
	QToolButton* m_zoomResetButton;
	QSlider* m_zoomSlider;
	friend class WImageViewerGraphicsScene;
};

