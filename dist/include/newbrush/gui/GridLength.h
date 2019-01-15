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
	GridLength(double value);
	GridLength(double value, GridUnitType type);
	bool operator == (const GridLength &other) const;
	bool operator != (const GridLength &other) const;

	bool isAuto() const;
	bool isStar() const;
	double value() const;

	GridUnitType gridUnitType() const;

private:
	GridUnitType	m_type;
	double			m_value;
};

}}