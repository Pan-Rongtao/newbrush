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

std::vector<std::shared_ptr<Timeline>>& Storyboard::children()
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
		auto iter = std::max_element(m_children.begin(), m_children.end(), [](std::shared_ptr<Timeline> tl0, std::shared_ptr<Timeline> tl1) {
			return tl0->getActualDurationTimespan() > tl1->getActualDurationTimespan();
		});
		return (*iter)->getActualDurationTimespan();
	}
}
