#pragma once

#include "wlookuptable_traits.h"
#include <vector>

template<typename T, int C>
class WLookupTable;

template<typename T>
class WLookupTable<T,1>
{
public:
	typename typedef WLookupTableTraits<T>::TableDataType TDT;
	typedef const TDT* ValueArrayType;
	typedef int CountArrayType;
	struct Item
	{
		Item(TDT _in,
			 TDT _out)
			: in(_in)
			, out(_out)
		{
		}
		TDT in;
		TDT out;
	};
	WLookupTable()
	{
	}
	virtual ~WLookupTable()
	{
	}
	int count() const
	{
		return (int)m_valuesIn.size();
	}
	void getCount(CountArrayType& array) const
	{
		array = m_valuesIn.size();
	}
	const T* valuesIn() const
	{
		return &m_valuesIn[0];
	}
	void getValuesIn(ValueArrayType& array) const
	{
		array = &m_valuesIn[0];
	}
	const T* valuesOut() const
	{
		return &m_valuesOut[0];
	}
	void getValuesOut(ValueArrayType& array) const
	{
		array = &m_valuesOut[0];
	}
	void clear()
	{
		m_valuesIn.clear();
		m_valuesOut.clear();
	}
	WLookupTable<T,1> & operator << (const Item& data)
	{
		m_valuesIn.push_back(data.in);
		m_valuesOut,push_back(data.out);
		return *this;
	}
	// bool loadFromFile(const QString& filePathName);
protected:
	std::vector<TDT> m_valuesIn;
	std::vector<TDT> m_valuesOut;
};

template<typename T>
class WLookupTable<T,3>
{
public:
	typename typedef WLookupTableTraits<T>::TableDataType TDT;
	typedef const TDT* ValueArrayType[3];
	typedef int CountArrayType[3];
	struct Item
	{
		Item(TDT _in0, TDT _in1, TDT _in2,
			 TDT _out0, TDT _out1, TDT _out2)
		{
			in0 = _in0;
			in1 = _in1;
			in2 = _in2;
			out0 = _out0;
			out1 = _out1;
			out2 = _out2;
		}
		TDT in0;
		TDT in1;
		TDT in2;
		TDT out0;
		TDT out1;
		TDT out2;
	};
	WLookupTable()
	{
		clear();
	}
	virtual ~WLookupTable()
	{
	}
	int count() const
	{
		// pick one and return its size
		return (int)m_valuesIn[0].size();
	}
	void getCount(CountArrayType& array) const
	{
		for (int i = 0; i < 3; ++i) {
			// pick one of 'in' and 'out'
			array[i] = m_valuesIn[0].size();
		}
	}
	void getValuesIn(ValueArrayType& array) const
	{
		// typedef const TDT* ValueArrayType[3];
		for (int i = 0; i < 3; ++i) {
			array[i] = &m_valuesIn[i][0];
		}
	}
	const TDT* valuesIn(int channel) const
	{
		const TDT* in = 0;
		if (channel >= 0 && channel < 3) {
			in = &m_valuesIn[channel][0];
		}
		return in;
	}
	void getValuesOut(ValueArrayType& array) const
	{
		for (int i = 0; i < 3; ++i) {
			array[i] = &m_valuesOut[i][0];
		}
	}
	const TDT* valuesOut(int channel) const
	{
		const TDT* out = 0;
		if (channel >= 0 && channel < 3) {
			out = &m_valuesOut[channel][0];
		}
		return out;
	}
	void clear()
	{
		for (int i = 0; i < 3; ++i) {
			m_valuesIn[i].clear();
			m_valuesOut[i].clear();
		}
	}
	WLookupTable<T,3>& operator << (const Item& data)
	{
		for (int i = 0; i < 3; ++i) {
			m_valuesIn[0].push_back(data.in0);
			m_valuesIn[1].push_back(data.in1);
			m_valuesIn[2].push_back(data.in2);
			m_valuesOut[0].push_back(data.out0);
			m_valuesOut[1].push_back(data.out1);
			m_valuesOut[2].push_back(data.out2);
		}
	}
	// bool loadFromFile(const QString& filePathName);
protected:
	std::vector<TDT> m_valuesIn[3];
	std::vector<TDT> m_valuesOut[3];
};
