#include "WHistogram.h"
#include "WImageBufferT.h"
#include "WImageT.h"
#include "ippi_ext.hpp"
#include <QtGlobal>

void testIppResize3()
{
	WHistogramParameter parameter
		= WHistogramParameter()
		.allChannel()
		.range(0,255);

	WHistogramResult<int, 3> histogram;

	WImageBufferT<uchar, 3> inBuffer(640,480);
	WConstImageT<uchar, 3> inImage = inBuffer;
	IppHistogramParameter<3> ippParam = parameter;
	histogram.resize(ippParam.levelsCount());

	IPPIP::ippiHistogramRange_C3R(inImage, //(const uchar*)inImage,
								  inImage.step(),
								  inImage.ippRoiSize(),
								  histogram.getDataRef(),
								  ippParam.levels(),
								  ippParam.levelsCount());
}

void testIppResize1()
{
	WHistogramParameter parameter
		= WHistogramParameter()
		.allChannel()
		.range(0,255);

	WHistogramResult<int, 1> histogram;
	histogram.resize(parameter.levelsCount());

	WImageBufferT<uchar, 1> inBuffer(640,480);
	WConstImageT<uchar, 1> inImage = inBuffer;
	IppHistogramParameter<1> ippParam = parameter;

	IPPIP::ippiHistogramRange_C1R(inImage, //(const uchar*)inImage,
								  inImage.step(),
								  inImage.ippRoiSize(),
								  histogram.getDataRef(),
								  ippParam.levels(),
								  ippParam.levelsCount());
}
