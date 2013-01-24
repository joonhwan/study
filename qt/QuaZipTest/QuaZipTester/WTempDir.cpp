#include "WTempDir.h"
#include <QTemporaryFile>
#include <QDir>
#include <QDirIterator>
#include <QCoreApplication>

namespace {

const char* _QT_TEMP_TEMPLATE = "XXXXXX";

// http://john.nachtimwald.com/2010/06/08/qt-remove-directory-and-its-contents/
bool _removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = _removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }

    return result;
}

bool removeDir(const QString& dirPath)
{
	bool done = true;

	QDir dir(dirPath);
	if (dir.exists(dirPath)) {
		QDir::Filters filters = QDir::NoDotAndDotDot
								| QDir::System
								| QDir::Hidden
								| QDir::AllDirs
								| QDir::Files
								;
		QDirIterator it(dirPath, filters);
		while (it.hasNext()) {
			QString path = it.next();
			QFileInfo fi = it.fileInfo();
			if (fi.isDir()) {
				done = removeDir(path);
			} else {
				done = QFile::remove(fi.absoluteFilePath());
			}
			if (!done) {
				return done;
			}
		}
		done = dir.rmdir(dirPath);
	}
	return done;
}

}

WTempDir::WTempDir(QString dirNameTemplatePrefix)
{
	{
		QTemporaryFile file;
		if (!dirNameTemplatePrefix.isNull()) {
			if (!dirNameTemplatePrefix.endsWith(_QT_TEMP_TEMPLATE)) {
				dirNameTemplatePrefix += QLatin1String(_QT_TEMP_TEMPLATE);
			}
			file.setFileTemplate(dirNameTemplatePrefix);
		}
		if (file.open()) {
			m_tempDirPath = file.fileName();
		}
	}
	if (!m_tempDirPath.isNull()) {
		m_dir.setPath(m_tempDirPath);
	}
	m_dir.mkpath(".");
}

//virtual
WTempDir::~WTempDir()
{
	// 혹 사고로 인하여? 임시폴더아래의 폴더가 아닌 경우에 삭제되는 것을 방지
	if (m_dir.absolutePath().startsWith(QDir::tempPath(), Qt::CaseInsensitive)) {
		removeDir(m_dir.absolutePath());
	}
}
