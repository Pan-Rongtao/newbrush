#pragma once

#include "EasingFunctionBase.h"

namespace nb { namespace Media {

class NB_EXPORT ElasticEase : public EasingFunctionBase
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ElasticEase(void);
	virtual ~ElasticEase(void);

	void SetEasingMode(EasingMode mode);
	double GetEaseDefault(double normalizedTime) const;
	
	//float m_springiness;	// 弹力值
};

}}