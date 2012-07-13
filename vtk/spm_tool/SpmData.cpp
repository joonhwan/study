#include "SpmData.h"
#include <QFileInfo>
#include <QMessageBox>
#include <float.h>
#include <limits.h>

CSpmData::CSpmData()
{
	wdVersion = 0;
	strTitle.clear();
	strDate.clear();
	strObj.clear();
	strInsp.clear();
	nMethod = 0;
	nProcessing = 0;
	nSXNum = 0;
	nSYNum = 0;
	nPixelBinning = 0;
	fXresol = 0;
	fYresol = 0;
	fXcen = 0;
	fYcen = 0;
	fHMax = 0;
	fHMin = 0;
}

CSpmData::~CSpmData()
{
	clearData();
}

void CSpmData::prepareData()
{
	int total = dataCount();
	surfaceValidity.reset(new quint8[total]);
	memset(surfaceValidity.data(), 0,  sizeof (quint8)*total);
	surfaceHeight.reset(new float[total]);
	memset(surfaceHeight.data(), 0, sizeof (float)*total);
}

void CSpmData::clearData()
{
	wdVersion = 0;
	strTitle = "";
	strDate = "";
	strObj = "";
	strInsp = "";
	nMethod = 0;
	nProcessing = 0;
	nSXNum = 2;
	nSYNum = 2;
	nPixelBinning = 0;
	fXresol = 0;
	fYresol = 0;
	fXcen = 0;
	fYcen = 0;
	fHMax = 0;
	fHMin = 0;
	surfaceHeight.reset();
	surfaceValidity.reset();
}

QByteArray CSpmData::byteData(const QLatin1String& _strType,
							  float fThreshold)
{
	int nTotalPixel = nSXNum * nSYNum;
	// quint8 *pBtData = (quint8 *)  new quint8[nTotalPixel];
	// memset(pBtData, 0, sizeof(quint8)*nTotalPixel);
	QByteArray pBtData(nTotalPixel, 0);

	QString strType = _strType;
	if( strType.toUpper() == "UP" )
	{
		for(int nIdx = 0; nIdx < nTotalPixel; nIdx++)
		{
			if(surfaceValidity[nIdx] != NOISE_PXL)
			{
				if (surfaceHeight[nIdx] > fThreshold)	// Top Area
				{
					pBtData[nIdx] = 1;
				}
			}
		}
	}
	else // Down
	{
		for(int nIdx = 0; nIdx < nTotalPixel; nIdx++)
		{
			if(surfaceValidity[nIdx] != NOISE_PXL)
			{
				if (surfaceHeight[nIdx] < fThreshold)	// Base Area
				{
					pBtData[nIdx] = 1;
				}
			}
		}
	}

	return pBtData;
}

QList<float> CSpmData::minMax(void)
{
	float min = FLT_MAX;
	float max = FLT_MIN;
	for (int i = 0; i < dataCount(); ++i) {
		float v = surfaceHeight[i];
		if (v > max) {
			max = v;
		}
		if (v < min) {
			min = v;
		}
	}
	return QList<float>() << min << max;
}

float CSpmData::heightAt(int x, int y)
{
	float v = 0.f;
	if (x < countX() && y < countY()) {
		v = surfaceHeight[x + y * countX()];
	}
	return v;
}

bool CSpmData::loadFromFile(QString filePathName)
{
	bool done = false;

	do
	{
		if( !QFileInfo(filePathName).exists() )
		{
			QMessageBox::warning(0, QObject::tr("SPM File Processor"),
								 QObject::tr("File does not exist !!!"));
			break;
		}

		QFile f(filePathName);
		if (!f.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(0, QObject::tr("SPM File Processor"),
								 QObject::tr("File Open Error."));
			break;
		}
		clearData();

		f.read((char*)&wdVersion, sizeof(qint16));

		if (!readStr(f, strTitle)
			|| !readStr(f, strDate)
			|| !readStr(f, strObj)
			|| !readStr(f, strInsp)) {
			break;
		}

		f.read((char*)&nMethod, sizeof(quint8));
		f.read((char*)&nProcessing, sizeof(quint8));

		f.read((char*)&nSXNum, sizeof(int));
		f.read((char*)&nSYNum, sizeof(int));

		f.read((char*)&nPixelBinning, sizeof(int));

		f.read((char*)&fXresol, sizeof(float));
		f.read((char*)&fYresol, sizeof(float));

		f.read((char*)&fXcen, sizeof(float));
		f.read((char*)&fYcen, sizeof(float));

		f.read((char*)&fHMax, sizeof(float));
		f.read((char*)&fHMin, sizeof(float));

		prepareData();

		// read height value(um?)
		qint64 bytesToRead = sizeof(float) * dataCount();
		if (bytesToRead != f.read((char*)surfaceHeight.data(), bytesToRead)) {
			break;
		}

		//read pixel validity
		bytesToRead = sizeof(quint8) * dataCount();
		if (bytesToRead != f.read((char*)surfaceValidity.data(), bytesToRead)) {
			break;
		}

		done = true;
	} while (0);

	return done;
}

