#pragma once

#include <QString>
#include <QStringList>

class WTempDir;

// zip 파일을 압축해제한다음, 소멸시 다시 압축함.
// ZIP파일내의 파일을 편집/갱신하기위한 helper class.
class WZipFileDelegate
{
public:
	// zipPath의 압축파일을 temp dir 에 압축해제함.
    WZipFileDelegate(const QString& zipPath = QString());
	// m_autoCompressBack이 true(기본값 false)면 객체소멸시 
    virtual ~WZipFileDelegate();
	// zip파일내의 상대경로 relPathInZip 파일의 압축이 풀린 상태로
	// 존재하는 local file path를 반환. 존재하지 않으면, null
	// QString() 반환
	QString localPath(const QString& relPathInZip) const;
	// 압축해제된 파일을 다시 원본 zipPath로 압축함.
	bool compressBack();
	// 동작가능상태확인
	bool isValid() const;

	void setAutoCompressBack(bool enabled);
	bool autoCompressBack() const {
		return m_autoCompressBack;
	}
	void setCreateBackupWhenCompressBack(bool enabled) {
		m_createBackupWhenCompressBack = enabled;
	}
private:
	// 삭제시 자동으로 원본 zip을 local file로 갱신?
	bool m_autoCompressBack;
	bool m_createBackupWhenCompressBack;
	QString m_zipPath;
	WTempDir* m_tempDir;
	QStringList m_extractedFileList;
};




