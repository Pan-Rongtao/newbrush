#pragma once
#include "EasingFunctionBase.h"

namespace nb { namespace gui {

class NB_API BounceEase : public EasingFunctionBase
{
public:
	BounceEase(void);
	virtual ~BounceEase(void);

	void SetEasingMode(EasingMode mode);
	double GetEaseDefault(double normalizedTime) const;

	//float m_springiness;	// 弹力值
};

}}