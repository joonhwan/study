void CSplitPatternRemover2::GetDiffImage(IplImage* pcvBright, IplImage* pcvDark)
{
	Ipp32f	dCellWidth = (Ipp32f)m_ptCellDistance.x;
	if ( dCellWidth < 0 || dCellWidth*3 > m_pcvSrc->width )
	{
		CString log;
		log.Format(_T("Not Valid nCellWidth dCellWidth=%.4f ImageWidth=%d "), dCellWidth, m_pcvSrc->width );
		LogTrace(log);
		return;
	}

	// 1. CellWidth 만큼 이동한 좌우로 이동한 영상과의 차영상을 구함
	IplImage* sourceImage		= m_pcvSrc;
	IppiSize	roiSize;
	int		iCenterPos;
	Ipp32f	fCenterPos;

	int		iLeftPos;
	Ipp32f	fLeftPos;

	int		iRightPos;
	Ipp32f	fRightPos;

    // 1. CenterArea
	iCenterPos = (int)ceil(dCellWidth);
	fCenterPos = 0;

	iLeftPos	= 0;	// iCenterPos - ceil(dCellWidth)
	fLeftPos	= (int)ceil(dCellWidth) - dCellWidth;

	iRightPos	= (int)floor(dCellWidth) + iCenterPos;
	fRightPos	= dCellWidth - floor(dCellWidth);	// Center기준으로 소수점 이하는 정수

	roiSize.width	= sourceImage->width - (int)ceil(dCellWidth)*2;
	roiSize.height	= sourceImage->height - 1;

	// ippiCopySubpix_8u_C1R(
	// 	Im::Buf(sourceImage,iLeftPos,0),		sourceImage->widthStep,	// 1. 우측의 영상을 CellWidth만큼 옮겨온다.
	// 	Im::Buf(imageL),					imageL->widthStep, roiSize, fLeftPos, (Ipp32f)0.0);	// 2. 소수점 이하의 CellWidth만큼을 더 보정한다.
	// LogImage(imageL, "copy1");
	// ippiCopySubpix_8u_C1R(
	// 	Im::Buf(sourceImage,iRightPos,0),		sourceImage->widthStep,
	// 	Im::Buf(imageR),					imageR->widthStep, roiSize, fRightPos, (Ipp32f)0.0);
	// LogImage(imageR, "copy2");

	int basePosition = ceil(dCellWidth);
	MonoImage imageLBuffer = MonoProcess::shifted(sourceImage, QSize(basePosition - dCellWidth, 0), roiSize);
	MonoImage imageRBuffer = MonoProcess::shifted(sourceImage, QSize(basePosition + dCellWidth, 0), roiSize);
	MonoImage::InOut imageL = imageLBuffer.to(QPoint(0,0), roiSize);
	MonoImage::InOut imageR = imageRBuffer.to(QPoint(0,0), roiSize);
	MonoImage::In imageC = sourceImage.from(QPoint(basePosition , 0), roiSize);

	// ippiAbsDiff_8u_C1R(	// for Ghost Cancel
	// 	Im::Buf(sourceImage,iLeftPos,0),		sourceImage->widthStep,
	// 	Im::Buf(sourceImage,iRightPos,0),		sourceImage->widthStep,
	// 	Im::Buf(ghost),					ghost->widthStep, roiSize );
	// LogImage(ghost, "ghost");
	MonoImage ghostBuffer(sourceImage.size());
	MonoImage::InOut ghost = ghostBuffer.to(QPoint(0,0), roiSize);
	MonoProcess::absDiff(sourceImage.from(QPoint(iLeftPos,0)),
						 sourceImage.from(QPoint(iRightPos,0)),
						 ghost);

	MonoImage diffBuffer1(sourceImage.size());
	MonoImage diffBuffer2(sourceImage.size());
	MonoImage diffBrightBuffer(sourceImage.size());
	MonoImage diffDarkBuffer(sourceImage.size());
	MonoImage::InOut diff1 = diffBuffer1.to(QPoint(0,0), roiSize);
	MonoImage::InOut diff2 = diffBuffer2.to(QPoint(0,0), roiSize);
	MonoImage::InOut diffBright = diffBrightBuffer.to(QPoint(basePosition,0), roiSize);
	MonoImage::InOut diffDark = diffDarkBuffer.to(QPoint(basePosition,0), roiSize);

	MonoProcess::sub(imageL, imageC, diff1);
	MonoProcess::sub(imageR, imageC, diffBright);
	MonoProcess::minEvery(diff1, diffBright);
	MonoProcess::sub(ghost, diffBright, diffBright);

	MonoProcess::sub(imageC, imageL, diff1);
	MonoProcess::sub(imageC, imageR, diffDark);
	MonoProcess::minEvery(diff1, diffDark);
	MonoProcess::sub(ghost, diffDark, diffDark);

	//	2. LeftArea
	iLeftPos	= 0;	// iCenterPos - ceil(dCellWidth)
	fLeftPos	= 0;	// 기준점

	iCenterPos = (int)floor(dCellWidth);
	fCenterPos = dCellWidth - floor(dCellWidth);

	iRightPos	= (int)floor((dCellWidth*2.0));
	fRightPos	= (dCellWidth*2.0) - floor((dCellWidth*2.0));

	roiSize.width	= (int)ceil(dCellWidth);
	roiSize.height	= sourceImage->height - 1;

	imageC = sourceImage.from(QPoint(iCenterPos , 0), roiSize);
	diffBright = diffBrightBuffer.to(QRect(QPoint(iLeftPos,0), roiSize));
	int unknownCorr = 1;

	imageLBuffer = MonoProcess::shifted(sourceImage, QSize(dCellWidth, 0), roiSize);
	imageL = imageLBuffer.to(QPoint(0,0), roiSize); // 2
	imageRBuffer = MonoProcess::shifted(sourceImage, QSize(dCellWidth + dCellWidth, 0), roiSize);
	imageR = imageRBuffer.to(QPoint(unknownCorr,0), roiSize); // 3
	MonoImage::In sourceL = sourceImage.from(QRect(QPoint(iLeftPos,0), roiSize));
	MonoProcess::absDiff(imageC, imageR, ghost); // for Ghost Cancel |2-3|'
	MonoProcess::absDiff(imageL, imageR, diff2); // | 2-3 |
	MonoProcess::sub(imageL, sourceL, diff1); // | 1-2 |
	MonoProcess::sub(imageR, sourceL, diffBright); // | 1-3 |
	MonoProcess::absDiff(diff1, diff2, diffBright);//   |1-2| - |2-3|
	MonoProcess::minEvery(diff1, diffBright); // | |1-2| - |2-3| | & |1-2|
	MonoProcess::sub(ghost, diffBright, diffBright); // | |1-2| - |2-3| | & |1-2| - |2-3|'
	MonoProcess::subC(7, diffBright);	// Offset for Side Image

	// Create Dark
	diffDark = diffDarkBuffer.to(QRect(QPoint(iLeftPos,0), roiSize));
	MonoProcess::absDiff(imageL, imageR, diff2); // | 2-3 |
	MonoProcess::sub(sourceL, imageL, diff1); // | 1-2 |
	MonoProcess::sub(sourceL, imageR, diffDark); // | 1-3 |
	MonoProcess::absDiff(diff1, diff2, diffDark); //   |1-2| - |2-3|
	MonoProcess::minEvery(diff1, diffDark); // | |1-2| - |2-3| | & |1-2|
	MonoProcess::sub(ghost, diffDark, diffDark); // | |1-2| - |2-3| | & |1-2| - |2-3|'
	MonoProcess::subC(7, diffDark);

	//	3. RightArea
	iRightPos	= (int)ceil(dCellWidth);	// iCenterPos - ceil(dCellWidth)
	fRightPos	= 0;	// 기준점

	iCenterPos	= (int)ceil(dCellWidth) + iRightPos;
	fCenterPos	= ceil(dCellWidth) - dCellWidth;

	iLeftPos	= (int)ceil(dCellWidth*2.0) + iRightPos;
	fLeftPos	= ceil(dCellWidth*2.0) - (dCellWidth*2.0);

	roiSize.width	= (int)floor(dCellWidth);
	roiSize.height	= sourceImage->height - 1;

	ippiCopySubpix_8u_C1R(
			Im::Buf(sourceImage,-iCenterPos,0),		sourceImage->widthStep,	// 1. 우측의 영상을 CellWidth만큼 옮겨온다.
			Im::Buf(imageL),					imageL->widthStep, roiSize, fCenterPos, (Ipp32f)0.0);	// 2. 소수점 이하의 CellWidth만큼을 더 보정한다.
	LogImage(imageL, "copy1-copysubpix-source_minus_center-copy1");

	ippiCopySubpix_8u_C1R(
			Im::Buf(sourceImage,-iLeftPos,0),		sourceImage->widthStep,
			Im::Buf(imageR),					imageR->widthStep, roiSize, fLeftPos, (Ipp32f)0.0);
	LogImage(imageR, "copy2-copysubpix-source_minus_left-copy2");

	ippiAbsDiff_8u_C1R(		// for Ghost Cancel |2-3|'
			Im::Buf(sourceImage,-iCenterPos,0),		sourceImage->widthStep,
			Im::Buf(sourceImage,-iLeftPos-1,0),		sourceImage->widthStep,
			Im::Buf(ghost),					ghost->widthStep, roiSize );
	LogImage(ghost, "ghost-absdiff-source_minus_center-source_minus_left");

	// Bright
	ippiAbsDiff_8u_C1R(		// | 2-3 |
			Im::Buf(imageL),					imageL->widthStep,
			Im::Buf(imageR),					imageR->widthStep,
			Im::Buf(pcvDiff2),					pcvDiff2->widthStep, roiSize );
	LogImage(pcvDiff2, "diff2-absdiff-copy1-copy2");

	ippiSub_8u_C1RSfs(		// | 1-2 |
			Im::Buf(sourceImage,-iRightPos,0),		sourceImage->widthStep,
			Im::Buf(imageL),					imageL->widthStep,
			Im::Buf(pcvDiff1),					pcvDiff1->widthStep, roiSize, 0 );
	LogImage(pcvDiff1, "diff2-sub-source_minus_right-copy1");

	ippiSub_8u_C1RSfs(		// | 1-3 |
			Im::Buf(sourceImage,-iRightPos,0),		sourceImage->widthStep,
			Im::Buf(imageR),					imageR->widthStep,
			Im::Buf(pcvBright,-iRightPos,0),	pcvBright->widthStep, roiSize, 0 );
	LogImage(pcvBright, "bright-sub-source_minus_right-copy2");

	ippiAbsDiff_8u_C1R(		//   |1-2| - |2-3|
			Im::Buf(pcvDiff1),					pcvDiff1->widthStep,
			Im::Buf(pcvDiff2),					pcvDiff2->widthStep,
			Im::Buf(pcvBright,-iRightPos,0),	pcvBright->widthStep, roiSize );
	LogImage(pcvBright, "bright_minus_right-absdiff-diff1-diff2");

	ippiMinEvery_8u_C1IR(	// | |1-2| - |2-3| | & |1-2|
			Im::Buf(pcvDiff1),					pcvDiff1->widthStep,
			Im::Buf(pcvBright,-iRightPos,0),	pcvBright->widthStep, roiSize );
	LogImage(pcvBright, "bright_minus_right-minevery-diff1-bright_minus_right");

	ippiSub_8u_C1RSfs(		// | |1-2| - |2-3| | & |1-2| - |2-3|'
			Im::Buf(ghost),					ghost->widthStep,
			Im::Buf(pcvBright,-iRightPos,0),	pcvBright->widthStep,
			Im::Buf(pcvBright,-iRightPos,0),	pcvBright->widthStep, roiSize, 0 );
	LogImage(pcvBright, "bright-sub-ghost-bright_minus_right");

	ippiSubC_8u_C1IRSfs( 7,
						 Im::Buf(pcvBright,-iRightPos,0),	pcvBright->widthStep, roiSize, 0 );	// Offset for Side Image
	LogImage(pcvBright, "bright-subc-bright_minus_right-roisize");

	// Dark
	ippiAbsDiff_8u_C1R(		// | 2-3 |
			Im::Buf(imageL),					imageL->widthStep,
			Im::Buf(imageR),					imageR->widthStep,
			Im::Buf(pcvDiff2),					pcvDiff2->widthStep, roiSize );
	LogImage(pcvDiff2, "diff2-absdiff-copy1-copy2");

	ippiSub_8u_C1RSfs(		// | 1-2 |
			Im::Buf(imageL),					imageL->widthStep,
			Im::Buf(sourceImage,-iRightPos,0),		sourceImage->widthStep,
			Im::Buf(pcvDiff1),					pcvDiff1->widthStep, roiSize, 0 );
	LogImage(pcvDiff1, "diff1-sub-copy1-source_minus_right");

	ippiSub_8u_C1RSfs(		// | 1-3 |
			Im::Buf(imageR),					imageR->widthStep,
			Im::Buf(sourceImage,-iRightPos,0),		sourceImage->widthStep,
			Im::Buf(pcvDark,-iRightPos,0),		pcvDark->widthStep, roiSize, 0 );
	LogImage(imageR, "copy2-sub-copy2-source_minus_right-dark_minus_right");

	ippiAbsDiff_8u_C1R(		//   |1-2| - |2-3|
			Im::Buf(pcvDiff1),					pcvDiff1->widthStep,
			Im::Buf(pcvDiff2),					pcvDiff2->widthStep,
			Im::Buf(pcvDark,-iRightPos,0),		pcvDark->widthStep, roiSize );
	LogImage(pcvDark, "dark_minus_right-absdiff-diff1-diff2");

	ippiMinEvery_8u_C1IR(	// | |1-2| - |2-3| | & |1-2|
			Im::Buf(pcvDiff1),					pcvDiff1->widthStep,
			Im::Buf(pcvDark,-iRightPos,0),		pcvDark->widthStep, roiSize );
	LogImage(pcvDark, "dark_minus_right-minevery-diff1");

	ippiSub_8u_C1RSfs(		// | |1-2| - |2-3| | & |1-2| - |2-3|'
			Im::Buf(ghost),					ghost->widthStep,
			Im::Buf(pcvDark,-iRightPos,0),		pcvDark->widthStep,
			Im::Buf(pcvDark,-iRightPos,0),		pcvDark->widthStep, roiSize, 0 );
	LogImage(pcvDark, "dark_minus_right-sub-ghost-dark_minus_right");

	ippiSubC_8u_C1IRSfs( 7,
						 Im::Buf(pcvDark,-iRightPos,0),		pcvDark->widthStep, roiSize, 0 );	// Offset for Side Image
	LogImage(pcvDark, "dark_minus_right-subc-dark_minus_right-roisize");
}
