#pragma once
#include "../core/Def.h"

namespace nb{ namespace gui{

class NB_API GridLength
{
public:
	enum GridUnitType
	{
		Auto,
		Pixcel,
		Star
	};

public:
	GridLength();
	GridLength(float value);
	GridLength(float value, GridUnitType type);
	bool operator == (const GridLength &other) const;
	bool operator != (const GridLength &other) const;

	bool isAuto() const;
	bool isStar() const;
	float value() const;

	GridUnitType gridUnitType() const;

private:
	GridUnitType	m_type;
	float			m_value;
};

}}