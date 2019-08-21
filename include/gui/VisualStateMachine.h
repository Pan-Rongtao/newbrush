#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Easing.h"
#include "Storyboard.h"
#include "../gui/DependencyObject.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	Property_rw<std::string>			Name;		//名字
	Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//故事板

	static const DependencyProperty		NameProperty();
	static const DependencyProperty		StoryboardProperty();
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

	Property_rw<std::string>			From;		//起始状态
	Property_rw<std::string>			To;			//目标状态
	Property_rw<TimeSpan>			Duration;	//持续时间
	Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//故事板
	//Property_rw<shared_ptr<EasingBase>>	Easing;		//缓动函数

	static const DependencyProperty		FromProperty();
	static const DependencyProperty		ToProperty();
	static const DependencyProperty		DurationProperty();
	static const DependencyProperty		StoryboardProperty();
	static const DependencyProperty		EasingProperty();
};

class NB_API VisualStateGroup : public DependencyObject
{
public:
	VisualStateGroup(const std::string &name);
	VisualStateGroup(const std::string &name, const std::vector<std::shared_ptr<VisualState>> &states);

	Property_rw<std::string>							Name;		//名字
	Property_rw<std::vector<std::shared_ptr<VisualState>>>	States;		//状态集合
	Property_r<std::shared_ptr<VisualState>>					CurrentState;//当前状态
	Property_r<std::vector<VisualTransition>>			Transitions;

	struct StateChangedEventArgs {};
	Event<StateChangedEventArgs>						CurrentStateChanged;
	Event<StateChangedEventArgs>						CurrentStateChanging;

	static const DependencyProperty		NameProperty();
	static const DependencyProperty		StatesProperty();
	static const DependencyProperty		CurrentStateProperty();
	static const DependencyProperty		TransitionsProperty();
};

class NB_API VisualStateMachine
{
public:
	//添加一个状态组
	//异常：已有name相同的状态组
	void addGroup(std::shared_ptr<VisualStateGroup> group);
	bool gotoState(const std::string &groupName, const std::string &stateName, bool useTransitions);

private:
	std::vector<std::shared_ptr<VisualStateGroup>>	m_groups;
};

}
}