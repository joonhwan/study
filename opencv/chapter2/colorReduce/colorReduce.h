#pragma once

#include "wimage_t.h"

typedef WImageBufferT<uchar, 3> ColorImage;

void colorReduce_1(ColorImage::InOut image, int div = 64);
void colorReduce_2(ColorImage::InOut image, int div = 64);
void colorReduce_3(ColorImage::InOut image, int div = 64);
void colorReduce_4(ColorImage::InOut image, int div = 64);
void colorReduce_5(ColorImage::InOut image, int div = 64);
void colorReduce_6(ColorImage::InOut image, int div = 64);

