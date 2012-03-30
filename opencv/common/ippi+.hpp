#pragma once

#pragma warning(push)
#pragma warning(disable : 4996)
#include "ippi.hpp"
#pragma warning(pop)

#include <ippcv.h>

#ifdef __cplusplus

namespace IPPIP {

IppStatus ippiAbsDiff_C1R(const Ipp8u* pSrc1, int src1Step,
						  const Ipp8u* pSrc2, int src2Step,
						  Ipp8u* pDst, int dstStep, IppiSize roiSize )
{
	return ippiAbsDiff_8u_C1R(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}

IppStatus ippiAbsDiff_C3R(const Ipp8u* pSrc1, int src1Step,
						  const Ipp8u* pSrc2, int src2Step,
						  Ipp8u* pDst, int dstStep, IppiSize roiSize )
{
	return ippiAbsDiff_8u_C3R(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}

};


#endif	// __cplusplus
