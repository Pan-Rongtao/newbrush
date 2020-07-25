#include "newbrush/gui/VisualStateMachine.h"
#include "newbrush/core/TimeSpan.h"

using namespace nb;

VisualState::VisualState()
	: VisualState("")
{
}

VisualState::VisualState(const std::string & name)
{
}

void VisualState::setName(const std::string & name)
{
	m_name = name;
}

const std::string & VisualState::name() const
{
	return m_name;
}

void VisualState::setStoryboard(StoryboardPtr sb)
{
	m_storyboard = sb;
}

StoryboardPtr VisualState::storyboard()
{
	return m_storyboard;
}

VisualTransition::VisualTransition()
{
}

void VisualTransition::setFrom(const std::string & from)
{
	m_from = from;
}

const std::string & VisualTransition::from() const
{
	return m_from;
}

void VisualTransition::setTo(const std::string & to)
{
	m_to = to;
}

const std::string & VisualTransition::to() const
{
	return m_to;
}

void VisualTransition::setDuration(const TimeSpan & duration)
{
	m_duration = duration;
}

const TimeSpan & VisualTransition::duration() const
{
	return m_duration;
}

void VisualTransition::setEasing(EasingBasePtr easing)
{
	m_easing = easing;
}

EasingBasePtr VisualTransition::easing() const
{
	return m_easing;
}

void VisualTransition::setStoryboard(StoryboardPtr sb)
{
	m_storyboard = sb;
}

StoryboardPtr VisualTransition::storyboard()
{
	return m_storyboard;
}

VisualStateGroup::VisualStateGroup()
	: VisualStateGroup("")
{
}

VisualStateGroup::VisualStateGroup(const std::string & name)
	: m_name(name)
{
}

void VisualStateGroup::setName(const std::string & name)
{
	m_name = name;
}

const std::string & VisualStateGroup::name() const
{
	return m_name;
}

VisualStatePtr VisualStateGroup::currentState()
{
	return m_currentState;
}

const std::vector<VisualStatePtr>& VisualStateGroup::states() const
{
	return m_states;
}

const std::vector<VisualTransitionPtr>& VisualStateGroup::transitions() const
{
	return m_transitions;
}

void VisualStateMachine::addGroup(VisualStateGroupPtr stateGroup)
{
	for (auto const &group : m_groups)
	{
		if (group->name() == stateGroup->name())
		{
			nbThrowException(std::logic_error, "[%s] is already exists", group->name().data());
		}
	}
	m_groups.push_back(stateGroup);
}

bool VisualStateMachine::gotoState(const std::string &stateGroupName, const std::string &stateName, bool useTransitions)
{
	auto state = findState(stateGroupName, stateName);
	if (!state)
	{
		return false;
	}

	auto sb = state->storyboard();
	sb->begin();
	return true;
}

VisualStateGroupPtr VisualStateMachine::findGroup(const std::string & groupName) const
{
	auto iter = std::find_if(m_groups.begin(), m_groups.end(), [&groupName](VisualStateGroupPtr group) {
		return group->name() == groupName;
	});
	return iter != m_groups.end() ? *iter : nullptr;
}

VisualStatePtr VisualStateMachine::findState(const std::string & groupName, const std::string & stateName) const
{
	auto group = findGroup(groupName);
	if (!group)
	{
		return nullptr;
	}

	auto const &states = group->states();
	auto iter = std::find_if(states.begin(), states.end(), [&stateName](VisualStatePtr s) {
		return s->name() == stateName;
	});
	return iter != states.end() ? *iter : nullptr;
}
