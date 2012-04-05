#include "vldhelper.h"
#include "wstopwatch.h"
#include "imagedir.h"
#include "colorReduce.h"
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

	ColorImage original(IMAGE_DIR "tiger.jpg");
	ColorImage reduced = original;

	WStopWatch stopWatch;
	double time = 0.;
	colorReduce_1(reduced);
	time = stopWatch.elapsedTime();
	std::cout << "colorReduce_1 : " << time << "msec" << std::endl;

	reduced = original;

	stopWatch.start();
	colorReduce_2(reduced);
	time = stopWatch.elapsedTime();
	std::cout << "colorReduce_2 : " << time << "msec" << std::endl;

	reduced = original;

	stopWatch.start();
	colorReduce_3(reduced);
	time = stopWatch.elapsedTime();
	std::cout << "colorReduce_3 : " << time << "msec" << std::endl;

	reduced = original;

	stopWatch.start();
	colorReduce_4(reduced);
	time = stopWatch.elapsedTime();
	std::cout << "colorReduce_4 : " << time << "msec" << std::endl;

	reduced = original;

	stopWatch.start();
	colorReduce_5(reduced);
	time = stopWatch.elapsedTime();
	std::cout << "colorReduce_5 : " << time << "msec" << std::endl;

	reduced = original;

	stopWatch.start();
	colorReduce_6(reduced);
	time = stopWatch.elapsedTime();
	std::cout << "colorReduce_6 : " << time << "msec" << std::endl;

	cv::namedWindow("original");
	cv::namedWindow("reduced");
	cv::imshow("original", original);
	cv::imshow("reduced", reduced);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;//app.exec();
}
