#pragma once

#include "AnimationTimeline.h"

namespace nb { namespace Media {

class NB_EXPORT ObjectAnimation : public AnimationTimeline
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ObjectAnimation(void);
	virtual ~ObjectAnimation(void);

	NB_OBJECT_PROPERTY_DECLARE(From, nb::Core::RefObject);
	NB_OBJECT_PROPERTY_DECLARE(To, nb::Core::RefObject);

protected:
	virtual void OnFrameChanged(const nb::System::TimeSpan &frame);
};

}}
