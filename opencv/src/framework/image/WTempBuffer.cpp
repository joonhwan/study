#include "WTempBuffer.h"


#define DEFINE_ALLOCATE(TYPE,PRE,CHAN)									\
	template<>															\
	void IppBuffer<uchar, 1>::allocateImpl()							\
	{																	\
		m_buffer = ippiMalloc_##PRE##_C##CHAN(m_size.width(), m_size.height());	\
	}

DEFINE_ALLOCATE(uchar,8u,1)
DEFINE_ALLOCATE(ushort,16u,1)
DEFINE_ALLOCATE(short,16s,1)
DEFINE_ALLOCATE(int,32s,1)
DEFINE_ALLOCATE(float,32f,1)

DEFINE_ALLOCATE(uchar,8u,3)
DEFINE_ALLOCATE(ushort,16u,3)
DEFINE_ALLOCATE(short,16s,3)
DEFINE_ALLOCATE(int,32s,3)
DEFINE_ALLOCATE(float,32f,3)
