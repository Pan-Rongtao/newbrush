#pragma once
#include "EasingFunctionBase.h"

namespace nb { namespace gui {

class NB_API LineEase : public EasingFunctionBase
{
public:
	LineEase();
	virtual ~LineEase();

	void SetEasingMode(EasingMode mode);
	double GetEaseDefault(double normalizedTime) const;
};

}}
