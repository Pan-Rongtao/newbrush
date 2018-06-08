#pragma once

#include "EasingFunctionBase.h"

namespace nb { namespace Media {

	class NB_EXPORT PowerEase : public EasingFunctionBase
	{
		NB_OBJECT_TYPE_DECLARE();

	public:
		PowerEase(void);
		virtual ~PowerEase(void);

		void SetEasingMode(EasingMode mode);
		double GetEaseDefault(double normalizedTime) const;
	};

}}