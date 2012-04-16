#include "image/Vld.h"
#include "image/WStopwatch.h"
#include "imagedir.h"
#include "image/WImageProcessor.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <QSize>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

typedef WImageBufferT<uchar, 3> ColorBuffer;
typedef WImageBufferT<uchar, 1> MonoBuffer;
typedef WImageProcess<uchar, 1> MonoProc;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("cvmattest");

	// pitch = 8 pixel
	MonoBuffer handWritten(1,32);
	handWritten.matrix() = (cv::Mat_<uchar>(1,32) << 20,80,127,180,127,127,80,20,20,80,127,127,127,127,80,20,20,80,127,70,127,127,80,20,20,80,127,127,127,127,80,20);

	// pitch changed . 9.6 pixel original image
	double pitch = 9.6;
	MonoBuffer sourceImage(1,128);
	// cv::resize(handWritten, original, cvSize(48,1));
	cv::resize(handWritten, sourceImage, cvSize(0,0), 1.2, 1.0);
	QSize sourceImageSize = sourceImage.size();

	int centerPos = ceil(pitch);
	double leftPos = centerPos - pitch;
	double rightPos= centerPos + pitch;
	QSize roiSize(sourceImageSize.width() - ceil(pitch*2),
				  sourceImageSize.height());

	MonoBuffer bufferL(roiSize);
	MonoBuffer bufferR(roiSize);
	MonoBuffer ghostReal(roiSize);
	MonoBuffer ghost(roiSize);
	MonoBuffer brightDiffBuffer(sourceImageSize);

	MonoBuffer::In bufferC = sourceImage.from(centerPos,0, roiSize);
	MonoBuffer::Out brightDiff = brightDiffBuffer.to(centerPos,0,roiSize);

	MonoProc::copySubpixel(sourceImage.fromF(leftPos , 0, roiSize), bufferL);
	MonoProc::copySubpixel(sourceImage.fromF(rightPos, 0, roiSize), bufferR);
	MonoProc::absDiff(bufferL, bufferR, ghostReal);
	MonoProc::absDiff(sourceImage.from((int)leftPos,0),
					  sourceImage.from((int)rightPos,0),
					  ghost);

	cout << "handWritten" << endl << handWritten.matrix() << endl;
	cout << "sourceImage" << endl << sourceImage.matrix() << endl;
	cout << "bufferL" << endl << bufferL.matrix() << endl;
	cout << "bufferC" << endl << bufferC.matrix() << endl;
	cout << "bufferR" << endl << bufferR.matrix() << endl;
	cout << "ghostReal" << endl << ghostReal.matrix() << endl;
	cout << "ghost" << endl << ghost.matrix() << endl;

	MonoBuffer temp(roiSize);
	MonoProc::sub(bufferL, bufferC, temp);
	MonoProc::sub(bufferR, bufferC, brightDiff);
	MonoProc::minEvery(temp, brightDiff);

	MonoBuffer bdWithGhost(roiSize);
	MonoBuffer bdWithGhostReal(roiSize);

	MonoProc::sub(ghost, brightDiff, bdWithGhost);
	MonoProc::sub(ghost, brightDiff, bdWithGhostReal);

	cout << "bright diff before removing ghost" << endl << brightDiff.matrix() << endl;
	cout << "bdWithGhost" << endl << bdWithGhost.matrix() << endl;
	cout << "bdWithGhostReal" << endl << bdWithGhostReal.matrix() << endl;

	return 0;//app.exec();
}
