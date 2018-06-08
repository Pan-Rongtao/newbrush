#pragma once

#include "EasingFunctionBase.h"

namespace nb { namespace Media {

class NB_EXPORT LineEase : public EasingFunctionBase
{
	NB_OBJECT_TYPE_DECLARE();
public:
	LineEase(void);
	virtual ~LineEase(void);

	void SetEasingMode(EasingMode mode);
	double GetEaseDefault(double normalizedTime) const;
};

}}
