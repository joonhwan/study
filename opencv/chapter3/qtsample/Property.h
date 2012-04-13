#pragma once

#include "types.h"
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
	void* key() {
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

template<typename T>
class Property : public PropertyBase<T>
{
public:
    Property(const QString& name,
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
	Property<T>& operator = (const T& rhs)
	{
		m_value = rhs;
		return *this;
	}
protected:
	T m_min;
	T m_max;
};

#define DECLARE_NO_RANGE_PROPERTY(TYPE)					\
	template<>											\
	class Property<TYPE> : public PropertyBase<TYPE>	\
	{													\
	public:												\
		Property(const QString& name,					\
				 const TYPE& value)						\
			: PropertyBase(name, value) {				\
		}												\
		Property<TYPE>& operator =(const TYPE& rhs) {	\
			m_value = rhs;								\
			return *this;								\
		}												\
	};

DECLARE_NO_RANGE_PROPERTY(QColor)
DECLARE_NO_RANGE_PROPERTY(ColorPixel)

typedef Property<int> PropertyInt;
typedef Property<double> PropertyDouble;
typedef Property<ColorPixel> PropertyColorPixel;