bool CSpmData::readStr(QFile &f, QString& str)
{
	bool done = false;

	do
	{
		char count = 0;
		if (sizeof (char) != f.read((char*)&count, sizeof(char))) {
			break;
		}

		QByteArray ansiString = f.read(count);
		if (ansiString.length() != count) {
			break;
		}

		str = ansiString;

		done = true;
	} while (0);

	return done;
}

void CSpmData::saveToFile(const QString& filePathName)
{
	QFile f(filePathName);
	if (!f.open(QIODevice::WriteOnly))
	{
				QMessageBox::warning(0,
									 QObject::tr("SPM File Processor"),
									 QObject::tr("File Open Error"));
		return;
	}

	f.write((const char*)&wdVersion, sizeof(qint16));

	writeStr(f, strTitle);
	writeStr(f, strDate);
	writeStr(f, strObj);
	writeStr(f, strInsp) ;

	f.write((const char*)&nMethod, sizeof(quint8));
	f.write((const char*)&nProcessing, sizeof(quint8));

	f.write((const char*)&nSXNum, sizeof(int));
	f.write((const char*)&nSYNum, sizeof(int));

	f.write((const char*)&nPixelBinning, sizeof(int));

	f.write((const char*)&fXresol, sizeof(float));
	f.write((const char*)&fYresol, sizeof(float));

	f.write((const char*)&fXcen, sizeof(float));
	f.write((const char*)&fYcen, sizeof(float));

	f.write((const char*)&fHMax, sizeof(float));
	f.write((const char*)&fHMin, sizeof(float));

	// height 값은 항상 um단위로 처리한다
	// for(int idx = 0; idx < nSYNum; idx++)
	// {
	// 	f.write((const char*)surfaceHeight + idx * nSXNum, sizeof(float) * nSXNum);
	// }
	f.write((const char*)surfaceHeight.data(), sizeof (float)*nSXNum*nSYNum);


	//write pixel validity
	// for(int idx = 0; idx < nSYNum; idx++)
	// {
	// 	f.write((const char*)surfaceValidity + idx * nSXNum, sizeof(quint8) * nSXNum);
	// }
	f.write((const char*)surfaceValidity.data(), sizeof (quint8)*nSXNum*nSYNum);
}

bool CSpmData::writeStr(QFile &f, const QString& str)
{
	bool done = false;

	do
	{
		QByteArray ansiStr = str.toAscii();

		char count = (char)ansiStr.length();
		if (sizeof (char) != f.write((const char*)&count, sizeof(char))) {
			break;
		}

		if (count != f.write(ansiStr.constData(), count)) {
			break;
		}

		done = true;
	} while (0);

	return done;
}

void CSpmData::copy(CSpmData &other)
{
	clearData();

	strTitle = other.strTitle;
	strDate = other.strDate;
	strObj = other.strObj;
	strInsp = other.strInsp;

	nMethod = other.nMethod;
	nProcessing = other.nProcessing;
	nSXNum = other.nSXNum;
	nSYNum = other.nSYNum;
	nPixelBinning = other.nPixelBinning;
	fXresol = other.fXresol;
	fYresol = other.fYresol;

	fXcen = other.fXcen;
	fYcen = other.fYcen;
	fHMax = other.fHMax;
	fHMin = other.fHMin;

	prepareData();

	// // height 값은 항상 um단위로 처리한다
	// for(int idx = 0; idx < nSYNum; idx++)
	// {
	// 	memcpy(surfaceHeight + idx * nSXNum, other.surfaceHeight + idx * nSXNum, sizeof(float) * nSXNum);
	// }
	memcpy(surfaceHeight.data(),
		   other.surfaceHeight.data(),
		   sizeof(float) * dataCount());

	// for(int idx = 0; idx < nSYNum; idx++)
	// {
	// 	memcpy(surfaceValidity + idx * nSXNum, other.surfaceValidity + idx * nSXNum, sizeof(quint8) * nSXNum);
	// }
	memcpy(surfaceValidity.data(),
		   other.surfaceValidity.data(),
		   sizeof(quint8) * dataCount());
}

