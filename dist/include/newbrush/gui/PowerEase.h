#pragma once
#include "EasingFunctionBase.h"

namespace nb { namespace gui {

class NB_API PowerEase : public EasingFunctionBase
{
public:
	PowerEase();
	virtual ~PowerEase();

	void SetEasingMode(EasingMode mode);
	double GetEaseDefault(double normalizedTime) const;
};

}}