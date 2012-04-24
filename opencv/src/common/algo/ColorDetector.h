#pragma once

#include "algo/AlgoTypes.h"
#include "algo/AlgoPropertyManager.h"

class AlgoPropertySystem;

class ColorDetector : public AlgoPropertyManager
{
    Q_OBJECT
public:
    ColorDetector(AlgoPropertySystem* system, QObject* parent=0);
    virtual ~ColorDetector();
	virtual void onValueChanged(QtProperty* property,
								void* id,
								const QVariant& value);
	void setImage(ColorBuffer& imageBuffer);
	bool setImageFile(const QString& fileNamePath);
	void setTargetColor(const ColorPixel& targetColor);
	QColor targetColor() const;
	int threshold() const;
signals:
	void thresholdChanged(int threshold);
	void targetColorChanged(QColor color);
	void sourceImageChanged(const ColorBuffer& buffer);
	void sourceImageChanged(const QImage& image);
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
	SimpleProperty<ColorPixel> m_targetColor;
	RangedProperty<int> m_threshold;
	const MonoBuffer& process(ColorBuffer& image);
	int getDistance(const ColorPixel& pixel) const;
};
