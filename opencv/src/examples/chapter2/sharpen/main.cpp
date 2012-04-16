#include "image/Vld.h"
#include "image/WStopwatch.h"
#include "imagedir.h"
#include "image/WImageProcessor.h"
#include <QApplication>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef WImageBufferT<uchar, 3> ColorBuffer;
typedef WImageBufferT<uchar, 1> MonoBuffer;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	{
		ColorBuffer inBuf(IMAGE_DIR "boldt.jpg");

		ColorBuffer outBuf = inBuf;

		QSize size = inBuf.size();
		cv::Mat& inMat = inBuf.matrix();
		cv::Mat& outMat = outBuf.matrix();

		{
			WStopWatchLogger stopWatch("sharpen");
			for (int i = 0; i < 50; ++i) {
				for (int y = 1; y < size.height()-1; ++y) {
					ColorBuffer::DataType* prev = inMat.ptr<ColorBuffer::DataType>(y-1);
					ColorBuffer::DataType* curr = inMat.ptr<ColorBuffer::DataType>(y  );
					ColorBuffer::DataType* next = inMat.ptr<ColorBuffer::DataType>(y+1);

					ColorBuffer::DataType* output  = outMat.ptr<ColorBuffer::DataType>(y  );
					for (int x = 1; x < size.width()-1; ++x) {
						*output++ = cv::saturate_cast<ColorBuffer::DataType>(5 * *curr - *prev - *(curr-1) - *(curr+1) - *next);
						++next; ++curr; ++prev;
						*output++ = cv::saturate_cast<ColorBuffer::DataType>(5 * *curr - *prev - *(curr-1) - *(curr+1) - *next);
						++next; ++curr; ++prev;
						*output++ = cv::saturate_cast<ColorBuffer::DataType>(5 * *curr - *prev - *(curr-1) - *(curr+1) - *next);
						++next; ++curr; ++prev;
					}
				}
			}
		}

		{
			WStopWatchLogger stopWatch("sharpen-no temp mat");
			for (int i = 0; i < 50; ++i) {
				for (int y = 1; y < size.height()-1; ++y) {
					ColorBuffer::DataType* prev = inBuf->ptr<ColorBuffer::DataType>(y-1);
					ColorBuffer::DataType* curr = inBuf->ptr<ColorBuffer::DataType>(y  );
					ColorBuffer::DataType* next = inBuf->ptr<ColorBuffer::DataType>(y+1);

					ColorBuffer::DataType* output  = outBuf->ptr<ColorBuffer::DataType>(y  );
					for (int x = 1; x < size.width()-1; ++x) {
						*output++ = cv::saturate_cast<ColorBuffer::DataType>(5 * *curr - *prev - *(curr-1) - *(curr+1) - *next);
						++next; ++curr; ++prev;
						*output++ = cv::saturate_cast<ColorBuffer::DataType>(5 * *curr - *prev - *(curr-1) - *(curr+1) - *next);
						++next; ++curr; ++prev;
						*output++ = cv::saturate_cast<ColorBuffer::DataType>(5 * *curr - *prev - *(curr-1) - *(curr+1) - *next);
						++next; ++curr; ++prev;
					}
				}
			}
		}

		{
			WStopWatchLogger stopWatch("sharpen cv::filter");
			// Construct kernel (all entries initialized to 0)
			cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
			// assigns kernel values
			kernel.at<float>(1,1)= 5.0;
			kernel.at<float>(0,1)= -1.0;
			kernel.at<float>(2,1)= -1.0;
			kernel.at<float>(1,0)= -1.0;
			kernel.at<float>(1,2)= -1.0;

			cv::Mat kernel2 = (cv::Mat_<float>(3,3) <<
							    0, -1,  0,
							   -1,  5, -1,
							    0, -1,  0);
			for (int i = 0; i < 50; ++i) {
				// cv::filter2D(inMat, outMat, inMat.depth(), kernel);
				//filter the image
				cv::filter2D(inMat,outMat,inMat.depth(),kernel2);
			}
		}

		{
			WStopWatchLogger stopWatch("sharpen-ipp");
			// Construct kernel (all entries initialized to 0)
			ColorBuffer::IppKernel3x3 kernel(  0, -1,  0,
											  -1,  5, -1,
											   0, -1,  0 );
			QRect roi(QPoint(0,0), inBuf.size());
			roi.adjust(1,1,-1,-1);
			for (int i = 0; i < 50; ++i) {
				ColorBuffer::Processor::filter(inBuf.from(roi), kernel, outBuf.to(roi));
			}
		}

		outBuf.matrix().row(0).setTo(cv::Scalar::all(255));
		outBuf.matrix().row(size.height()-1).setTo(cv::Scalar::all(255));
		outBuf->col(size.width()-1).setTo(cv::Scalar::all(255));
		outBuf->col(0).setTo(cv::Scalar::all(255));

		ColorBuffer::PixelValue p_0_10 = outBuf.pixel(0,10);
		ColorBuffer::PixelValue p_10_0 = outBuf.pixel(10,0);
		Q_ASSERT(p_0_10 == ColorBuffer::PixelValue(255));
		Q_ASSERT(p_10_0 == ColorBuffer::PixelValue(255));
		// {
		// 	ColorBuffer::Processor::filter(inBuf, outBuf, ColorBuffer::Kernel(-1, -1, -1,
		// 																		-1,  5, -1,
		// 																		-1, -1, -1));
		// }

		cv::namedWindow("inBuf");
		cv::namedWindow("outBuf");

		cv::imshow("inBuf", inBuf);
		cv::imshow("outBuf", outBuf);
	}

	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;//app.exec();
}
