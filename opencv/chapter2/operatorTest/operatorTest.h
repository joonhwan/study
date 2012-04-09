#pragma once

#include "wimage_t.h"

typedef WImageBufferT<uchar, 3> ColorImage;

void test(ColorImage::In image, ColorImage::Out result);

