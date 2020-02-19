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
	Var						value;		//条件属性值
	BindingPtr				binding;	//适用于MultiDataTrigger
};

class NB_API TriggerBase
{
public:
	std::vector<TriggerActionPtr>	enterActions;
	std::vector<TriggerActionPtr>	exitActions;
};

//普通触发器
class NB_API Trigger : public TriggerBase
{
public:
	Trigger();
	Trigger(const DependencyProperty &dp, const Var &v);

	DependencyProperty			property;	//触发条件的属性
	Var							value;		//触发条件的值
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

//多条件触发器
class NB_API MultiTrigger : public TriggerBase
{
public:
	std::vector<Condition>		conditions;	//触发条件组
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

class DataTrigger : public TriggerBase
{
public:
	BindingPtr					binding;	//绑定
	Var							value;		//触发的绑定值
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	std::vector<Condition>		conditions;	//触发条件组
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

//事件触发器，主要用于动画
class EventTrigger : public TriggerBase
{
public:
	RoutedEvent						event;
	std::vector<TriggerActionPtr>	actions;
};

using TriggerBasePtr = std::shared_ptr<TriggerBase>;

}}