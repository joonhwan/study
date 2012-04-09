#include "vldhelper.h"
#include "wstopwatch.h"
#include "imagedir.h"
#include "operatorTest.h"
#include "wimageprocessor.h"
#include "wimage_operator.h"
#include <QApplication>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	WStopWatch stopWatch;

	ColorBuffer imagebuffer1(IMAGE_DIR "tiger.jpg");
	ColorBuffer imagebuffer2 = imagebuffer1;
	ColorBuffer imagebuffer3 = imagebuffer1;
	// test(imagebuffer1, result1);

	ColorBuffer result1;
	const int count = 50;
	double time1 = 0.;
	for (int i = 0; i < count; ++i) {
		result1.copyFrom(imagebuffer1);
		stopWatch.start();
		result1 = (imagebuffer1 + 100)*0.5;
		time1 += stopWatch.elapsedTime();
	}
	std::cout << "test1 : " << time1/count << "msec" << std::endl;

	ColorBuffer result2;
	double time2 = 0.;
	for (int i = 0; i < count; ++i) {
		result2.copyFrom(imagebuffer2);
		stopWatch.start();
		cv::add(result2, cv::Scalar::all(100), result2);
		cv::multiply(result2, cv::Scalar::all(0.5), result2);
		time2 += stopWatch.elapsedTime();
	}
	std::cout << "test2 : " << time2/count << "msec" << std::endl;

	ColorBuffer result3;
	double time3 = 0.;
	for (int i = 0; i < count; ++i) {
		result3.copyFrom(imagebuffer3);
		stopWatch.start();
		ColorBuffer::Processor::add(ColorBuffer::Processor::PixelValue(100,100,100), result3);
		ColorBuffer::Processor::div(ColorBuffer::Processor::PixelValue(2,2,2), result3);
		time3 += stopWatch.elapsedTime();
	}
	std::cout << "test3 : " << time3/count << "msec" << std::endl;

	cv::namedWindow("imagebuffer1");
	cv::namedWindow("result1");
	cv::namedWindow("result2");
	cv::namedWindow("result3");
	cv::imshow("imagebuffer1", imagebuffer1);
	cv::imshow("result1", result1);
	cv::imshow("result2", result2);
	cv::imshow("result3", result3);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;//app.exec();
}
