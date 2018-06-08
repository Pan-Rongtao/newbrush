#pragma once

#include "AnimationTimeline.h"
#include "system/Point.h"

using namespace nb::System;

namespace nb 
{ 
	namespace Media
	{
		class NB_EXPORT PointAnimation : public AnimationTimeline
		{
			NB_OBJECT_TYPE_DECLARE();

		public:
			PointAnimation(void);
			virtual ~PointAnimation(void);

			virtual void AnimateTo(int frame);

			NB_OBJECT_VALUE_PROPERTY_DECLARE(From, nb::System::Point);
			NB_OBJECT_VALUE_PROPERTY_DECLARE(To, nb::System::Point);

		protected:
			virtual void OnFrameChanged(const nb::System::TimeSpan &frame);
		};
	}
}
