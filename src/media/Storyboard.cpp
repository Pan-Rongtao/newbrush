#include "newbrush/media/Storyboard.h"

using namespace nb;

Storyboard::Storyboard()
{
	Completed += [&](const EventArgs &args) {
		for (auto child : m_children)
		{
			child->stop();
		}
	};
}

std::vector<TimelinePtr>& Storyboard::children()
{
	return m_children;
}

void Storyboard::begin()
{
	Timeline::begin();
	for (auto const &animation : m_children)
		animation->begin();
}

TimeSpan Storyboard::getActualDurationTimespan() const
{
	if (duration().hasTimeSpan())
	{
		return duration().timeSpan();
	}
	else
	{
		auto iter = std::max_element(m_children.begin(), m_children.end(), [](TimelinePtr tl0, TimelinePtr tl1) {
			return tl1->getActualDurationTimespan() > tl0->getActualDurationTimespan();
		});
		return (*iter)->getActualDurationTimespan();
	}
}
