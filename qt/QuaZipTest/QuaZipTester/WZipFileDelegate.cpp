#include "WZipFileDelegate.h"
#include "WTempDir.h"
#include "QuaZip/JlCompress.h"
#include <QDebug>

WZipFileDelegate::WZipFileDelegate(const QString& zipPath)
	: m_tempDir(new WTempDir)
	, m_autoCompressBack(false)
	, m_createBackupWhenCompressBack(true)
{
	// normalize
	m_zipPath = QFileInfo(zipPath).absoluteFilePath();

	if (m_tempDir->isValid()) {
		m_extractedFileList = JlCompress::extractDir(m_zipPath, m_tempDir->dir().absolutePath());
	}
}

//virtual
WZipFileDelegate::~WZipFileDelegate()
{
	if (isValid() && m_autoCompressBack) {
		compressBack();
	}
	delete m_tempDir;
}

QString WZipFileDelegate::localPath(const QString& relFilePathInZipFile) const
{
	QString r;
	if (isValid()) {
		// 임시 압축해제 폴더 아래의 경로
		QString expected = m_tempDir->dir().absoluteFilePath(relFilePathInZipFile);
		QFileInfo fi(expected);
		if (fi.exists()) {
			r = fi.absoluteFilePath();
		}
	}
	return r;
}

bool WZipFileDelegate::compressBack()
{
	bool done = false;

	do
	{
		if (!isValid()) {
			break;
		}

		if (m_createBackupWhenCompressBack) {
			QFileInfo zip(m_zipPath);
			QFileInfo backup(m_zipPath + QLatin1String(".bak"));
			if (backup.exists()) {
				if (!QFile::remove(backup.absoluteFilePath())) {
					qWarning() << "unable to remove zip backup file : " << backup.absoluteFilePath();
					break;
				}
			}

			if (!QFile::rename(m_zipPath, backup.absoluteFilePath())) {
				qWarning() << "unabel to create zip backup file : " << zip.absoluteFilePath();
			}
		}

		if (!JlCompress::compressDir(m_zipPath, m_tempDir->dir().absolutePath())) {
			break;
		}

		done = true;
	} while (0);

	return done;
}

bool WZipFileDelegate::isValid() const
{
	return m_tempDir->isValid() && m_extractedFileList.count();
}

void WZipFileDelegate::setAutoCompressBack(bool enabled)
{
	m_autoCompressBack = enabled;
}
