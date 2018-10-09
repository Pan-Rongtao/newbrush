#pragma once
#include "../core/Def.h"

namespace nb { namespace gui {

class NB_API EasingFunctionBase
{
public:
	EasingFunctionBase();
	virtual ~EasingFunctionBase();

	double GetEase(double normalizedTime) const;

	virtual double GetEaseDefault(double rate) const{return 0;};

	enum EasingMode
	{
		EaseIn = 0,
		EaseOut,
		EaseInOut,
	};

public:
	EasingMode m_mode;
};
}}

