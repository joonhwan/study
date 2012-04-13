#include "ColorDetector.h"
#include <math.h>

ColorDetector::ColorDetector(QObject* parent)
	: QObject(parent)
{
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
		emit sourceImageChanged(m_inBuffer.toPixmap());
		process();
	}
}

bool ColorDetector::setImageFile(const QString& filePathName)
{
	bool done = m_inBuffer.loadFromFile(filePathName);
	if (done && m_inBuffer.isValid()) {
		emit sourceImageChanged(m_inBuffer);
		emit sourceImageChanged(m_inBuffer.toPixmap());
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
	return m_targetColor.toQColor();
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

void ColorDetector::process()
{
	if (m_inBuffer.isValid()) {
		process(m_inBuffer);
	}
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
	if (m_targetColor.toQColor() != targetColor) {
		m_targetColor = targetColor;
		emit targetColorChanged(targetColor);

		process();
	}
}

int ColorDetector::getDistance(const ColorPixel& pixel) const
{
	return
		abs(pixel.r() - m_targetColor.r())
		+ abs(pixel.g() - m_targetColor.g())
		+ abs(pixel.b() - m_targetColor.b());
}
