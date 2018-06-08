#pragma once

#include "AnimationTimeline.h"

namespace nb { namespace Media {

	class NB_EXPORT FloatAnimation : public AnimationTimeline
	{
		NB_OBJECT_TYPE_DECLARE();

	public:
		FloatAnimation(void);
		virtual ~FloatAnimation(void);

//		virtual void AnimateTo(int frame);

		NB_OBJECT_VALUE_PROPERTY_DECLARE(From, Core::Float);
		NB_OBJECT_VALUE_PROPERTY_DECLARE(To, Core::Float);

	protected:
		virtual void OnFrameChanged(const nb::System::TimeSpan &frame);

	};
}}
