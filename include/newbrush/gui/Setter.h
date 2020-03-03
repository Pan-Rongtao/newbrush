#pragma once
#include "newbrush/core/Property.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/RoutedEvent.h"
#include "Poco/Dynamic/Var.h"

namespace nb{
namespace gui{

class UIElement;
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
	Setter(const DependencyProperty &dp, const Var &v);

	virtual void attach(UIElement* uie) override;

	DependencyProperty	property;	//属性
	Var					value;		//属性值
	std::shared_ptr<std::string> targetName; //目标名字
};

class NB_API EventSetter : public SetterBase
{
public:
	virtual void attach(UIElement* uie) override;

	RoutedEvent			event;
	RoutedEventHandler	handler;
};

using SetterBasePtr = std::shared_ptr<SetterBase>;

}}
