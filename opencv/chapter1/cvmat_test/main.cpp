#include "wimage.h"
#include "vldhelper.h"
#include "imagedir.h"
#include <QApplication>
#include <vld.h>
#include <iostream>
#include <ipp.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	cv::namedWindow("image");
	cv::namedWindow("image2");
	cv::namedWindow("image3");
	cv::namedWindow("image4");
	cv::namedWindow("image5");

	WImage image;
	image = cv::imread(IMAGE_DIR "castle.jpg");
	WImage image2 = image;
	cv::randShuffle(image2);

	WImage image3(240, 320, CV_8U, cv::Scalar(255));
	// WimageT<uchar, 1>

	cv::Ptr<IplImage> iplImage = cvLoadImage(IMAGE_DIR "castle.jpg");
	WImage image4(iplImage, false);
	WImage image5;
	cv::flip(image4, image5, 1);

	cv::imshow("image", image);
	cv::imshow("image2", image2);
	cv::imshow("image3", image3);
	cv::imshow("image4", image4);
	cv::imshow("image5", image5);
	cv::waitKey(60000);
	cv::destroyAllWindows();
	// getchar();
	return 0;//app.exec();
}
