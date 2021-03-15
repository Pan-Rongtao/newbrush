#include "newbrush/Animation.h"

using namespace nb;

void Animation::setTarget(std::weak_ptr<Object> target)
{
	m_target = target;
	if (target.lock())
	{
		auto t0 = type::get(*(target.lock()));
		auto t1 = type::get<Object>();
		bool derived = t0 != t1 && t0.is_derived_from(t1);
		nbThrowExceptionIf(!derived, std::runtime_error, "[%s] is not derived from [%s], forgot to use RTTR_ENABLE ?", t0.get_name().data(), t1.get_name().data());
	}
}

void Animation::setTargetName(const std::string & name)
{
}

std::weak_ptr<Object> Animation::target() const
{
	return m_target;
}

void Animation::setTargetProperty(property property)
{
	m_targetProperty = property;
	m_targetPropertyNameMode = false;
}

void Animation::setTargetPropertyName(const std::string & propertyName)
{
	m_targetPropertyName = propertyName;
	m_targetPropertyNameMode = true;
	m_needUpdateTargetProperty = true;
}

const std::string & Animation::targetPropertyName() const
{
	return m_targetPropertyName;
}

property Animation::targetProperty()
{
	auto target = m_target.lock();
	if (m_targetPropertyNameMode && m_needUpdateTargetProperty)
	{
		m_targetProperty = type::get(*target).get_property(m_targetPropertyName);
		m_needUpdateTargetProperty = false;
	}
	return m_targetProperty;
}

Animation::Animation()
	: m_targetProperty(type::get<Object>().get_property("none"))
	, m_targetPropertyNameMode(false)
	, m_needUpdateTargetProperty(false)
{
}

void Animation::onStateChanged()
{
	if (currentState() == TimelineStateE::Active)
	{
		nbThrowExceptionIf(!target().lock(), std::runtime_error, "'target' is nullptr for animation");
		nbThrowExceptionIf(!targetProperty(), std::runtime_error, "'targetProperty' is invalid for animation");
	}
}

//////////////
Storyboard::Storyboard()
{
	Completed += [&](const EventArgs &args) 
	{
		for (auto child : m_children)
		{
		//	child->stop();
		}
	};
}

std::vector<ref<Timeline>>& Storyboard::children()
{
	return m_children;
}

void Storyboard::begin()
{
	//Timeline::begin();
	for (auto const &animation : m_children)
	{
		animation->begin();
	}
}

void Storyboard::stop()
{
	for (auto const &animation : m_children)
	{
		animation->stop();
	}
}

TimeSpan Storyboard::getActualDurationTimespan() const
{
	auto iter = std::max_element(m_children.begin(), m_children.end(), [](ref<Timeline> tl0, ref<Timeline> tl1) 
	{
		return tl1->getActualDurationTimespan() > tl0->getActualDurationTimespan();
	});
	return (*iter)->getActualDurationTimespan();
}
