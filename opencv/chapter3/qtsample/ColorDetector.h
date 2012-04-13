#pragma once

#include "types.h"
#include <QObject>

class ColorDetector : public QObject
{
    Q_OBJECT
public:
    ColorDetector(QObject* parent=0);
    virtual ~ColorDetector();
	void setImage(ColorBuffer& imageBuffer);
	bool setImageFile(const QString& fileNamePath);
	void setTargetColor(const ColorPixel& targetColor);
	QColor targetColor() const;
	int threshold() const;
signals:
	void thresholdChanged(int threshold);
	void targetColorChanged(QColor color);
	void sourceImageChanged(const ColorBuffer& buffer);
	void sourceImageChanged(const QPixmap& pixmap);
	void processed(const MonoBuffer& buffer);
public slots:
	void process();
	void setThreshold(int threshold);
	void setTargetColor(const QColor& targetColor);
protected:
	// buffer
	ColorBuffer m_inBuffer;
	MonoBuffer m_outBuffer;

	// parameter
	ColorPixel m_targetColor;
	int m_threshold;

	const MonoBuffer& process(ColorBuffer& image);
	int getDistance(const ColorPixel& pixel) const;
};