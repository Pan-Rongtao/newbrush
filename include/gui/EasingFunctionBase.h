#pragma once

#include "core/Object.h"
#include "GuiDef.h"

namespace nb { namespace Media {

class NB_EXPORT EasingFunctionBase : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	EasingFunctionBase(void);
	virtual ~EasingFunctionBase(void);

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

