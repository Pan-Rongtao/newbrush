#pragma once

#include "core/ValueObject.h"

class GridLength : public nb::Core::ValueObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	enum UnitType
	{
		UnitType_Auto,
		UnitType_Length,
		UnitType_Star
	};

public:
	GridLength(void) : m_unitType(UnitType_Length), m_value(0) {}
	GridLength(float value) : m_unitType(UnitType_Length), m_value(value) {}
	GridLength(float value, UnitType type) : m_unitType(type), m_value(value) {}

//	~GridLength(void);

	bool IsAuto() const {return m_unitType == UnitType_Auto;}
	bool IsStar() const {return m_unitType == UnitType_Star;}
	float GetValue() const {return m_value;}

	UnitType GetUnitType() const {return m_unitType;}

private:
	UnitType m_unitType;
	float m_value;
};
