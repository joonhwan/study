#include "vldhelper.h"
#include "wstopwatch.h"
#include "imagedir.h"
#include "wimageipp.h"
#include "wimage_operator.h"
#include <QApplication>
#include <iostream>
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

typedef WImageT<uchar, 3> ColorImage;
typedef WImageT<uchar, 1> MonoImage;
typedef MonoImage::Processor MonoProc;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	// pitch = 8 pixel
	MonoImage sample(1,32);
	sample.matrix() = (cv::Mat_<uchar>(1,32) << 20,80,127,180,127,127,80,20,20,80,127,127,127,127,80,20,20,80,127,70,127,127,80,20,20,80,127,127,127,127,80,20);

	// pitch changed . 9.6 pixel original image
	double pitch = 9.6;
	MonoImage sourceImage(1,128);
	// cv::resize(sample, original, cvSize(48,1));
	cv::resize(sample, sourceImage, cvSize(0,0), 1.2, 1.0);
	QSize sourceImageSize = sourceImage.size();

	QSize roiSize(sourceImageSize.width - ceil(pitch*2),
				  sourceImageSize.height);

	cout << "sample" << endl << sample.matrix() << endl;
	cout << "original" << endl << original.matrix() << endl;

	return 0;//app.exec();
}
