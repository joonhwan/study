#include "MainWindow.h"
#include "algo/ColorDetector.h"
#include "algo/AlgoPropertySystem.h"
#include "ColorIcon.h"
#include "WImageViewer.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QVBoxLayout>

MainWindow::MainWindow(QObject* parent)
{
	m_propertySystem = new AlgoPropertySystem(this);
	m_colorDetector = new ColorDetector(m_propertySystem, this);
	m_colorIcon = new ColorIcon(10,10,QColor(0,200,0));
	createUi();
	createConnection();
	loadSettings();
}

//virtual
MainWindow::~MainWindow()
{
	QSettings s;
	s.setValue("lastDirectory", m_lastDirectoryName);
	s.setValue("targetColor", m_colorDetector->targetColor());

	delete m_colorIcon;
	delete m_colorDetector;
	delete m_propertySystem;
}

void MainWindow::createUi()
{
	m_openButton = new QPushButton(tr("&Open"));
	m_processButton = new QPushButton(tr("&Process"));
	m_originalImageLabel = new WImageViewer;
	m_processedImageLabel = new WImageViewer;

	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftLayout->addWidget(m_openButton);
	leftLayout->addWidget(m_processButton);
	leftLayout->addWidget(m_colorDetector->createEditor(0));

	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightLayout->addWidget(m_originalImageLabel);
	rightLayout->addWidget(m_processedImageLabel);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addLayout(leftLayout);
	layout->addLayout(rightLayout);
	QWidget* central = new QWidget;
	central->setLayout(layout);

	this->setCentralWidget(central);
}

void MainWindow::createConnection()
{
	connect(m_openButton, SIGNAL(clicked()),
			SLOT(openImageFile()));
	connect(m_processButton, SIGNAL(clicked()),
			SLOT(processImage()));
	connect(m_colorDetector, SIGNAL(sourceImageChanged(const QImage&)),
			m_originalImageLabel, SLOT(setImage(const QImage&)));
	connect(m_colorDetector, SIGNAL(targetColorChanged(QColor)),
			SLOT(setButtonColor(QColor)));
	connect(m_colorDetector, SIGNAL(processed(const MonoBuffer&)),
			SLOT(updateResult(const MonoBuffer&)));
}

void MainWindow::loadSettings()
{
	QSettings s;
	m_lastDirectoryName = s.value("lastDirectory", "").toString();
	QDir dir(m_lastDirectoryName);
	if (!dir.exists()) {
		m_lastDirectoryName.clear();
	}
	QColor color = s.value("targetColor", QColor(127,127,127)).value<QColor>();
	m_colorDetector->setTargetColor(color);
}

void MainWindow::openImageFile()
{
	QString filePathName = QFileDialog::getOpenFileName(this, tr("Select image file to process"),
														m_lastDirectoryName);
	if (!filePathName.isEmpty()) {
		if (m_colorDetector->setImageFile(filePathName)) {
			QFileInfo fileInfo(filePathName);
			m_lastDirectoryName = fileInfo.dir().absolutePath();
		} else {
			QMessageBox::warning(this, tr("Image File Load Error!"),
								 tr("Unable to load image file!. Check the image file's format!"));
		}
	}
}

void MainWindow::selectColor()
{
	QColor color = QColorDialog::getColor(m_colorIcon->color(), this, tr("Select target color."));
	if (color.isValid()) {
		m_colorDetector->setTargetColor(color);
	}
}

void MainWindow::processImage()
{
	m_colorDetector->process();
}

void MainWindow::updateResult(MonoBuffer result)
{
	m_processedImageLabel->setImage(result.toImage());
}
