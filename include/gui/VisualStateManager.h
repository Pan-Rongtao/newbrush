#pragma once
#include <string>
#include "../core/Property.h"
#include "../core/Easing.h"
#include "Storyboard.h"

namespace nb{
namespace gui{

class UIElement;

class VisualState
{
public:
	core::Property_rw<std::string>					Name;		//名字
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//故事板
};

class VisualTransition
{
public:
	core::Property_rw<std::string>					From;		//起始状态
	core::Property_rw<std::string>					To;			//目标状态
	core::Property_rw<core::TimeSpan>				Duration;	//持续时间
	core::Property_rw<std::shared_ptr<Storyboard>>	Storyboard;	//故事板
	core::Property_rw<core::EasingBase>				Easing;		//缓动函数

};

class VisualGroup
{
public:
	core::Property_rw<std::string>					Name;		//名字
	core::Property_rw<std::vector<VisualState>>		States;		//状态集合

};

class VisualStateManager
{
public:
	static std::vector<VisualGroup>	getVisualStateGroups(std::shared_ptr<UIElement> element);
	static bool gotoElementState(std::shared_ptr<UIElement> element, const std::string &state, bool useTransitions);
};

}
}