void CSpmData::copyRoi(CSpmData &other, int nX1, int nY1, int nX2, int nY2)
{
	// Roi 설정 부분.
	clearData();
	wdVersion = other.wdVersion;
	strTitle = other.strTitle;
	strDate = other.strDate;
	strObj = other.strObj;
	strInsp = other.strInsp;

	nMethod = other.nMethod;
	nProcessing = other.nProcessing;
	nSXNum = (nX2 - nX1) + 1; //X2-X1 nSXNum = other.nSXNum;
	nSYNum = (nY2 - nY1) + 1; //Y2-Y1 nSYNum = other.nSYNum;
	nPixelBinning = other.nPixelBinning;
	fXresol = other.fXresol;
	fYresol = other.fYresol;

	fXcen = other.fXcen;
	fYcen = other.fYcen;
	fHMax = other.fHMax;
	fHMin = other.fHMin;

	prepareData();

	// height 값은 항상 um단위로 처리한다
	int nIdxSrc, nIdxTar;

	for(nIdxSrc = nY1, nIdxTar = 0; nIdxSrc <= nY2; nIdxSrc++, nIdxTar++)
	{
		memcpy(&surfaceHeight[nIdxTar * nSXNum], &other.surfaceHeight[nIdxSrc * other.nSXNum + nX1], sizeof(float) * nSXNum);
	}

	for( nIdxSrc = nY1, nIdxTar = 0; nIdxSrc <= nY2; nIdxSrc++, nIdxTar++)
	{
		memcpy(&surfaceValidity[nIdxTar * nSXNum], &other.surfaceValidity[nIdxSrc * other.nSXNum + nX1], sizeof(quint8) * nSXNum);
	}
}

void CSpmData::prepareStitching(const QString& strLeftTopFile,
								const QString& strRightBottomFile)
{
	CSpmData SpmStart, SpmEnd;

	SpmStart.loadFromFile(strLeftTopFile);
	SpmEnd.loadFromFile(strRightBottomFile);

	SpmStart.fYcen *= -1.f; // For Stitching
	SpmEnd.fYcen *= -1.f; // For Stitching

	float fTotWidth = (SpmEnd.fXcen - SpmStart.fXcen) + SpmEnd.nSXNum * SpmEnd.fXresol;
	float fTotHeight = (SpmEnd.fYcen - SpmStart.fYcen) + SpmEnd.nSYNum * SpmEnd.fYresol;

	int nTotWidth = (int)(fTotWidth / SpmEnd.fXresol) + 1;
	int nTotHeight = (int)(fTotHeight / SpmEnd.fYresol) + 1;

	//---------------------

	clearData();

	wdVersion = SpmStart.wdVersion;

	strTitle = SpmStart.strTitle;
	strDate = SpmStart.strDate;
	strObj = SpmStart.strObj;
	strInsp = SpmStart.strInsp;

	nMethod = SpmStart.nMethod;
	nProcessing = SpmStart.nProcessing;
	nSXNum = nTotWidth;
	nSYNum = nTotHeight;
	nPixelBinning = SpmStart.nPixelBinning;
	fXresol = SpmStart.fXresol;
	fYresol = SpmStart.fYresol;

	fXcen = (SpmStart.fXcen - (0.5f * SpmStart.nSXNum * SpmStart.fXresol)) +
		    (nTotWidth * 0.5f * fXresol);
	fYcen = (SpmStart.fYcen - (0.5f * SpmStart.nSYNum * SpmStart.fYresol)) +
		    (nTotHeight * 0.5f * fYresol);
	fHMax = SpmStart.fHMax;
	fHMin = SpmStart.fHMin;

	//-------------------
	prepareData();

	memset(surfaceValidity.data(), 0xff, sizeof(quint8)*nSXNum*nSYNum);
}

