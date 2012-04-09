#include "wimagebuffer.h"
#include "wimage_t.h"
#include "wimageprocessor.h"
#include "vldhelper.h"
#include "imagedir.h"
#include <QApplication>
#include <iostream>
#include <ipp.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef WImageBufferT<uchar,3> ImageBuffer;

void salt(ImageBuffer::Image image, int n)
{
	cv::Mat mat = image.matrix();
	QRect roi = image.roi();
	for (int i = 0; i < n; ++i) {
		int x = (qrand() % roi.width()) / 2;
		int y = qrand() % roi.height();
		// color
		// NOTE : (y, x) 의 순서에 주의
		mat.at< cv::Vec<ImageBuffer::DataType,3> >(y, x)[0] = 255;
		mat.at< cv::Vec<ImageBuffer::DataType,3> >(y, x)[1] = 255;
		mat.at< cv::Vec<ImageBuffer::DataType,3> >(y, x)[2] = 255;
	}
}

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	cv::namedWindow("image");
	cv::namedWindow("floatimage");
	cv::namedWindow("timage");
	cv::namedWindow("diffImage");

	ImageBuffer image(IMAGE_DIR "castle.jpg");
	cv::imshow("image", image);
	cv::waitKey(0);

	WImageBufferT<float,3> floatImage = image;
	ImageBuffer timage = image; // keep original but not yet copy!
	if (timage.isValid()) {
		salt(timage, 2000);
	}
	ImageBuffer diffImage = image;
	// WImageBufferT<uchar,3> colorImage = image;

	ImageBuffer::Processor::absDiff(image.from(QPoint(50,50)), timage.from(QPoint(50,50)), diffImage.to(QRect(50,50,100,100)));
	// ImageBuffer::Processor::absDiff(image, timage, diffImage);
	// ImageBuffer::Processor::add(diffImage, 50, 1);
	// QRect roi(50,50,100,100);

	// cv::absdiff(image.from(roi), timage.from(roi), diffImage.to(roi));
	// Wf::absDiff(image, timage, output);

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
