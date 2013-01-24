#pragma once

#include <QDir>

class WTempDir
{
public:
	// 임시디렉토리를 QTemporaryFile을 사용해 생성
	WTempDir(QString dirNameTemplatePrefix = QString());
	// 임시디렉토리를 삭제됨.
	virtual ~WTempDir();
	// 반환된 QDir을 WTempDir()객체가 파괴된 이후에 사용할 경우 문제
	// 발생함.
	QDir& dir() {
		return m_dir;
	}
	bool isValid() const {
		return !m_tempDirPath.isNull();
	}
protected:
	QString m_tempDirPath;
	QDir m_dir;
};
