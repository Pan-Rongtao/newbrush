#include "newbrush/gui/Trigger.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/core/DataContext.h"
#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/core/Log.h"

using namespace nb;

Condition::Condition()
	: Condition(nullptr, var(), nullptr)
{
}

Condition::Condition(DependencyPropertyPtr dp, const var & v)
	: Condition(dp, v, nullptr)
{
}

Condition::Condition(DependencyPropertyPtr dp, const var & v, BindingPtr bd)
	: property(dp)
	, value(v)
	, binding(bd)
{
}

void TriggerBase::attach(UIElement * uie)
{
}

void TriggerBase::onElementPropertyChanged(UIElement * uie)
{
}

void TriggerBase::processSetters(UIElement *uie, std::vector<SetterBasePtr> setters)
{
	for (auto setterBase : setters)
	{
		auto setter = std::dynamic_pointer_cast<Setter>(setterBase);
		if (setter)
		{
			if (setter->targetName)
			{
				auto node = VisualTreeHelper::findLogicalNode(uie, "rc");
				if (node)
				{
					node->setValue(setter->property, setter->value);
				}
			}
			else
			{
				uie->setValue(setter->property, setter->value);
			}
		}
		else
		{
			auto eventSetter = std::dynamic_pointer_cast<EventSetter>(setterBase);
			if (!eventSetter)
				nbThrowException(std::runtime_error, "unsupported SetterBase subclass in style setter [%s]", typeid(setterBase).name());
			uie->addHandler(eventSetter->event, eventSetter->handler);
		}
	}
}

Trigger::Trigger()
	: Trigger(nullptr, var())
{
}

Trigger::Trigger(DependencyPropertyPtr dp, const var & v)
	: m_property(dp)
	, m_value(v)
{
}

void Trigger::attach(UIElement *uie)
{
	onElementPropertyChanged(uie);
}

void Trigger::onElementPropertyChanged(UIElement * uie)
{
	if (uie->getValue(m_property) == m_value)
	{
		processSetters(uie, m_setters);
	//	Log::info("property=%s", m_property.name().data());
	}
}

void Trigger::setProperty(DependencyPropertyPtr dp)
{
	m_property = dp;
}

DependencyPropertyPtr Trigger::property() const
{
	return m_property;
}

void Trigger::setValue(const var & value)
{
	m_value = value;
}

const var & Trigger::getValue() const
{
	return m_value;
}

std::vector<SetterBasePtr>& Trigger::setters()
{
	return m_setters;
}

MultiTrigger::MultiTrigger()
{
}

MultiTrigger::MultiTrigger(const std::vector<Condition>& conditions, const std::vector<SetterBasePtr> setters)
	: m_conditions(conditions)
	, m_setters(setters)
{
}

void MultiTrigger::attach(UIElement * uie)
{
	onElementPropertyChanged(uie);
}

void MultiTrigger::onElementPropertyChanged(UIElement * uie)
{
	if (match(uie))
	{
		processSetters(uie, m_setters);
	}
}

bool MultiTrigger::match(UIElement * uie) const
{
	for (auto const &c : m_conditions)
	{
		if (uie->getValue(c.property) != c.value)
			return false;
	}
	return true;
}

std::vector<Condition>& MultiTrigger::conditions()
{
	return m_conditions;
}

std::vector<SetterBasePtr>& MultiTrigger::setters()
{
	return m_setters;
}

DataTrigger::DataTrigger()
{
}

DataTrigger::DataTrigger(std::shared_ptr<Binding> bd, const var & value)
	: m_value(value)
{
	setBinding(bd);
}

void DataTrigger::setBinding(std::shared_ptr<Binding> bd)
{
	m_binding = bd;
	if (m_binding)
	{
		m_binding->BindDataChanged += [](const Binding::BindDataChangedEventArgs & args) {

		};
	}
}

std::shared_ptr<Binding> DataTrigger::binding() const
{
	return m_binding;
}

std::vector<SetterBasePtr>& DataTrigger::setters()
{
	return m_setters;
}

void DataTrigger::attach(UIElement * uie)
{
	if(match())
	{
		processSetters(uie, m_setters);
	}
	m_binding->BindDataChanged += [uie, this](const Binding::BindDataChangedEventArgs & args) {
		processSetters(uie, this->m_setters);
	};
}

bool DataTrigger::match() const
{
	if (!m_binding)
		return false;
	return m_binding->source()->lookup(m_binding->path())->get() == m_value;
}

void MultiDataTrigger::attach(UIElement * uie)
{
	if (match())
	{
		processSetters(uie, setters);
	}

	for (auto c : conditions)
	{
		c.binding->BindDataChanged += [uie, this](const Binding::BindDataChangedEventArgs & args) {
			if (match())
				processSetters(uie, this->setters);
		};
	}
}

bool MultiDataTrigger::match() const
{
	for (auto const &c : conditions)
	{
		auto bd = c.binding;
		if (bd->source()->lookup(bd->path())->get() != c.value)
			return false;
	}
	return true;
}

void EventTrigger::attach(UIElement * uie)
{
	uie->addHandler(routedEvent, RoutedEventHandler([&](std::shared_ptr<RoutedEventArgs> args) {
		for (auto action : actions)
		{
			action->invoke();
		}
	}));
}
