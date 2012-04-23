#pragma once

#pragma warning(push)
#pragma warning(disable : 4996)
#include "image/ippi.hpp"
#pragma warning(pop)

#include <ippcv.h>
#include <QtGlobal>

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
IppStatus ippiAdd_C1R(Ipp32f value,
					  Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiAddC_32f_C1IR(value, pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiAdd_C1R(const Ipp32f* pSrc, int srcStep,
					  Ipp32f value,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiAddC_32f_C1R(pSrc, srcStep, value,
							pDst, dstStep, roiSize);
}

inline
IppStatus ippiAdd_C1R(const Ipp32f* pSrc1, int src1Step,
					  const Ipp32f* pSrc2, int src2Step,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiAdd_32f_C1R(pSrc1, src1Step,
						   pSrc2, src2Step,
						   pDst, dstStep, roiSize);
}

inline
IppStatus ippiAdd_C3R(const Ipp32f value[3],
					  Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiAddC_32f_C3IR(value, pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiAdd_C3R(const Ipp32f* pSrc, int srcStep,
					  const Ipp32f value[3],
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiAddC_32f_C3R(pSrc, srcStep, value,
							pDst, dstStep, roiSize);
}

inline
IppStatus ippiAdd_C3R(const Ipp32f* pSrc1, int src1Step,
					  const Ipp32f* pSrc2, int src2Step,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiAdd_32f_C3R(pSrc1, src1Step,
						   pSrc2, src2Step,
						   pDst, dstStep, roiSize);
}

// generalized ippiConvert function :
//  rule 1) ignore roundMode if not needed
//  rule 2) use scaleFactor = 0 if needed
static inline IppStatus ippiConvert___C1R( const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u16u_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u16u_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u8u_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u8u_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u16s_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u16s_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s8u_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s8u_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u32f_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u32f_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f8u_C1R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}
static inline IppStatus ippiConvert___C3R( const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f8u_C3R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}

static inline IppStatus ippiConvert___C1R( const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s32f_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s32f_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f16s_C1R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}

static inline IppStatus ippiConvert___C3R( const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f16s_C3R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}

static inline IppStatus ippiConvert___C1R( const Ipp8s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8s32f_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp8s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8s32f_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp32f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f8s_C1R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}

static inline IppStatus ippiConvert___C3R( const Ipp32f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32f8s_C3R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}

static inline IppStatus ippiConvert___C1R( const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u32f_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u32f_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f16u_C1R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}
static inline IppStatus ippiConvert___C3R( const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	return ippiConvert_32f16u_C3R( pSrc, srcStep, pDst, dstStep, roiSize, roundMode );
}
static inline IppStatus ippiConvert___C1R( const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u32s_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8u32s_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32s8u_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32s8u_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp8s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8s32s_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp8s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8s32s_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp32s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32s8s_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp32s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32s8s_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C1R( const Ipp16u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u32s_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp16u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u32s_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}


static inline IppStatus ippiConvert___C1R( const Ipp16s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s32s_C1R( pSrc, srcStep, pDst, dstStep, roiSize );
}

static inline IppStatus ippiConvert___C3R( const Ipp16s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s32s_C3R( pSrc, srcStep, pDst, dstStep, roiSize );
}


static inline IppStatus ippiConvert___C1R( const Ipp8s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_8s16s_C1R( pSrc, srcStep, pDst, dstStep, roi );
}

static inline IppStatus ippiConvert___C1R( const Ipp8u* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_8u8s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp16s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_16s8s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1Rs( const Ipp16s* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s16u_C1Rs( pSrc, srcStep, pDst, dstStep, roi );
}


static inline IppStatus ippiConvert___C1Rs( const Ipp16s* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16s32u_C1Rs( pSrc, srcStep, pDst, dstStep, roi );
}

static inline IppStatus ippiConvert___C1R( const Ipp16u* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_16u8s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode,
									 scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp16u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_16u16s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode,
									  scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp16u* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_16u32u_C1R( pSrc, srcStep, pDst, dstStep, roi );
}

static inline IppStatus ippiConvert___C1R( const Ipp32s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32s16s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32s* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32s16u_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1Rs( const Ipp32s* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32s32u_C1Rs( pSrc, srcStep, pDst, dstStep, roi );
}

static inline IppStatus ippiConvert___C1R( const Ipp32s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	return ippiConvert_32s32f_C1R( pSrc, srcStep, pDst, dstStep, roi );
}


static inline IppStatus ippiConvert___C1R( const Ipp32u* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32u8s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32u8u_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32u16s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32u16u_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32u32s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	Q_UNUSED(roundMode);
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32u32f_C1R( pSrc, srcStep, pDst, dstStep, roi );
}

static inline IppStatus ippiConvert___C1R( const Ipp32f* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32f32u_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( const Ipp32f* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32f32s_C1RSfs( pSrc, srcStep, pDst, dstStep, roi, roundMode, scaleFactor );
}

static inline IppStatus ippiConvert___C1R( Ipp32u* pSrcDst, int srcDstStep, IppiSize roi, IppRoundMode roundMode)
{
	int scaleFactor = 0; 		// default scale factor
	return ippiConvert_32f32u_C1IRSfs( pSrcDst, srcDstStep, roi, roundMode, scaleFactor);
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
IppStatus ippiDiv_C1R(Ipp32f value,
					  Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiDivC_32f_C1IR(value, pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiDiv_C1R(const Ipp32f* pSrc, int srcStep,
					  Ipp32f value,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiDivC_32f_C1R(pSrc, srcStep, value,
							pDst, dstStep, roiSize);
}

inline
IppStatus ippiDiv_C1R(const Ipp32f* pSrc1, int src1Step,
					  const Ipp32f* pSrc2, int src2Step,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiDiv_32f_C1R(pSrc1, src1Step,
						   pSrc2, src2Step,
						   pDst, dstStep, roiSize);
}

inline
IppStatus ippiDiv_C3R(const Ipp32f value[3],
					  Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiDivC_32f_C3IR(value, pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiDiv_C3R(const Ipp32f* pSrc, int srcStep,
					  const Ipp32f value[3],
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiDivC_32f_C3R(pSrc, srcStep, value,
							pDst, dstStep, roiSize);
}

inline
IppStatus ippiDiv_C3R(const Ipp32f* pSrc1, int src1Step,
					  const Ipp32f* pSrc2, int src2Step,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiDiv_32f_C3R(pSrc1, src1Step,
						   pSrc2, src2Step,
						   pDst, dstStep, roiSize);
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

inline
IppStatus ippiMul_C1R(Ipp32f value,
					  Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiMulC_32f_C1IR(value, pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiMul_C1R(const Ipp32f* pSrc, int srcStep,
					  Ipp32f value,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiMulC_32f_C1R(pSrc, srcStep, value,
							pDst, dstStep, roiSize);
}

inline
IppStatus ippiMul_C1R(const Ipp32f* pSrc1, int src1Step,
					  const Ipp32f* pSrc2, int src2Step,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiMul_32f_C1R(pSrc1, src1Step,
						   pSrc2, src2Step,
						   pDst, dstStep, roiSize);
}

inline
IppStatus ippiMul_C3R(const Ipp32f value[3],
					  Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiMulC_32f_C3IR(value, pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiMul_C3R(const Ipp32f* pSrc, int srcStep,
					  const Ipp32f value[3],
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiMulC_32f_C3R(pSrc, srcStep, value,
							pDst, dstStep, roiSize);
}

inline
IppStatus ippiMul_C3R(const Ipp32f* pSrc1, int src1Step,
					  const Ipp32f* pSrc2, int src2Step,
					  Ipp32f* pDst, int dstStep, IppiSize roiSize,
					  int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiMul_32f_C3R(pSrc1, src1Step,
						   pSrc2, src2Step,
						   pDst, dstStep, roiSize);
}

inline
IppStatus ippiSqr_C1R( const Ipp32f* pSrc, int srcStep,
					   Ipp32f* pDst, int dstStep, IppiSize roiSize,
					   int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqr_32f_C1R(pSrc, srcStep, pDst, dstStep, roiSize);
}

inline
IppStatus ippiSqr_C3R( const Ipp32f* pSrc, int srcStep,
					   Ipp32f* pDst, int dstStep, IppiSize roiSize,
					   int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqr_32f_C3R(pSrc, srcStep, pDst, dstStep, roiSize);
}

inline
IppStatus ippiSqr_C1R( Ipp32f* pSrcDst, int srcDstStep,
					   IppiSize roiSize,
					   int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqr_32f_C1IR(pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiSqr_C3R( Ipp32f* pSrcDst, int srcDstStep,
					   IppiSize roiSize,
					   int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqr_32f_C3IR(pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiSqrt_C1R( const Ipp32f* pSrc, int srcStep,
					   Ipp32f* pDst, int dstStep, IppiSize roiSize,
					   int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqrt_32f_C1R(pSrc, srcStep, pDst, dstStep, roiSize);
}

inline
IppStatus ippiSqrt_C3R( const Ipp32f* pSrc, int srcStep,
					   Ipp32f* pDst, int dstStep, IppiSize roiSize,
					   int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqrt_32f_C3R(pSrc, srcStep, pDst, dstStep, roiSize);
}

inline
IppStatus ippiSqrt_C1R( Ipp32f* pSrcDst, int srcDstStep,
						IppiSize roiSize,
						int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqrt_32f_C1IR(pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiSqrt_C3R( Ipp32f* pSrcDst, int srcDstStep,
						IppiSize roiSize,
						int scaleFactor)
{
	Q_UNUSED(scaleFactor);
	return ippiSqrt_32f_C3IR(pSrcDst, srcDstStep, roiSize);
}

inline
IppStatus ippiSum_C1R(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
					   Ipp64f* pSum)
{
	IppHintAlgorithm defaultAlgorithm  = ippAlgHintNone;
	return ippiSum_C1R(pSrc, srcStep, roiSize, pSum, defaultAlgorithm);
}

inline
IppStatus ippiSum_C3R(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
					   Ipp64f pSum[3])
{
	IppHintAlgorithm defaultAlgorithm  = ippAlgHintNone;
	return ippiSum_C3R(pSrc, srcStep, roiSize, pSum, defaultAlgorithm);
}

} // namespace IPPIP

#endif	// __cplusplus
