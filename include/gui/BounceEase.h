#pragma once

#include "EasingFunctionBase.h"

namespace nb { namespace Media {

	class NB_EXPORT BounceEase : public EasingFunctionBase
	{
		NB_OBJECT_TYPE_DECLARE();

	public:
		BounceEase(void);
		virtual ~BounceEase(void);

		void SetEasingMode(EasingMode mode);
		double GetEaseDefault(double normalizedTime) const;

		//float m_springiness;	// 弹力值
	};

}}