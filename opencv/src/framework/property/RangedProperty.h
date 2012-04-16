#pragma once

#include "property/propertybase.h"

template<typename T>
class RangedProperty : public PropertyBase<T>
{
public:
    RangedProperty(const QString& name,
				   const T& value,
				   T min,
				   T max)
		: PropertyBase<T>(name, value)
		, m_min(min)
		, m_max(max)
	{
	}
	const T& max() const {
		return m_max;
	}
	const T& min() const {
		return m_min;
	}
	bool isValid() const {
		return (m_value <= m_max)
			&& (m_value >= m_min);
	}
	RangedProperty<T>& operator = (const T& rhs)
	{
		m_value = rhs;
		return *this;
	}
protected:
	T m_min;
	T m_max;
};
