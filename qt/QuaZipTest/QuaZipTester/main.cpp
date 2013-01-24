#include "WTempDir.h"
#include "WZipFileDelegate.h"
#include "QuaZip/quazip.h"
#include "QuaZip/quazipfile.h"
#include "QuaZip/JlCompress.h"
#include <QtGui>

const char* ZIP_PATH = "c:/temp/mytest.rcz";

QDir generateFiles(const QString& directory_name)
{
	QDir dir(directory_name);
	dir.mkpath(".");
	{
		QFile mainDataFile(dir.filePath("maindata.txt"));
		if (mainDataFile.open(QIODevice::WriteOnly))
		{
			QTextStream s(&mainDataFile);
			s << "This is main data File." << endl;
			for (int i=0; i<1000; ++i) {
				s << QString("data-%1: %2, %3").arg(i).arg(i%4).arg(i%5) << endl;
			}
		}
	}
	dir.mkdir("images");
	dir.cd("images");
	{
		for (int i=0; i<3; ++i) {
			QFile image(dir.filePath(QString("image-%1.dat").arg(i)));
			if (image.open(QIODevice::WriteOnly)) {
				QDataStream s(&image);
				for (int x=0; x<100*1024; ++x) {
					s << char(x % 0xff);
				}
			}
		}
	}
	dir.cdUp();

	return dir;
}


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("QuaZipTester");

	QDir dir = generateFiles("test/directory_to_archive");
	QFileInfoList fileInfoList;
	QDirIterator it(dir.absolutePath(),
					QDir::AllEntries | QDir::NoDotAndDotDot,
					QDirIterator::Subdirectories);
	while (it.hasNext()) {
		it.next();
		fileInfoList << it.fileInfo();
		// qDebug() << it.next();
	}

	bool done = false;
	do
	{
#ifdef USE_RAW_API
		QuaZip zip(ZIP_PATH);
		if (!zip.open(QuaZip::mdCreate)) {
			break;
		}

		const char* password = 0;
		quint32 crc = 0;
		bool errored = false;
		char buf[4096];

		foreach(const QFileInfo& fileInfo, fileInfoList) {
			if (fileInfo.isDir()) {
				continue;
			}
			QuaZipFile zipFile(&zip);
			QString relPath = dir.relativeFilePath(fileInfo.absoluteFilePath());
			QuaZipNewInfo newInfo(relPath, fileInfo.absoluteFilePath());
			int method = fileInfo.isDir() ? 0 : Z_DEFLATED;
			if (!zipFile.open(QIODevice::WriteOnly, newInfo, password, crc, method)) {
				goto loopend;
			}
			if (!fileInfo.isDir()) {
				QFile file(fileInfo.absoluteFilePath());
				if (!file.open(QIODevice::ReadOnly)) {
					goto loopend;
				}
				while (!file.atEnd()) {
					qint64 l = file.read(buf, 4096);
					if (l<=0) {
						goto loopend;
					}
					if (l!=zipFile.write(buf, l)) {
						goto loopend;
					}
				}
			}
			zipFile.close();
		}
		zip.setComment("This is a commen string in my archive by joonhwan");
		zip.close();
#endif
		JlCompress::compressDir(ZIP_PATH, dir.absolutePath());
		done = true;
	} while (0);

#ifdef USE_RAW_API
loopend:
#endif
	if (!done) {
		QMessageBox::critical(0, "ZipFail", "Failed");
	}


	QMessageBox::information(0, "ZipModify", "Will modify one file...");

	done = false;
	do
	{
		// WTempDir tempDir;
		// if (tempDir.isValid()) {
		// 	JlCompress::extractDir(ZIP_PATH, tempDir.dir().absolutePath());
		// }
		WZipFileDelegate zip(ZIP_PATH);
		if (zip.isValid()) {
			QFile file(zip.localPath("images/image-2.dat"));
			if (file.open(QIODevice::ReadWrite))
			{
				QDataStream s(&file);
				for (int i=0; i<32; ++i) {
					s << (uchar)4;
				}
			}
		}
		if (!zip.compressBack()) {
			break;
		}

		done = true;
	} while (0);

	return 0;
}
