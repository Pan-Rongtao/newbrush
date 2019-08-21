#include "gui/VisualStateMachine.h"

using namespace nb;
using namespace nb::gui;

VisualState::VisualState()
	: VisualState("", nullptr)
{
}

VisualState::VisualState(const std::string & name, std::shared_ptr<nb::gui::Storyboard> sb)
	: Name([&](std::string v) { set(NameProperty(), v); }, [&]() {return get<std::string>(NameProperty()); })
	, Storyboard([&](std::shared_ptr<nb::gui::Storyboard> v) { set(StoryboardProperty(), v); }, [&]() {return get<std::shared_ptr<nb::gui::Storyboard>>(StoryboardProperty()); })
{
//	Name = name;
//	Storyboard = sb;
}

const DependencyProperty VisualState::NameProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualState, std::string>("Name", std::string());
	return dp;
}

const DependencyProperty VisualState::StoryboardProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualState, std::shared_ptr<nb::gui::Storyboard>>("Storyboard", nullptr);
	return dp;
}

VisualTransition::VisualTransition()
	: From([&](std::string v) { set(FromProperty(), v); }, [&]() {return get<std::string>(FromProperty()); })
	, To([&](std::string v) { set(ToProperty(), v); }, [&]() {return get<std::string>(ToProperty()); })
	, Duration([&](TimeSpan v) { set(DurationProperty(), v); }, [&]() {return get<TimeSpan>(DurationProperty()); })
	, Storyboard([&](std::shared_ptr<nb::gui::Storyboard> v) { set(StoryboardProperty(), v); }, [&]() {return get<std::shared_ptr<nb::gui::Storyboard>>(StoryboardProperty()); })
	//, Easing([&](shared_ptr<EasingBase> v) { set(EasingProperty(), v); }, [&]() {return get<shared_ptr<EasingBase>>(EasingProperty()); })
{
}

const DependencyProperty VisualTransition::FromProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualTransition, std::string>("From", std::string());
	return dp;
}

const DependencyProperty VisualTransition::ToProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualTransition, std::string>("To", std::string());
	return dp;
}

const DependencyProperty VisualTransition::DurationProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualTransition, TimeSpan>("Duration", TimeSpan());
	return dp;
}

const DependencyProperty VisualTransition::StoryboardProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualTransition, std::shared_ptr<nb::gui::Storyboard>>("Storyboard", nullptr);
	return dp;
}

const DependencyProperty VisualTransition::EasingProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualTransition, std::shared_ptr<EasingBase>>("Easing", nullptr);
	return dp;
}

VisualStateGroup::VisualStateGroup(const std::string & name)
	: VisualStateGroup(name, {})
{
}

VisualStateGroup::VisualStateGroup(const std::string & name, const std::vector<std::shared_ptr<VisualState>>& states)
	: Name([&](std::string v) { set(NameProperty(), v); }, [&]() {return get<std::string>(NameProperty()); })
	, States([&](std::vector<std::shared_ptr<VisualState>> v) { set(StatesProperty(), v); }, [&]() {return get<std::vector<std::shared_ptr<VisualState>>>(StatesProperty()); })
	, CurrentState([&]() {return get<std::shared_ptr<VisualState>>(CurrentStateProperty()); })
	, Transitions([&]() {return get<std::vector<VisualTransition>>(TransitionsProperty()); })
{
	Name = name;
	States = states;
}

const DependencyProperty VisualStateGroup::NameProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualStateGroup, std::string>("Name", std::string());
	return dp;
}

const DependencyProperty VisualStateGroup::StatesProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualStateGroup, std::vector<std::shared_ptr<VisualState>>>("States", {});
	return dp;
}

const DependencyProperty VisualStateGroup::CurrentStateProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualStateGroup, std::shared_ptr<VisualState>>("CurrentState", nullptr);
	return dp;
}

const DependencyProperty VisualStateGroup::TransitionsProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<VisualStateGroup, std::vector<VisualTransition>>("Transitions", {});
	return dp;
}

void VisualStateMachine::addGroup(std::shared_ptr<VisualStateGroup> group)
{
	for (auto const &g : m_groups)
		if (g->Name() == group->Name())
		{
			nbThrowException(std::logic_error, "[%s] is already exists", g->Name().data());
		}
	m_groups.push_back(group);
}

bool VisualStateMachine::gotoState(const std::string &groupName, const std::string & stateName, bool useTransitions)
{
	for (auto const &g : m_groups)
	{
		if (g->Name() == groupName)
		{
			if (useTransitions)
			{

			}
			for (auto const &s : g->States())
			{
				if (s->Name == stateName)
				{
					s->Storyboard()->begin();
					return true;
				}
			}
		}
	}
	return false;
}
