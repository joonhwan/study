#include "imagedir.h"
#include "image/Vld.h"
#include "image/WStopwatch.h"
#include "image/wimageprocessor.h"
#include "algo/AlgoTypes.h"
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

	{
		ColorBuffer image1(IMAGE_DIR "castle.jpg");

		ColorBuffer result1 = image1;
		ColorBuffer::Processor::logical_and(ColorBuffer::PixelValue(255, 0, 0), result1);
		// test(image1, result1);

		cv::namedWindow("image1");
		cv::namedWindow("result1");

		cv::imshow("image1", image1);
		cv::imshow("result1", result1);
	}

	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
