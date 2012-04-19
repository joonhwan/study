#pragma once

#include "property/PropertyBase.h"

template<typename T>
class RangedProperty : public PropertyBase<T>
{
public:
    RangedProperty(const QString& name,
				   const T& value,
				   T valueMinLimit,
				   T valueMaxLimit)
		: PropertyBase<T>(name, value)
		, m_valueMinLimit(valueMinLimit)
		, m_valueMaxLimit(valueMaxLimit)
	{
	}
	const T& valueMaxLimit() const {
		return m_valueMaxLimit;
	}
	const T& valueMinLimit() const {
		return m_valueMinLimit;
	}
	bool isValid() const {
		return (m_value <= m_valueMaxLimit)
			&& (m_value >= m_valueMinLimit);
	}
	RangedProperty<T>& operator = (const T& rhs)
	{
		m_value = rhs;
		return *this;
	}
protected:
	T m_valueMinLimit;
	T m_valueMaxLimit;
};
