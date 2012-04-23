#pragma once

#include "algo/AlgoTypes.h"
#include "algo/Algorithm.h"

class ImageResizer : public Algorithm
{
    Q_OBJECT
public:
    ImageResizer(Algorithm* parent=0);
    virtual ~ImageResizer();
	void setInput(const MonoBuffer& input);
protected:
	int m_zoomRatio;
	MonoBuffer m_input;
	MonoBuffer m_output;
	virtual void doProcess();
};
