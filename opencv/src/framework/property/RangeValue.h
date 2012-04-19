#pragma once

template <typename T>
class RangeValue
{
public:
	RangeValue(T minValue=0,
		  T maxValue=0)
	{
		setValue(minValue, maxValue);
	}
	void setValue(T minValue, T maxValue)
	{
		if (minValue > maxValue) {
			std::swap(minValue, maxValue);
		}
		m_minValue = minValue;
		m_maxValue = maxValue;
	}
	void minValue() const
	{
		return m_minValue;
	}
	void maxValue() const
	{
		return m_maxValue;
	}
protected:
	T m_minValue;
	T m_maxValue;
};

