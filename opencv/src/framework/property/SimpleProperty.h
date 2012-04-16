#pragma once

#include "PropertyBase.h"

template<typename T>
class SimpleProperty : public PropertyBase<T>
{
public:
	SimpleProperty(const QString& name,
				   const T& value)
		: PropertyBase(name, value) {
	}
	SimpleProperty<T>& operator =(const T& rhs) {
		m_value = rhs;
		return *this;
	}
};

typedef SimpleProperty<int> SimplePropertyInt;
typedef SimpleProperty<double> SimplePropertyDouble;

// DECLARE_NO_RANGE_PROPERTY(QColor)
// DECLARE_NO_RANGE_PROPERTY(ColorPixel)

// typedef SimpleProperty<int> PropertyInt;
// typedef SimpleProperty<double> PropertyDouble;
// typedef SimpleProperty<ColorPixel> PropertyColorPixel;

