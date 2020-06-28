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
	Setter(DependencyPropertyPtr dp, const var &v, const std::string &targetName);

	//控制的属性
	//异常：std::invalid_argument，dp为nullptr
	void setProperty(DependencyPropertyPtr dp);
	DependencyPropertyPtr property() const;

	//控制的值
	//异常：std::invalid_argument，v为空
	void setValue(const var &v);
	const var &value() const;

	//控制的目标名字
	void setTargetName(const std::string &name);
	const std::string &targetName() const;

	virtual void attach(UIElement* uie) override;

private:
	std::string m_targetName; //目标名字
	DependencyPropertyPtr m_property;	//属性
	var m_value;		//属性值
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
