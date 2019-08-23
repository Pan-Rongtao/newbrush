#include "gui/VisualStateMachine.h"

using namespace nb;
using namespace nb::gui;

VisualState::VisualState()
	: VisualState("", nullptr)
{
}

VisualState::VisualState(const std::string & name, shared_ptr<gui::Storyboard> sb)
	: Name([&](std::string v) { set(NameProperty(), v); }, [&]()->std::string& {return get<std::string>(NameProperty()); })
	, Storyboard([&](shared_ptr<gui::Storyboard> v) { set(StoryboardProperty(), v); }, [&]()->shared_ptr<gui::Storyboard>& {return get<shared_ptr<gui::Storyboard>>(StoryboardProperty()); })
{
//	Name = name;
//	Storyboard = sb;
}

DependencyProperty VisualState::NameProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualState, std::string>("Name", std::string());
	return dp;
}

DependencyProperty VisualState::StoryboardProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualState, std::shared_ptr<gui::Storyboard>>("Storyboard", nullptr);
	return dp;
}

VisualTransition::VisualTransition()
	: From([&](std::string v) { set(FromProperty(), v); }, [&]()->std::string& {return get<std::string>(FromProperty()); })
	, To([&](std::string v) { set(ToProperty(), v); }, [&]()->std::string& {return get<std::string>(ToProperty()); })
	, Duration([&](TimeSpan v) { set(DurationProperty(), v); }, [&]()->TimeSpan& {return get<TimeSpan>(DurationProperty()); })
	, Storyboard([&](shared_ptr<gui::Storyboard> v) { set(StoryboardProperty(), v); }, [&]()->shared_ptr<gui::Storyboard>& {return get<shared_ptr<gui::Storyboard>>(StoryboardProperty()); })
	//, Easing([&](shared_ptr<EasingBase> v) { set(EasingProperty(), v); }, [&]() {return get<shared_ptr<EasingBase>>(EasingProperty()); })
{
}

DependencyProperty VisualTransition::FromProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, std::string>("From", std::string());
	return dp;
}

DependencyProperty VisualTransition::ToProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, std::string>("To", std::string());
	return dp;
}

DependencyProperty VisualTransition::DurationProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, TimeSpan>("Duration", TimeSpan());
	return dp;
}

DependencyProperty VisualTransition::StoryboardProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, shared_ptr<gui::Storyboard>>("Storyboard", nullptr);
	return dp;
}

DependencyProperty VisualTransition::EasingProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualTransition, shared_ptr<EasingBase>>("Easing", nullptr);
	return dp;
}

VisualStateGroup::VisualStateGroup(const std::string & name)
	: VisualStateGroup(name, {})
{
}

VisualStateGroup::VisualStateGroup(const std::string & name, const std::vector<std::shared_ptr<VisualState>>& states)
	: Name([&](std::string v) { set(NameProperty(), v); }, [&]()->std::string& {return get<std::string>(NameProperty()); })
	, States([&](std::vector<shared_ptr<VisualState>> v) { set(StatesProperty(), v); }, [&]()->std::vector<shared_ptr<VisualState>>& {return get<std::vector<shared_ptr<VisualState>>>(StatesProperty()); })
	, CurrentState([&]() {return get<shared_ptr<VisualState>>(CurrentStateProperty()); })
	, Transitions([&]() {return get<std::vector<VisualTransition>>(TransitionsProperty()); })
{
	Name = name;
	States = states;
}

DependencyProperty VisualStateGroup::NameProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::string>("Name", std::string());
	return dp;
}

DependencyProperty VisualStateGroup::StatesProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::vector<std::shared_ptr<VisualState>>>("States", {});
	return dp;
}

DependencyProperty VisualStateGroup::CurrentStateProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, shared_ptr<VisualState>>("CurrentState", std::make_shared<VisualState>());
	return dp;
}

DependencyProperty VisualStateGroup::TransitionsProperty()
{
	static auto dp = DependencyProperty::registerDependency<VisualStateGroup, std::vector<VisualTransition>>("Transitions", {});
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
				if (s->Name() == stateName)
				{
					s->Storyboard()->begin();
					return true;
				}
			}
		}
	}
	return false;
}
