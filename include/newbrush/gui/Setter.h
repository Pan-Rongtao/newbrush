#pragma once
#include "newbrush/core/RoutedEvent.h"

namespace nb{

class UIElement;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API SetterBase
{
public:
	virtual void attach(UIElement* uie);

protected:
	SetterBase() = default;
	virtual ~SetterBase() = default;
};

class NB_API Setter : public SetterBase
{
public:
	Setter();
	Setter(DependencyPropertyPtr dp, const var &v);
	Setter(DependencyPropertyPtr dp, const var &v, const std::string &_targetName);

	virtual void attach(UIElement* uie) override;

	DependencyPropertyPtr	property;	//属性
	var						value;		//属性值
	std::shared_ptr<std::string>	targetName; //目标名字
};

class NB_API EventSetter : public SetterBase
{
public:
	virtual void attach(UIElement* uie) override;

	RoutedEvent			event;
	RoutedEventHandler	handler;
};

using SetterBasePtr = std::shared_ptr<SetterBase>;

}
