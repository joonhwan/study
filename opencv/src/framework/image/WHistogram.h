#pragma once

#include <QtGlobal>
#include <vector>

template<typename T, int C>
class WHistogramResult
{
public:
	typedef T* ValueArray[C];
	typedef T CountArray[C];
	typedef std::vector<T> Values;
	typedef std::vector<Values> ValuesList;
	WHistogramResult(int size=0x100)
	{
		m_valuesList.resize(C);
		for (int i = 0; i < C; ++i ) {
			m_valuesList[i].resize(size, 0);
			m_countArray[i] = size;
			m_valueArray[i] = &m_valuesList[i][0];
		}
	}
	ValueArray* getDataPtr() {
		return &m_valueArray;
	}
	ValueArray& getDataRef() {
		return m_valueArray;
	}
	const Values& values(int ch) const
	{
		m_values;
	}
	void resize(CountArray& valuesCount)
	{
		int index = 0;
		ValuesList::iterator it = m_valuesList.begin();
		for (; it!=m_valuesList.end(); ++it, ++index) {
			it->resize(valuesCount[index]);
		}
	}
	void accumulate()
	{
		ValuesList::iterator it = m_valuesList.begin();
		for (; it!=m_valuesList.end(); ++it) {
			Values::iterator itPrev = it->begin();
			Values::iterator itNext = itPrev + 1;
			for (; itNext != it->end(); ++itPrev, ++itNext) {
				(*itNext) += (*itPrev);
			}
		}
	}
	T value(int ch, int index) const
	{
		T value = 0;
		value = m_values[ch][index];
		return value;
	}
protected:
	ValueArray m_valueArray;
	CountArray m_countArray;
	ValuesList m_valuesList;
};

template<typename T>
class WHistogramResult<T, 1>
{
public:
	typedef std::vector<T> Values;
	WHistogramResult()
	{
	}
	T* getDataPtr() {
		return &m_values[0];
	}
	T* getDataRef() {
		return &m_values[0];
	}
	const Values& values() const
	{
		m_values;
	}
	void resize(int valuesCount)
	{
		m_values.resize(valuesCount);
	}
	T value(int index) const
	{
		return m_values[index];
	}
protected:
	Values m_values;
};

// WHistogramParameter는 각 채널의 level(즉, bin)갯수와 값의 목록이
// 전부 동일한 경우만 가정함. 즉, red는 100개, blue는 150개..  이런식으로
// 할 수는 없음.(그럴 필요가 있는가?)
class WHistogramParameter
{
public:
	WHistogramParameter()
	{
		m_levels.clear();
		for (int i = 0; i <= 255; ++i) {
			m_levels.push_back(i);
		}
	}
	virtual ~WHistogramParameter()
	{
	}
	WHistogramParameter& allChannel()
	{
		m_channel = -1;
		return *this;
	}
	WHistogramParameter& channel(int ch)
	{
		if (ch >= 0 && ch < 3) {
			m_channel = ch;
		} else {
			Q_ASSERT(FALSE);
			m_channel = -1; // just process all channels
		}
		return *this;
	}
	WHistogramParameter& range(int min, int max, int step=1)
	{
		// normalize parameters
		if (min > max) {
			std::swap(min, max);
		}
		if ( step < 0) {
			step = qAbs(step);
		}

		m_levels.clear();
		for (int i = min; i < max; i+=step) {
			m_levels.push_back(i);
		}
		return *this;
	}
	int levelsCount() const
	{
		return (int)m_levels.size();
	}
	const int* levels() const
	{
		return &m_levels[0];
	}
	int level(int index) const
	{
		return m_levels[index];
	}
protected:
	int m_channel;
	typedef std::vector<int> Levels;
	// 모든 채널이 동일함.
	Levels m_levels;
};

template<int C>
class IppHistogramParameter
{
public:
	typedef const int* ValueArray[C];
	typedef int CountArray[C];
	IppHistogramParameter(const WHistogramParameter& source)
	{
		for (int i = 0; i < C; ++i) {
			m_valueArray[i] = source.levels();
			m_countArray[i] = source.levelsCount();
		}
	}
	CountArray& levelsCount()
	{
		return m_countArray;
	}
	ValueArray& levels()
	{
		return m_valueArray;
	}
protected:
	ValueArray m_valueArray;
	CountArray m_countArray;
};

template<>
class IppHistogramParameter<1>
{
public:
	IppHistogramParameter(const WHistogramParameter& source)
		: m_source(source)
	{
	}
	int levelsCount() const
	{
		return m_source.levelsCount();
	}
	const int* levels()
	{
		return m_source.levels();
	}
protected:
	const WHistogramParameter& m_source;
};

// template<typename T, int C>
// class CvHistogramParameter
// {
// public:
// 	CvHistogramParameter(const WHistogramParameter<T>& source);


// {
// 	WHistogramParameter parameter;
// 	WHistogramData data;
// 	data = processor.histogram(inBuffer, parameter.channel(1).range(0,255));
// }

// void calcHistogram(In a, HistogramResult
