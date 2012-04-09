#include "vldhelper.h"
#include "wstopwatch.h"
#include "imagedir.h"
#include "wimageprocessor.h"
#include "wimage_operator.h"
#include <QApplication>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

typedef WImageBufferT<uchar, 3> ColorImage;
typedef WImageBufferT<uchar, 1> MonoImage;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	WStopWatch stopWatch;

	MonoImage bufferA(4,4);
	bufferA.matrix() = (cv::Mat_<uchar>(4,4) << 10,20,30,40,50,60,70,80,110,120,130,140,150,160,170,180);

	MonoImage bufferB(4,4);
	bufferB.matrix() = (cv::Mat_<uchar>(4,4) << 70,10,30,50,100,110,120,130,10,20,30,40,50,60,70,80);

	MonoImage bufferC(4,4);
	// bufferB - bufferA
	MonoImage::Processor::sub(bufferA, bufferB, bufferC);

	MonoImage bufferD = bufferA;
	// bufferA - 50
	MonoImage::Processor::subValueFromImage(50, bufferD);

	cout << "A" << endl << bufferA.matrix() << endl;
	cout << "B" << endl << bufferB.matrix() << endl;
	cout << "C = B-A" << endl << bufferC.matrix() << endl;
	cout << "D = A-50" << endl << bufferD.matrix() << endl;

	MonoImage bufferE = bufferB;
	MonoImage::Processor::minEvery(bufferA, bufferE);
	cout << "MinEvery(A,B)" << endl << bufferE.matrix() << endl;

	MonoImage bufferF = bufferA;
	MonoImage::Processor::logical_and(bufferA, bufferB, bufferF);
	cout << "A & B" << endl << bufferF.matrix() << endl;

	return 0;//app.exec();
}
