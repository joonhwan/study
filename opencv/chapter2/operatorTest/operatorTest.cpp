#include "operatorTest.h"

void test(ColorBuffer::In image, ColorBuffer::Out result)
{
	cv::Mat imageMat = image.matrix(result.roiSize());
	cv::Mat resultMat = result.matrix();
	resultMat =  imageMat + 200;
}
