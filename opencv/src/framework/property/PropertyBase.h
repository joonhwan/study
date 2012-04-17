#pragma once

#include <QString>

template<typename T>
class PropertyBase
{
public:
    PropertyBase(const QString& name,
				 const T& value)
		: m_name(name)
		, m_value(value)
	{
	}
	void* id() {
		return this;
	}
	const T& value() const {
		return m_value;
	}
	const QString& name() const {
		return m_name;
	}
	operator const T() const {
		return m_value;
	}
	operator T() {
		return m_value;
	}
	bool operator == (const T& rhs) const
	{
		return m_value == rhs;
	}
	bool operator != (const T& rhs) const
	{
		return m_value != rhs;
	}
protected:
	QString m_name;
	T m_value;
	T m_min;
	T m_max;
};
