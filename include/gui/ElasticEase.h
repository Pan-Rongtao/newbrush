#pragma once
#include "EasingFunctionBase.h"

namespace nb { namespace gui {

class NB_API ElasticEase : public EasingFunctionBase
{
public:
	ElasticEase();
	virtual ~ElasticEase();

	void SetEasingMode(EasingMode mode);
	double GetEaseDefault(double normalizedTime) const;
	
	//float m_springiness;	// 弹力值
};

}}