#pragma once
#include "../gui/Setter.h"
#include "../gui/Binding.h"

namespace nb{
namespace gui{

class Condition
{
public:
	DependencyProperty		property;	//条件属性
	Any						value;		//条件属性值
};

class TriggerBase
{

};

class NB_API Trigger : public TriggerBase
{
public:
	DependencyProperty		condition;	//触发条件的属性
	Any						value;		//触发条件的值
	std::vector<Setter>		setters;	//条件成立后执行的setters
};

class NB_API MultiTrigger : public TriggerBase
{
public:
	std::vector<Condition>	conditions;	//触发条件组
	std::vector<Setter>		setters;	//条件成立后执行的setters
};

class DataTrigger : public TriggerBase
{
public:
	BindingPtr				binding;	//绑定
	Any						value;		//触发的绑定值
	std::vector<Setter>		setters;	//条件成立后执行的setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	std::vector<Condition>	conditions;	//触发条件组
	std::vector<Setter>		setters;	//条件成立后执行的setters
};

class EventTrigger : public TriggerBase
{
public:

};

}}