#pragma once
#include "newbrush/gui/Setter.h"
#include "newbrush/core/Binding.h"
#include "TriggerAction.h"

namespace nb{
namespace gui{

class Condition
{
public:
	Condition();
	Condition(const DependencyProperty &dp, const Var &v);
	Condition(const DependencyProperty &dp, const Var &v, BindingPtr bd);

	DependencyProperty		property;	//条件属性
	BindingPtr				binding;	//适用于MultiDataTrigger
	Var						value;		//条件属性值
};

class UIElement;
class NB_API TriggerBase
{
public:
	virtual ~TriggerBase() = default;

	void processSetters(UIElement *uie, std::vector<SetterBasePtr> setters);

	std::vector<TriggerActionPtr>	enterActions;
	std::vector<TriggerActionPtr>	exitActions;

protected:
	TriggerBase() = default;
};

//普通触发器
class NB_API Trigger : public TriggerBase
{
public:
	Trigger();
	Trigger(const DependencyProperty &dp, const Var &v);

	bool match(const DependencyProperty &dp, const Var &v) const;

	DependencyProperty			property;	//触发条件的属性
	Var							value;		//触发条件的值
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

//多条件触发器
class NB_API MultiTrigger : public TriggerBase
{
public:
	bool match(UIElement *uie) const;

	std::vector<Condition>		conditions;	//触发条件组
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

class DataTrigger : public TriggerBase
{
public:
	bool match(const Var &v) const;

	BindingPtr					binding;	//绑定
	Var							value;		//触发的绑定值
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	bool match(const Var &v) const;

	std::vector<Condition>		conditions;	//触发条件组
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

//事件触发器，主要用于动画
class EventTrigger : public TriggerBase
{
public:
	RoutedEvent						routedEvent;
	std::vector<TriggerActionPtr>	actions;
};

using TriggerBasePtr = std::shared_ptr<TriggerBase>;

}}