#pragma once

#include <vector>
#include "gui/Timeline.h"
#include "core/PropertyLock.h"

namespace nb { namespace Media {

class Storyboard;
class StoryboardPrivate
{
public:
	StoryboardPrivate(Storyboard *owner);
	virtual ~StoryboardPrivate(void);
	void AddChild(Timeline *timeline);

	void BeginOverride();

	void OnFrameChanged(const nb::System::TimeSpan &frame);


	Storyboard * const m_owner;

	std::vector<TimelinePtr> m_childs;

//	nb::Core::PropertyValueLockPtr m_durationLock;

	nb::Core::PropertyLockPtr m_durationLock;
};

}}
