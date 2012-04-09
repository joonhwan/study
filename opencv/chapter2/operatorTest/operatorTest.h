#pragma once

#include "wimage_t.h"

typedef WImageBufferT<uchar, 3> ColorBuffer;

void test(ColorBuffer::In image, ColorBuffer::Out result);

