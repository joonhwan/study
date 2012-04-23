#include "Algorithm.h"

Algorithm::Algorithm(Algorithm* parent)
	: QObject(parent)
{
	this->connect(parent, SIGNAL(processFailed(const QString&)),
				  SLOT(error(const QString&)));
}

//virtual
Algorithm::~Algorithm()
{
}

void Algorithm::link(Algorithm* linked)
{
	this->connect(linked, SIGNAL(processed()),
				  SLOT(process()));
}

bool Algorithm::process(const QString& hint)
{
	m_error = tr("Unknown error");
	m_successful = false;
	doProcess();
	if (m_successful) {
		emit processed();
	} else {
		emit processFailed(m_lastErrorReason);
	}
	return m_successful;
}

void Algorithm::reset()
{
	doReset();
	emit resetted();
}

void Algorithm::error(const QString& reason)
{
	m_successful = false;
	m_lastErrorReason = reason;
}
