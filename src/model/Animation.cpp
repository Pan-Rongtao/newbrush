#include "newbrush/model/Animation.h"

using namespace nb;

void Animation::setTarget(std::weak_ptr<Object> target)
{
	m_target = target;
	if (target.lock())
	{
		auto t0 = type::get(*(target.lock()));
		auto t1 = type::get<Object>();
		bool derived = t0 != t1 && t0.is_derived_from(t1);
		if (!derived)
		{
			nbThrowException(std::runtime_error, "[%s] is not derived from [%s], forgot to use RTTR_ENABLE ?", t0.get_name().data(), t1.get_name().data());
		}
	}
}

std::weak_ptr<Object> Animation::target() const
{
	return m_target;
}

void Animation::setTargetProperty(rttr::property property)
{
	m_targetProperty = property;
}

void Animation::setTargetPropertyName(const std::string & propertyName)
{
	auto target = m_target.lock();
	if (target)
	{
		auto targetProperty = type::get(*target).get_property(propertyName);
		if (!targetProperty)
		{
			int x = 10;
		}
		m_targetProperty = targetProperty;
	}
}

rttr::property Animation::targetProperty() const
{
	return m_targetProperty;
}

Animation::Animation()
	: m_targetProperty(rttr::type::get<Object>().get_property("none"))
{
}

void Animation::onStateChanged()
{
	if (currentState() == StateE::Active)
	{
		if (!m_target.lock())	nbThrowException(std::runtime_error, "'target' is nullptr for animation");
		if (!m_targetProperty)	nbThrowException(std::runtime_error, "'targetProperty' is invalid for animation");
	}
}

//////////////
Storyboard::Storyboard()
{
	Completed += [&](const EventArgs &args) 
	{
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
	{
		animation->begin();
	}
}

TimeSpan Storyboard::getActualDurationTimespan() const
{
	auto iter = std::max_element(m_children.begin(), m_children.end(), [](std::shared_ptr<Timeline> tl0, std::shared_ptr<Timeline> tl1) {
		return tl1->getActualDurationTimespan() > tl0->getActualDurationTimespan();
	});
	return (*iter)->getActualDurationTimespan();
}
