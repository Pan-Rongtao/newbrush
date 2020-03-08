#pragma once
#include "newbrush/gui/Setter.h"
#include "newbrush/core/Binding.h"
#include "TriggerAction.h"

namespace nb{

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

	virtual void attach(UIElement *uie);

	virtual void onElementPropertyChanged(UIElement * uie);

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

	virtual void attach(UIElement *uie) override;

	virtual void onElementPropertyChanged(UIElement * uie) override;

	void setProperty(const DependencyProperty &dp);
	const DependencyProperty property() const;

	void setValue(const Var &value);
	const Var &getValue() const;

	std::vector<SetterBasePtr> &setters();

private:
	DependencyProperty			m_property;	//触发条件的属性
	Var							m_value;	//触发条件的值
	std::vector<SetterBasePtr>	m_setters;	//条件成立后执行的setters
};

//多条件触发器
class NB_API MultiTrigger : public TriggerBase
{
public:
	MultiTrigger();
	MultiTrigger(const std::vector<Condition> &conditions, const std::vector<SetterBasePtr> setters);

	virtual void attach(UIElement *uie) override;

	virtual void onElementPropertyChanged(UIElement * uie) override;

	bool match(UIElement *uie) const;

	std::vector<Condition> &conditions();
	std::vector<SetterBasePtr> &setters();

private:
	std::vector<Condition>		m_conditions;	//触发条件组
	std::vector<SetterBasePtr>	m_setters;		//条件成立后执行的setters
};

class DataTrigger : public TriggerBase
{
public:
	DataTrigger();
	DataTrigger(std::shared_ptr<Binding> bd, const Var &value);

	void setBinding(std::shared_ptr<Binding> bd);
	std::shared_ptr<Binding> binding() const;

	std::vector<SetterBasePtr> &setters();

	virtual void attach(UIElement *uie) override;

	bool match() const;

private:
	BindingPtr					m_binding;	//绑定
	Var							m_value;	//触发的绑定值
	std::vector<SetterBasePtr>	m_setters;	//条件成立后执行的setters
};

class MultiDataTrigger : public TriggerBase
{
public:
	virtual void attach(UIElement *uie) override;

	bool match() const;

	std::vector<Condition>		conditions;	//触发条件组
	std::vector<SetterBasePtr>	setters;	//条件成立后执行的setters
};

//事件触发器，主要用于动画
class EventTrigger : public TriggerBase
{
public:
	virtual void attach(UIElement *uie) override;

	RoutedEvent						routedEvent;
	std::vector<TriggerActionPtr>	actions;
};

using TriggerBasePtr = std::shared_ptr<TriggerBase>;

}