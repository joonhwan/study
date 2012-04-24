#pragma once

#include "algo/AlgoTypes.h"
#include <QMainWindow>

class ColorDetector;
class ColorIcon;
class QPushButton;
class QSlider;
class WImageViewer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QObject* parent=0);
    virtual ~MainWindow();
signals:
public slots:
protected slots:
	void processImage();
	void openImageFile();
	void selectColor();
	void updateResult(MonoBuffer result);
protected:
	QPushButton* m_processButton;
	QPushButton* m_openButton;
	WImageViewer* m_originalImageLabel;
	WImageViewer* m_processedImageLabel;

	class AlgoPropertySystem* m_propertySystem;
	ColorDetector* m_colorDetector;
	QImage* m_targetColorIcon;
	QString m_lastDirectoryName;
	ColorIcon* m_colorIcon;

	void createUi();
	void createConnection();
	void loadSettings();
};
