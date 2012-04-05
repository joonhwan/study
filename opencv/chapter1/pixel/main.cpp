#include "wimage.h"
#include "wimage_t.h"
#include "wimageipp.h"
#include "vldhelper.h"
#include "imagedir.h"
#include <QApplication>
#include <iostream>
#include <ipp.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef WImageT<uchar,3> MyImageType;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	MyImageType image(IMAGE_DIR "castle.jpg");

	WImageT<float,3> floatImage = image;
	MyImageType timage = image; // keep original but not yet copy!
	if (timage.isValid()) {
		MyImageType::Processor::salt(timage, 2000);
	}
	MyImageType diffImage = image;
	// WImageT<uchar,3> colorImage = image;

	MyImageType::Processor::absDiff(image.of(QPoint(50,50)), timage.of(QPoint(50,50)), diffImage.of(QRect(50,50,100,100)));
	MyImageType::Processor::absDiff(image, timage, diffImage);
	MyImageType::Processor::add(diffImage, 50, 1);
	cv::absdiff(image(QPoint(50,50)).matrix(100,100),
				timage(QPoint(50,50)).matrix(100,100),
				diffImage(QRect(50,50,100,100)).matrix());
	// Wf::absDiff(image, timage, output);

	cv::namedWindow("image");
	cv::namedWindow("floatimage");
	cv::namedWindow("timage");
	cv::namedWindow("diffImage");
	cv::imshow("image", image);
	cv::imshow("floatimage", image);
	cv::imshow("timage", timage);
	cv::imshow("diffImage", diffImage);
	cv::waitKey(0);
	cv::destroyAllWindows();

	// IplImage* ii = cvLoadImage(IMAGE_DIR "castle.jpg");
	// cv::flip(ii, ii, 1);

	cv::Mat mat(100,100,CV_8U);
	cv::Mat_<uchar> mp = mat;
	// Ipp32f* p =0;
	// // ippiAdd_32f_C1R(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize);
	// IppiSize roiSize = {
	// 	100, 200
	// };
	// ippiAdd_32f_C1R(p, 0, p, 0, p, 0, roiSize);
	// getchar();
	return 0;//app.exec();
}