void CSpmData::stitch(int nRow, int nCol, const QString& strSpmFile)
{
	CSpmData SpmIn;
	SpmIn.loadFromFile(strSpmFile);
	SpmIn.fYcen *= -1.f; // For Stitching

	// QString str = QString::fromLatin1("%1, %2")
	// 			  .arg(nRow)
	// 			  .arg(nCol);

	// Top 1/4 Rect
	float fOverX1, fOverY1, fOverX2, fOverY2;

	if( nCol == 0 )
	{
		// Top 1/4 Rect
		fOverX1 = SpmIn.fXcen - (SpmIn.nSXNum / 2) * SpmIn.fXresol;
		fOverY1 = SpmIn.fYcen - (SpmIn.nSYNum / 2) * SpmIn.fYresol;
		fOverX2 = SpmIn.fXcen + (SpmIn.nSXNum / 2) * SpmIn.fXresol;
		fOverY2 = SpmIn.fYcen - (SpmIn.nSYNum / 4) * SpmIn.fYresol;
	}
	else
	{
		// Left 1/4 Rect
		fOverX1 = SpmIn.fXcen - (SpmIn.nSXNum / 2) * SpmIn.fXresol;
		fOverY1 = SpmIn.fYcen - (SpmIn.nSYNum / 2) * SpmIn.fYresol;
		fOverX2 = SpmIn.fXcen - (SpmIn.nSXNum / 4) * SpmIn.fXresol;
		fOverY2 = SpmIn.fYcen + (SpmIn.nSYNum / 2) * SpmIn.fYresol;
	}

	float fGap = 0.f;

	if( (nCol != 0) || (nRow != 0) )
	{
		int nInX1, nInY1, nInX2, nInY2;
		int nAccX1, nAccY1, nAccX2, nAccY2;

		nInX1 = (int)( (SpmIn.nSXNum / 2) + (fOverX1 - SpmIn.fXcen) / SpmIn.fXresol );
		nInY1 = (int)( (SpmIn.nSYNum / 2) + (fOverY1 - SpmIn.fYcen) / SpmIn.fYresol );
		nInX2 = (int)( (SpmIn.nSXNum / 2) + (fOverX2 - SpmIn.fXcen) / SpmIn.fXresol );
		nInY2 = (int)( (SpmIn.nSYNum / 2) + (fOverY2 - SpmIn.fYcen) / SpmIn.fYresol );

		nAccX1 = (int)( (nSXNum / 2) + (fOverX1 - fXcen) / fXresol );
		nAccY1 = (int)( (nSYNum / 2) + (fOverY1 - fYcen) / fYresol );
		nAccX2 = (int)( (nSXNum / 2) + (fOverX2 - fXcen) / fXresol );
		nAccY2 = (int)( (nSYNum / 2) + (fOverY2 - fYcen) / fYresol );

		int nX, nY, nAddr, nCount = 0;

		float fSum = 0.f;

		for(nY = nInY1; nY < nInY2; nY++)
			for(nX = nInX1; nX < nInX2; nX++)
			{
				nAddr = nX + nY * SpmIn.nSXNum;

				if(SpmIn.surfaceValidity[nAddr] != NOISE_PXL)
				{
					fSum += SpmIn.surfaceHeight[nAddr];
					nCount++;
				}
			}

		float fInAvg = 0;
		if(nCount != 0)
		{
			fInAvg = fSum / nCount;
		}

		//------

		fSum = 0.f;
		nCount = 0;

		for(nY = nAccY1; nY < nAccY2; nY++)
			for(nX = nAccX1; nX < nAccX2; nX++)
			{
				nAddr = nX + nY * nSXNum;

				if( (surfaceValidity[nAddr] != NOISE_PXL) &&
					(surfaceValidity[nAddr] != 0xff) )
				{
					fSum += surfaceHeight[nAddr];
					nCount++;
				}
			}

		float fAccAvg = 0.f;
		if(nCount != 0)
		{
			fAccAvg = fSum / nCount;
		}

		if( (fInAvg == 0.f) || (fAccAvg == 0.f) )
		{
			fGap = 0.f;
		}
		else
		{
			fGap = fAccAvg - fInAvg;
		}
	}


	//-----------------------------

	int nInAddr, nOutAddr;
	int nInX, nInY;
	int nOutX, nOutY;

	for(nInY = 0; nInY < SpmIn.nSYNum; nInY++)
	{
		float fYPos = SpmIn.fYcen + (nInY - (int)(SpmIn.nSYNum / 2)) * SpmIn.fYresol;
		nOutY = (int)((fYPos - fYcen) / fYresol + (nSYNum / 2.f) + 0.5);

		if( nOutY < 0 )
		{
			nOutY = 0;
		}

		if( nOutY >= nSYNum )
		{
			nOutY = nSYNum - 1;
		}

		for(nInX = 0; nInX < SpmIn.nSXNum; nInX++)
		{
			float fXPos = SpmIn.fXcen + (nInX - ((int)(SpmIn.nSXNum/2))) * SpmIn.fXresol;
			nOutX = (int)((fXPos - fXcen) / fXresol + (nSXNum / 2.f) + 0.5);

			if( nOutX < 0 )
			{
				nOutX = 0;
			}

			if( nOutX >= nSXNum )
			{
				nOutX = nSXNum - 1;
			}

			nInAddr = nInX + nInY * SpmIn.nSXNum;
			nOutAddr = nOutX + nOutY * nSXNum;

			switch(surfaceValidity[nOutAddr])
			{
			case 0xff :
				surfaceValidity[nOutAddr] = SpmIn.surfaceValidity[nInAddr];
				surfaceHeight[nOutAddr] = SpmIn.surfaceHeight[nInAddr] + fGap;
				break;
			case NOISE_PXL :
				break;
			default :
				//				surfaceHeight[nOutAddr] = (surfaceHeight[nOutAddr] + SpmIn.surfaceHeight[nInAddr] + fGap) / 2.f;
				break;
			}

			/*
			  switch(surfaceValidity[nOutAddr])
			  {
			  case 0xff :
			  case NOISE_PXL :
			  surfaceValidity[nOutAddr] = SpmIn.surfaceValidity[nInAddr];
			  surfaceHeight[nOutAddr] = SpmIn.surfaceHeight[nInAddr] + fGap;
			  break;
			  default :
			  surfaceHeight[nOutAddr] = (surfaceHeight[nOutAddr] + SpmIn.surfaceHeight[nInAddr] + fGap) / 2.f;
			  break;
			  }
			*/
		}
	}

	if(fHMax < SpmIn.fHMax + fGap)
	{
		fHMax = SpmIn.fHMax + fGap;
	}

	if(fHMin > SpmIn.fHMin + fGap)
	{
		fHMin = SpmIn.fHMin + fGap;
	}


	/*
	  CSpmData SpmIn;
	  SpmIn.loadFromFile(strSpmFile);
	  SpmIn.fYcen *= -1.f; // For Stitching

	  QString str;
	  str.Format("%d, %d", nRow, nCol);

	  //-----------------------------

	  int nInAddr, nOutAddr;
	  int nInX, nInY;
	  int nOutX, nOutY;

	  for(nInY = 0; nInY < SpmIn.nSYNum; nInY++)
	  {
	  float fYPos = SpmIn.fYcen + (nInY - (int)(SpmIn.nSYNum / 2)) * SpmIn.fYresol;
	  nOutY = (int)((fYPos - fYcen) / fYresol) + (int)(nSYNum / 2);

	  for(nInX = 0; nInX < SpmIn.nSXNum; nInX++)
	  {
	  float fXPos = SpmIn.fXcen + (nInX - ((int)(SpmIn.nSXNum/2))) * SpmIn.fXresol;
	  nOutX = (int)((fXPos - fXcen) / fXresol) + (int)(nSXNum / 2);

	  nInAddr = nInX + nInY * SpmIn.nSXNum;
	  nOutAddr = nOutX + nOutY * nSXNum;

	  switch(surfaceValidity[nOutAddr])
	  {
	  case 0xff :
	  case NOISE_PXL :
	  surfaceValidity[nOutAddr] = SpmIn.surfaceValidity[nInAddr];
	  surfaceHeight[nOutAddr] = SpmIn.surfaceHeight[nInAddr];
	  break;
	  default :
	  surfaceHeight[nOutAddr] = (surfaceHeight[nOutAddr] + SpmIn.surfaceHeight[nInAddr]) / 2.f;
	  break;
	  }
	  }
	  }
	*/
}

void CSpmData::resize(int nRate)
{
	int nXStart = 0;
	int nXEnd = nSXNum;
	int nYStart = 0;
	int nYEnd = nSYNum;

	int nSXNumResize = nSXNum / nRate;
	int nSYNumResize = nSYNum / nRate;

	fXresol = fXresol * nRate;
	fYresol = fYresol * nRate;

	int nAddrFrom;
	int nAddrTo;

	for(int nY = nYStart; nY < nYEnd; nY += nRate)
	{
		for(int nX = nXStart; nX < nXEnd; nX += nRate)
		{
			nAddrFrom = nX + nY * nSXNum;
			nAddrTo = nX / nRate + nY / nRate * nSXNumResize;

			surfaceHeight[nAddrTo]  = surfaceHeight[nAddrFrom];
			surfaceValidity[nAddrTo]  = surfaceValidity[nAddrFrom];
		}
	}

	nSXNum = nSXNumResize;
	nSYNum = nSYNumResize;
}
