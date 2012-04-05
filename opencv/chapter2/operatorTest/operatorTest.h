#pragma once

#include "wimage_t.h"

typedef WImageT<uchar, 3> ColorImage;

void test(ColorImage::In image, ColorImage::Out result);

