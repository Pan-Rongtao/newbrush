#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/Easing.h"
#include "Storyboard.h"
#include "../core/DependencyObject.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	Property_rw<std::string>			Name;					//名字
	Property_rw<shared_ptr<Storyboard>>	Storyboard;				//故事板
	static DependencyProperty			NameProperty();			//名字的依赖属性
	static DependencyProperty			StoryboardProperty();	//故事板的依赖属性
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

	Property_rw<std::string>			From;				//起始状态
	Property_rw<std::string>			To;					//目标状态
	Property_rw<TimeSpan>				Duration;			//持续时间
	Property_rw<shared_ptr<Storyboard>>	Storyboard;			//故事板
	//Property_rw<shared_ptr<EasingBase>>	Easing;			//缓动函数

	static DependencyProperty			FromProperty();		//起始状态的依赖属性
	static DependencyProperty			ToProperty();		//目标状态的依赖属性
	static DependencyProperty			DurationProperty();	//持续时间的依赖属性
	static DependencyProperty			StoryboardProperty();//故事板的依赖属性
	static DependencyProperty			EasingProperty();	//缓动函数的依赖属性
};

class NB_API VisualStateGroup : public DependencyObject
{
public:
	VisualStateGroup(const std::string &name);
	VisualStateGroup(const std::string &name, const std::vector<std::shared_ptr<VisualState>> &states);

	Property_rw<std::string>							Name;					//名字
	Property_rw<std::vector<shared_ptr<VisualState>>>	States;					//状态集合
	Property_r<shared_ptr<VisualState>>					CurrentState;			//当前状态
	Property_r<std::vector<VisualTransition>>			Transitions;			//过度
	static DependencyProperty							NameProperty();			//名字的依赖属性
	static DependencyProperty							StatesProperty();		//状态集合的依赖属性
	static DependencyProperty							CurrentStateProperty();	//当前状态的依赖属性
	static DependencyProperty							TransitionsProperty();	//过度的依赖属性

	struct StateChangedEventArgs {};
	Event<StateChangedEventArgs>						CurrentStateChanged;	//当前状态改变完成事件
	Event<StateChangedEventArgs>						CurrentStateChanging;	//当前状态正在改变事件

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