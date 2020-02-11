#pragma once
#include <string>
#include "newbrush/core/Property.h"
#include "newbrush/core/TimeSpan.h"
#include "newbrush/core/Easing.h"
#include "newbrush/media/Storyboard.h"
#include "newbrush/core/DependencyObject.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API VisualState : public DependencyObject
{
public:
	VisualState();
	VisualState(const std::string &name, std::shared_ptr<Storyboard> sb = nullptr);

	static DependencyProperty			NameProperty();			//名字的依赖属性
	static DependencyProperty			StoryboardProperty();	//故事板的依赖属性
};

class NB_API VisualTransition : public DependencyObject
{
public:
	VisualTransition();

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