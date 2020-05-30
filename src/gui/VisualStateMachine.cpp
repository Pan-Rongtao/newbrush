#include "newbrush/gui/VisualStateMachine.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

VisualState::VisualState()
	: VisualState("", nullptr)
{
}

VisualState::VisualState(const std::string & name, std::shared_ptr<Storyboard> sb)
{
	setValue(NameProperty(), name);
	setValue(StoryboardProperty(), sb);
}

DependencyPropertyPtr VisualState::NameProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualState, std::string>("Name", std::string());
	return dp;
}

DependencyPropertyPtr VisualState::StoryboardProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualState, std::shared_ptr<Storyboard>>("Storyboard", nullptr);
	return dp;
}

VisualTransition::VisualTransition()
{
}

DependencyPropertyPtr VisualTransition::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, std::string>("From", std::string());
	return dp;
}

DependencyPropertyPtr VisualTransition::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, std::string>("To", std::string());
	return dp;
}

DependencyPropertyPtr VisualTransition::DurationProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, TimeSpan>("Duration", TimeSpan());
	return dp;
}

DependencyPropertyPtr VisualTransition::StoryboardProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, std::shared_ptr<Storyboard>>("Storyboard", nullptr);
	return dp;
}

DependencyPropertyPtr VisualTransition::EasingProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, std::shared_ptr<EasingBase>>("Easing", nullptr);
	return dp;
}

VisualStateGroup::VisualStateGroup(const std::string & name)
	: VisualStateGroup(name, {})
{
}

VisualStateGroup::VisualStateGroup(const std::string & name, const std::vector<std::shared_ptr<VisualState>>& states)
{
	setValue(NameProperty(), name);
	setValue(StatesProperty(), states);
}

DependencyPropertyPtr VisualStateGroup::NameProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::string>("Name", std::string());
	return dp;
}

DependencyPropertyPtr VisualStateGroup::StatesProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::vector<std::shared_ptr<VisualState>>>("States", {});
	return dp;
}

DependencyPropertyPtr VisualStateGroup::CurrentStateProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::shared_ptr<VisualState>>("CurrentState", std::make_shared<VisualState>());
	return dp;
}

DependencyPropertyPtr VisualStateGroup::TransitionsProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::vector<VisualTransition>>("Transitions", {});
	return dp;
}

void VisualStateMachine::addGroup(std::shared_ptr<VisualStateGroup> group)
{
	for (auto const &g : m_groups)
	{
		auto gName0 = g->getValue<std::string>(VisualStateGroup::NameProperty());
		auto gName1 = group->getValue<std::string>(VisualStateGroup::NameProperty());
		if (gName0 == gName1)
		{
			nbThrowException(std::logic_error, "[%s] is already exists", gName0.data());
		}
	}
	m_groups.push_back(group);
}

bool VisualStateMachine::gotoState(const std::string &groupName, const std::string & stateName, bool useTransitions)
{
	for (auto const &g : m_groups)
	{
		auto gName = g->getValue<std::string>(VisualStateGroup::NameProperty());
		if (gName == groupName)
		{
			if (useTransitions)
			{

			}
			auto states = g->getValue<std::vector<std::shared_ptr<VisualState>>>(VisualStateGroup::StatesProperty());
			for (auto const &s : states)
			{
				auto sName = s->getValue<std::string>(VisualState::NameProperty());
				if (sName == stateName)
				{
					auto sb = s->getValue<std::shared_ptr<Storyboard>>(VisualState::StoryboardProperty());
					sb->begin();
					return true;
				}
			}
		}
	}
	return false;
}
