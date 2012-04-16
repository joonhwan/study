#pragma once

#include "image/WImageT.h"

typedef WImageBufferT<uchar, 3> ColorBuffer;

void test(ColorBuffer::In image, ColorBuffer::Out result);

