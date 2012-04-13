#pragma once

#include "types.h"
#include "PropertyManager.h"

class ColorDetector : public PropertyManager
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
	Property<ColorPixel> m_targetColor;
	Property<int> m_threshold;

	virtual void onValueChanged(QtVariantProperty* property,
								void* id,
								const QVariant& value);
	const MonoBuffer& process(ColorBuffer& image);
	int getDistance(const ColorPixel& pixel) const;
};
