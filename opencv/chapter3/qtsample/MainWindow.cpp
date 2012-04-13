#include "ColorDetector.h"
#include "ColorIcon.h"
#include "MainWindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QVBoxLayout>

MainWindow::MainWindow(QObject* parent)
{
	m_colorDetector = new ColorDetector(this);
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
}

void MainWindow::createUi()
{
	m_openButton = new QPushButton(tr("&Open"));
	m_selectColorButton = new QPushButton(*m_colorIcon, tr("&Select Color"));
	m_processButton = new QPushButton(tr("&Process"));
	m_thresholdSlider = new QSlider(Qt::Vertical);
	m_thresholdSlider->setRange(0,255*3);
	m_thresholdLabel = new QLabel;
	m_originalImageLabel = new QLabel;
	m_processedImageLabel = new QLabel;

	QVBoxLayout* left1Layout = new QVBoxLayout;
	left1Layout->addWidget(m_openButton);
	left1Layout->addWidget(m_selectColorButton);
	left1Layout->addWidget(m_thresholdSlider);
	left1Layout->addWidget(m_thresholdLabel);
	left1Layout->addWidget(m_processButton);

	QHBoxLayout* leftLayout = new QHBoxLayout;
	leftLayout->addLayout(left1Layout);
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
	connect(m_selectColorButton, SIGNAL(clicked()),
			SLOT(selectColor()));
	connect(m_thresholdSlider, SIGNAL(valueChanged(int)),
			m_colorDetector, SLOT(setThreshold(int)));
	connect(m_processButton, SIGNAL(clicked()),
			SLOT(processImage()));

	connect(m_colorDetector, SIGNAL(sourceImageChanged(const QPixmap&)),
			m_originalImageLabel, SLOT(setPixmap(const QPixmap&)));
	connect(m_colorDetector, SIGNAL(thresholdChanged(int)),
			m_thresholdSlider, SLOT(setValue(int)));
	connect(m_colorDetector, SIGNAL(targetColorChanged(QColor)),
			SLOT(setButtonColor(QColor)));
	connect(m_colorDetector, SIGNAL(processed(const MonoBuffer&)),
			SLOT(updateResult(const MonoBuffer&)));
}

void MainWindow::loadSettings()
{
	QSettings s;
	m_lastDirectoryName = s.value("lastDirectory", "").toString();
	QColor color = s.value("targetColor", QColor(127,127,127)).value<QColor>();
	m_colorDetector->setTargetColor(color);

	// for sure gui update
	setButtonColor(color);
}

void MainWindow::openImageFile()
{
	QString filePathName = QFileDialog::getOpenFileName(this, tr("Select image file to process"),
														m_lastDirectoryName);
	if (!filePathName.isEmpty()) {
		if (!m_colorDetector->setImageFile(filePathName)) {
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

void MainWindow::setButtonColor(QColor color)
{
	QSize size(10,10);
	QImage image(size, QImage::Format_RGB888);
	{
		QPainter painter(&image);
		QRect rect(QPoint(0,0), size);
		painter.fillRect(rect, color);
		painter.setPen(QColor(0,0,0));
		painter.drawRect(rect);
	}
	QPixmap pixmap;
	pixmap.convertFromImage(image);
	m_selectColorButton->setIcon(QIcon(pixmap));
}

void MainWindow::updateResult(MonoBuffer result)
{
	m_processedImageLabel->setPixmap(result.toPixmap());
}
