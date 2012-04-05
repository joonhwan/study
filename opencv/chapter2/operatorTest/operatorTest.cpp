#include "operatorTest.h"

void test(ColorImage::In image, ColorImage::Out result)
{
	cv::Mat imageMat = image.matrix(result.roiSize());
	cv::Mat resultMat = result.matrix();
	resultMat =  imageMat + 200;
}
