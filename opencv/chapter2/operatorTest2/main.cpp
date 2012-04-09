#include "vldhelper.h"
#include "wstopwatch.h"
#include "imagedir.h"
#include "wimageprocessor.h"
#include "wimage_operator.h"
#include <QApplication>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef WImageBufferT<uchar, 3> ColorImage;
typedef WImageBufferT<uchar, 1> MonoImage;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	WStopWatch stopWatch;

	{
		ColorImage image1(IMAGE_DIR "castle.jpg");

		ColorImage result1 = image1;
		ColorImage::Processor::logical_and(ColorImage::Value(255, 0, 0), result1);
		// test(image1, result1);

		cv::namedWindow("image1");
		cv::namedWindow("result1");

		cv::imshow("image1", image1);
		cv::imshow("result1", result1);
	}

	{
		// COPY subpixel test
		MonoImage monoImage1(IMAGE_DIR "castle-black.jpg");//(128*4, 128*4);
		// cv::randu(monoImage1, cv::Scalar(0), cv::Scalar(255));
		cv::namedWindow("monoImage1");
		cv::imshow("monoImage1", monoImage1);

		QSize size = monoImage1.size();
		MonoImage output1(size);
		MonoImage output2(size);

		float delta = 20;
		float fraction = 0.;
		QPointF topLeft(delta+fraction,delta+fraction);
		MonoImage::Processor::copySubpixel(monoImage1.from(topLeft, size),
										   output1.to(QRect(QPoint(0,0), size)));

		cv::Point2f center = monoImage1.centerCv();
		center.x += (delta+fraction);
		center.y += (delta+fraction);
		cv::getRectSubPix(monoImage1, monoImage1.sizeCv(),
						  center, output2);

		cv::namedWindow("output1");
		cv::imshow("output1", output1);
		cv::namedWindow("output2");
		cv::imshow("output2", output2);
	}

	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;//app.exec();
}
