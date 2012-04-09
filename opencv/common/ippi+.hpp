#pragma once

#pragma warning(push)
#pragma warning(disable : 4996)
#include "ippi.hpp"
#pragma warning(pop)

#include <ippcv.h>

#ifdef __cplusplus

namespace IPPIP {

inline
IppStatus ippiAbsDiff_C1R(const Ipp8u* pSrc1, int src1Step,
						  const Ipp8u* pSrc2, int src2Step,
						  Ipp8u* pDst, int dstStep, IppiSize roiSize )
{
	return ippiAbsDiff_8u_C1R(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}

inline
IppStatus ippiAbsDiff_C3R(const Ipp8u* pSrc1, int src1Step,
						  const Ipp8u* pSrc2, int src2Step,
						  Ipp8u* pDst, int dstStep, IppiSize roiSize )
{
	return ippiAbsDiff_8u_C3R(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}

inline
IppStatus ippiCopySubpix_C1R(const Ipp8u* pSrc, int srcStep,
							 Ipp8u* pDst, int dstStep, IppiSize roiSize,
							 Ipp32f dx, Ipp32f dy)
{
	return ippiCopySubpix_8u_C1R(pSrc, srcStep,
								 pDst, dstStep, roiSize,
								 dx, dy);
}

inline
IppStatus ippiCopySubpix_C1R(const Ipp16u* pSrc, int srcStep,
							 Ipp16u* pDst, int dstStep, IppiSize roiSize,
							 Ipp32f dx, Ipp32f dy)
{
	return ippiCopySubpix_16u_C1R(pSrc, srcStep,
								  pDst, dstStep, roiSize,
								  dx, dy);
}

inline
IppStatus ippiCopySubpix_C1R(const Ipp32f* pSrc, int srcStep,
							 Ipp32f* pDst, int dstStep, IppiSize roiSize,
							 Ipp32f dx, Ipp32f dy)
{
	return ippiCopySubpix_32f_C1R(pSrc, srcStep,
								  pDst, dstStep, roiSize,
								  dx, dy);
}

inline
IppStatus ippiCopySubpix_C1R(const Ipp8u* pSrc, int srcStep,
							 Ipp32f* pDst, int dstStep, IppiSize roiSize,
							 Ipp32f dx, Ipp32f dy)
{
	return ippiCopySubpix_8u32f_C1R(pSrc, srcStep,
									pDst, dstStep, roiSize,
									dx, dy);
}

inline
IppStatus ippiMean_C1R(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
					   Ipp64f* pMean)
{
	IppHintAlgorithm defaultAlgorithm  = ippAlgHintNone;
	return ippiMean_C1R(pSrc, srcStep, roiSize, pMean, defaultAlgorithm);
}

inline
IppStatus ippiMean_C3R(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
					   Ipp64f pMean[3])
{
	IppHintAlgorithm defaultAlgorithm  = ippAlgHintNone;
	return ippiMean_C3R(pSrc, srcStep, roiSize, pMean, defaultAlgorithm);
}

} // namespace IPPIP

#endif	// __cplusplus
