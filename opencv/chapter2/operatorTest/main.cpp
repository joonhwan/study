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

	ColorImage image1(IMAGE_DIR "tiger.jpg");
	ColorImage image2 = image1;
	ColorImage image3 = image1;
	// test(image1, result1);

	ColorImage result1;
	const int count = 50;
	double time1 = 0.;
	for (int i = 0; i < count; ++i) {
		result1.copyFrom(image1);
		stopWatch.start();
		result1 = (image1 + 100)*0.5;
		time1 += stopWatch.elapsedTime();
	}
	std::cout << "test1 : " << time1/count << "msec" << std::endl;

	ColorImage result2;
	double time2 = 0.;
	for (int i = 0; i < count; ++i) {
		result2.copyFrom(image2);
		stopWatch.start();
		cv::add(result2, cv::Scalar::all(100), result2);
		cv::multiply(result2, cv::Scalar::all(0.5), result2);
		time2 += stopWatch.elapsedTime();
	}
	std::cout << "test2 : " << time2/count << "msec" << std::endl;

	ColorImage result3;
	double time3 = 0.;
	for (int i = 0; i < count; ++i) {
		result3.copyFrom(image3);
		stopWatch.start();
		ColorImage::Processor::add(result3, 100);
		time3 += stopWatch.elapsedTime();
	}
	std::cout << "test3 : " << time3/count << "msec" << std::endl;

	cv::namedWindow("image1");
	cv::namedWindow("result1");
	cv::namedWindow("result2");
	cv::namedWindow("result3");
	cv::imshow("image1", image1);
	cv::imshow("result1", result1);
	cv::imshow("result2", result2);
	cv::imshow("result3", result3);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;//app.exec();
}
