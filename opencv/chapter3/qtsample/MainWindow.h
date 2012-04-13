#pragma once

#include "types.h"
#include <QMainWindow>

class ColorDetector;
class ColorIcon;
class QPushButton;
class QSlider;
class QLabel;

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
	void setButtonColor(QColor color);
	void updateResult(MonoBuffer result);
protected:
	QPushButton* m_processButton;
	QPushButton* m_openButton;
	QPushButton* m_selectColorButton;
	QSlider* m_thresholdSlider;
	QLabel* m_thresholdLabel;
	QLabel* m_originalImageLabel;
	QLabel* m_processedImageLabel;

	ColorDetector* m_colorDetector;
	QImage* m_targetColorIcon;
	QString m_lastDirectoryName;
	ColorIcon* m_colorIcon;

	void createUi();
	void createConnection();
	void loadSettings();
};
