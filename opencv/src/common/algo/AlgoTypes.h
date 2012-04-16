#pragma once

#include <image/WImageBufferT.h>
#include <QSharedPointer>

typedef WImageBufferT<uchar, 3> ColorBuffer;
typedef QSharedPointer<ColorBuffer> ColorBufferPtr;
typedef WPixelValue<uchar, 3> ColorPixel;
typedef WImageBufferT<uchar, 1> MonoBuffer;
typedef WPixelValue<uchar, 1> MonoPixel;
