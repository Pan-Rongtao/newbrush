#pragma once

#include "AnimationTimeline.h"
#include "system/Color.h"

using namespace nb::System;

namespace nb 
{ 
	namespace Media
	{
		class NB_EXPORT ColorAnimation : public AnimationTimeline
		{
			NB_OBJECT_TYPE_DECLARE();

		public:
			ColorAnimation(void);
			virtual ~ColorAnimation(void);

			virtual void AnimateTo(int frame);

			NB_OBJECT_VALUE_PROPERTY_DECLARE(From, nb::System::Color);
			NB_OBJECT_VALUE_PROPERTY_DECLARE(To, nb::System::Color);

		protected:
			virtual void OnFrameChanged(const nb::System::TimeSpan &frame);
		};
	}
}
