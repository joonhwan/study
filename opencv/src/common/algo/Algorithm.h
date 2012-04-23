#pragma once

#include <QObject>

class Algorithm : public QObject
{
    Q_OBJECT
public:
	Algorithm(Algorithm* parent=0);
    virtual ~Algorithm();
	void link(Algorithm* linked);
signals:
	void processed();
	void processFailed(const QString& error);
	void resetted();
public slots:
	bool process();
	void reset();
protected slots:
	void error(const QString& reason);
protected:
	bool m_successful;
	QString m_lastErrorReason;
	virtual bool doProcess () = 0;
};
