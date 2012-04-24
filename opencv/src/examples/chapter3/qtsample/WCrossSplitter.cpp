#include "WCrossSplitter.h"
#include <QSplitter>
#include <QVBoxLayout>

WCrossSplitter::WCrossSplitter(QWidget* parent)
	: QFrame(parent)
{
	m_vert = new QSplitter(Qt::Vertical);
	m_horzUp = new QSplitter(Qt::Horizontal);
	m_horzDown = new QSplitter(Qt::Horizontal);

	connect(m_horzUp, SIGNAL(splitterMoved(int,int)),
			SLOT(horzUpMoved()));
	connect(m_horzDown, SIGNAL(splitterMoved(int,int)),
			SLOT(horzDownMoved()));

	m_vert->addWidget(m_horzUp);
	m_vert->addWidget(m_horzDown);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setContentsMargins(0,0,0,0);
	layout->addWidget(m_vert);
	setLayout(layout);
}

//virtual
WCrossSplitter::~WCrossSplitter()
{
}

void WCrossSplitter::addUpperWidget(QWidget* w)
{
	m_horzUp->addWidget(w);
}

void WCrossSplitter::addLowerWidget(QWidget* w)
{
	m_horzDown->addWidget(w);
}

void WCrossSplitter::horzUpMoved()
{
	m_horzDown->setSizes(m_horzUp->sizes());
}

void WCrossSplitter::horzDownMoved()
{
	m_horzUp->setSizes(m_horzDown->sizes());
}

//virtual
void WCrossSplitter::showEvent(QShowEvent* e)
{
	horzUpMoved(); // synchronize
}

//virtual
void WCrossSplitter::resizeEvent(QResizeEvent* e)
{
	horzUpMoved(); // synchronize
}
