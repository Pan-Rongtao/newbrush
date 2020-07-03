#pragma once
#include <string>
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/TimeSpan.h"
#include "newbrush/core/Event.h"
#include "newbrush/core/EventArgs.h"

namespace nb{

class UIElement;
class Storyboard;
class EasingBase;
using UIElementPtr = std::shared_ptr<UIElement>;
using StoryboardPtr = std::shared_ptr<Storyboard>;
using EasingBasePtr = std::shared_ptr<EasingBase>;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name);

	void setName(const std::string &name);
	const std::string &name() const;

	void setStoryboard(StoryboardPtr sb);
	StoryboardPtr storyboard();

private:
	std::string m_name;
	StoryboardPtr m_storyboard;
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

	void setFrom(const std::string &from);
	const std::string &from() const;

	void setTo(const std::string &to);
	const std::string &to() const;

	void setDuration(const TimeSpan &duration);
	const TimeSpan &duration() const;

	void setEasing(EasingBasePtr easing);
	EasingBasePtr easing() const;

	void setStoryboard(StoryboardPtr sb);
	StoryboardPtr storyboard();

private:
	std::string m_from;
	std::string m_to;
	TimeSpan m_duration;
	EasingBasePtr m_easing;
	StoryboardPtr m_storyboard;
};

using VisualStatePtr = std::shared_ptr<VisualState>;
using VisualTransitionPtr = std::shared_ptr<VisualTransition>;
class NB_API VisualStateGroup : public DependencyObject
{
public:
	VisualStateGroup();
	VisualStateGroup(const std::string &name);

	void setName(const std::string &name);
	const std::string &name() const;

	VisualStatePtr currentState();

	const std::vector<VisualStatePtr> &states() const;

	const std::vector<VisualTransitionPtr> &transitions() const;

	struct StateChangedEventArgs {};
	Event<StateChangedEventArgs> CurrentStateChanged;	//当前状态改变完成事件
	Event<StateChangedEventArgs> CurrentStateChanging;	//当前状态正在改变事件

private:
	std::string m_name;
	VisualStatePtr m_currentState;
	std::vector<VisualStatePtr> m_states;
	std::vector<VisualTransitionPtr> m_transitions;

};

using VisualStateGroupPtr = std::shared_ptr<VisualStateGroup>;
class NB_API VisualStateMachine
{
public:
	//添加一个状态组
	//异常：已有name相同的状态组
	void addGroup(VisualStateGroupPtr stateGroup);
	bool gotoState(const std::string &stateGroupName, const std::string &stateName, bool useTransitions);

private:
	VisualStateGroupPtr findGroup(const std::string &groupName) const;
	VisualStatePtr findState(const std::string &groupName, const std::string &stateName) const;

	std::vector<VisualStateGroupPtr> m_groups;
};

}