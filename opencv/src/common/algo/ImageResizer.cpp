#include "ImageResizer.h"

ImageResizer::ImageResizer(Algorithm* parent)
	: Algorithm(parent)
{
}

//virtual
ImageResizer::~ImageResizer()
{
}

void ImageResizer::setInput(const MonoBuffer& input)
{
	m_input = input;
}

//virtual
void ImageResizer::doProcess()
{
	if (!m_input.isValid()) {
		processFailed(tr("no input image!"));
		break;
	}

	QSize expectedSize = m_input.size() * m_zoomRatio;
	if (!m_output.isValid()
		|| m_output.size()!=expectedSize)
	{
		m_output = MonoBuffer(expectedSize);
	}

	
}
