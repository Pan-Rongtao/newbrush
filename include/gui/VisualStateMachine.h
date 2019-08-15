#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/Easing.h"
#include "Storyboard.h"

namespace nb{
namespace gui{

class UIElement;

class NB_API VisualState
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	core::Property_rw<std::string>					Name;		//名字
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//故事板
};

class NB_API VisualTransition
{
public:
	core::Property_rw<std::string>					From;		//起始状态
	core::Property_rw<std::string>					To;			//目标状态
	core::Property_rw<core::TimeSpan>				Duration;	//持续时间
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//故事板
	core::Property_rw<std::shared_ptr<core::EasingBase>>				Easing;		//缓动函数

};

class NB_API VisualStateGroup
{
public:
	VisualStateGroup(const std::string &name);
	VisualStateGroup(const std::string &name, const std::vector<std::shared_ptr<VisualState>> &states);

	core::Property_rw<std::string>					Name;		//名字
	core::Property_rw<std::vector<std::shared_ptr<VisualState>>>		States;		//状态集合
	core::Property_r<VisualState>					CurrentState;//当前状态
	core::Property_r<std::vector<VisualTransition>>	Transitions;
	struct StateChangedEventArgs {};
	core::Event<StateChangedEventArgs>				CurrentStateChanged;
	core::Event<StateChangedEventArgs>				CurrentStateChanging;
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