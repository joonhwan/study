#include "colorReduce.h"
#include <math.h>

void colorReduce_1(ColorImage::InOut image, int div)
{
	cv::Mat mat = image;
	for (int row = 0; row < mat.rows; ++row) {
		ColorImage::DataType* data = mat.ptr<ColorImage::DataType>(row);
		for (int col = 0; col < mat.cols * mat.channels(); ++col) {
			data[col] = data[col] / div * div + div / 2;
		}
	}
}

void colorReduce_2(ColorImage::InOut image, int div)
{
	cv::Mat mat = image;
	int rowCount = mat.rows;
	int columnCount = mat.cols * mat.channels();
	for (int row = 0; row < rowCount; ++row) {
		ColorImage::DataType* data = mat.ptr<ColorImage::DataType>(row);
		for (int col = 0; col < columnCount; ++col) {
			data[col] = data[col] / div * div + div / 2;
		}
	}
}

void colorReduce_3(ColorImage::InOut image, int div)
{
	cv::Mat mat = image;
	int rowCount = mat.rows;
	int columnCount = mat.cols * mat.channels();
	if (mat.isContinuous()) {
		columnCount = columnCount * rowCount;
		rowCount = 1;
	}
	for (int row = 0; row < rowCount; ++row) {
		ColorImage::DataType* data = mat.ptr<ColorImage::DataType>(row);
		for (int col = 0; col < columnCount; ++col) {
			data[col] = data[col] / div * div + div / 2;
		}
	}
}

void colorReduce_4(ColorImage::InOut image, int div)
{
	cv::Mat mat = image;
	int rowCount = mat.rows;
	int columnCount = mat.cols;
	if (mat.isContinuous()) {
		columnCount = columnCount * rowCount;
		rowCount = 1;
	}
	for (int row = 0; row < rowCount; ++row) {
		ColorImage::DataType* data = mat.ptr<ColorImage::DataType>(row);
		for (int col = 0; col < columnCount; ++col) {
			*data++ = *data / div * div + div / 2;
			*data++ = *data / div * div + div / 2;
			*data++ = *data / div * div + div / 2;
		}
	}
}

void colorReduce_5(ColorImage::InOut image, int div)
{
	cv::Mat mat = image;
	int rowCount = mat.rows;
	int columnCount = mat.cols;
	if (mat.isContinuous()) {
		columnCount = columnCount * rowCount;
		rowCount = 1;
	}
	int n= static_cast<int>(
			log(static_cast<double>(div))/log(2.0));
	// mask used to round the pixel value
	uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0

	for (int row = 0; row < rowCount; ++row) {
		ColorImage::DataType* data = mat.ptr<ColorImage::DataType>(row);
		for (int col = 0; col < columnCount; ++col) {
			*data++ = *data & mask + div / 2;
			*data++ = *data & mask + div / 2;
			*data++ = *data & mask + div / 2;
		}
	}
}

void colorReduce_6(ColorImage::InOut image, int div)
{
	cv::Mat mat = image.matrix();
	int n= static_cast<int>(
			log(static_cast<double>(div))/log(2.0));
	// mask used to round the pixel value
	uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0

	cv::bitwise_and(mat, cv::Scalar::all(mask), mat);
}
