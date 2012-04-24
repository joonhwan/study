#include "ColorDetector.h"
#include "AlgoPropertySystem.h"

#include <math.h>

ColorDetector::ColorDetector(AlgoPropertySystem* system,
							 QObject* parent)
	: AlgoPropertyManager(tr("Color Detector"), system, parent)
	, m_targetColor(tr("Target Color"), ColorPixel(0,255,0))
	, m_threshold(tr("Threshold"), 100, 0, 1000)
{
	addProperty(m_targetColor);
	addProperty(m_threshold);
}

//virtual
ColorDetector::~ColorDetector()
{
}

void ColorDetector::setImage(ColorBuffer& imageBuffer)
{
	m_inBuffer = imageBuffer;
	if (m_inBuffer.isValid()) {
		emit sourceImageChanged(m_inBuffer);
		emit sourceImageChanged(m_inBuffer.toImage());
		process();
	}
}

bool ColorDetector::setImageFile(const QString& filePathName)
{
	bool done = m_inBuffer.loadFromFile(filePathName);
	if (done && m_inBuffer.isValid()) {
		emit sourceImageChanged(m_inBuffer);
		emit sourceImageChanged(m_inBuffer.toImage());
		process();
	}
	return done;
}

void ColorDetector::setTargetColor(const ColorPixel& targetColor)
{
	if (m_targetColor != targetColor) {
		m_targetColor = targetColor;
		QColor color = targetColor.toQColor();
		emit targetColorChanged(color);

		process();
	}
}

QColor ColorDetector::targetColor() const
{
	return m_targetColor.value().toQColor();
}

int ColorDetector::threshold() const
{
	return m_threshold;
}

const MonoBuffer& ColorDetector::process(ColorBuffer& image)
{
	if (m_outBuffer.size() != image.size()) {
		m_outBuffer = MonoBuffer(image.size());
	}
	ColorBuffer::const_iterator itIn = image.begin();
	ColorBuffer::const_iterator itInEnd = image.end();
	MonoBuffer::iterator itOut = m_outBuffer.begin();
	MonoBuffer::iterator itOutEnd = m_outBuffer.end();
	for ( ;itIn != itInEnd && itOut != itOutEnd; ++itIn, ++itOut) {
		if (getDistance(*itIn) > m_threshold) {
			*itOut = 0xFF;
		} else {
			*itOut = 0;
		}
	}
	emit processed(m_outBuffer);
	return m_outBuffer;
}

void ColorDetector::setThreshold(int threshold)
{
	if (m_threshold != threshold) {
		m_threshold = threshold;
		emit thresholdChanged(threshold);

		process();
	}
}

void ColorDetector::setTargetColor(const QColor& targetColor)
{
	if (m_targetColor.value().toQColor() != targetColor) {
		m_targetColor = targetColor;
		emit targetColorChanged(targetColor);

		process();
	}
}

void ColorDetector::process()
{
	if (m_inBuffer.isValid()) {
		process(m_inBuffer);
	}
}

int ColorDetector::getDistance(const ColorPixel& pixel) const
{
	return
		abs(pixel.r() - m_targetColor.value().r())
		+ abs(pixel.g() - m_targetColor.value().g())
		+ abs(pixel.b() - m_targetColor.value().b());
}

//virtual
void ColorDetector::onValueChanged(QtProperty* property,
								   void* id,
								   const QVariant& variant)
{
	// addIntProperty(tr("Threshold"), m_threshold, 0, 1000);
	// addColorProperty(tr("Target Color"), m_targetColor.toQColor());
	if (id == m_threshold.id()) {
		setThreshold(variant.value<int>());
	} else if (id == m_targetColor.id()) {
		setTargetColor(variant.value<QColor>());
	}
}
