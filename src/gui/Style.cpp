#include "newbrush/gui/Style.h"
#include "newbrush/gui/UIElement.h"

using namespace nb;
using namespace nb::gui;

Style::Style()
	: Style(typeid(void))
{
}

Style::Style(std::type_index targetType)
	: m_targetType(targetType)
{
}

void Style::setTargetType(std::type_index targetType)
{
	m_targetType = targetType;
}

std::type_index Style::targetType() const
{
	return m_targetType;
}

std::vector<SetterBasePtr>& Style::setters()
{
	return m_setters;
}

std::vector<TriggerBasePtr>& Style::triggers()
{
	return m_triggers;
}

void Style::attach(UIElement * uie)
{
	//setters
	for (auto setterBase : setters())
	{
		auto setter = std::dynamic_pointer_cast<Setter>(setterBase);
		if (setter)
		{
			uie->set(setter->property, setter->value);
		}
		else
		{
			auto eventSetter = std::dynamic_pointer_cast<EventSetter>(setterBase);
			if (!eventSetter)
				nbThrowException(std::runtime_error, "unsupported SetterBase subclass in style setters [%s]", typeid(setterBase).name());
			uie->addHandler(eventSetter->event, eventSetter->handler);
		}
	}
	//triggers
	for (auto triggerBase : triggers())
	{
		auto trigger = std::dynamic_pointer_cast<Trigger>(triggerBase);
		auto multiTrigger = std::dynamic_pointer_cast<MultiTrigger>(triggerBase);
		auto dataTrigger = std::dynamic_pointer_cast<DataTrigger>(triggerBase);
		auto eventTrigger = std::dynamic_pointer_cast<EventTrigger>(triggerBase);
		if (dataTrigger && dataTrigger->binding)
		{
			auto source = dataTrigger->binding->source();
			source->ValueChanged += std::bind(&Style::onBingingDataChanged, this, std::placeholders::_1);
		}
		else if(eventTrigger)
		{
			uie->addHandler(eventTrigger->routedEvent, RoutedEventHandler([eventTrigger](std::shared_ptr<RoutedEventArgs> args) {
				for (auto action : eventTrigger->actions)
				{
					action->invoke();
				}
			}));
		}
	}
}

void Style::handlePropertyChanged(UIElement * uie, const DependencyProperty & dp, const Var & v)
{
	for (auto triggerBase : triggers())
	{
		auto trigger = std::dynamic_pointer_cast<Trigger>(triggerBase);
		auto multiTrigger = std::dynamic_pointer_cast<MultiTrigger>(triggerBase);
		auto dataTrigger = std::dynamic_pointer_cast<DataTrigger>(triggerBase);
		auto multiDataTrigger = std::dynamic_pointer_cast<MultiDataTrigger>(triggerBase);
		auto eventTrigger = std::dynamic_pointer_cast<EventTrigger>(triggerBase);
		if (trigger && trigger->match(dp, v))
		{
			trigger->processSetters(uie, trigger->setters);
		}
		else if (multiTrigger && multiTrigger->match(uie))
		{
			multiTrigger->processSetters(uie, trigger->setters);
		}
		else if (dataTrigger || multiDataTrigger || eventTrigger)
		{
			//do nothing
		}
		else
		{
			nbThrowException(std::runtime_error, "unsupported SetterBase subclass in style triggers [%s]", typeid(triggerBase).name());
		}
	}
}

void Style::onBingingDataChanged(const DataContext::ValueChangedArgs & args)
{
	auto v = args.value;
	for (auto triggerBase : triggers())
	{
		auto trigger = std::dynamic_pointer_cast<Trigger>(triggerBase);
		auto multiTrigger = std::dynamic_pointer_cast<MultiTrigger>(triggerBase);
		auto dataTrigger = std::dynamic_pointer_cast<DataTrigger>(triggerBase);
		auto multiDataTrigger = std::dynamic_pointer_cast<MultiDataTrigger>(triggerBase);
		auto eventTrigger = std::dynamic_pointer_cast<EventTrigger>(triggerBase);
		if (trigger || multiTrigger || eventTrigger)
		{
			//do nothing
		}
		else if (dataTrigger && dataTrigger->match(v))
		{
			StyleDataTrigger.invoke({ dataTrigger });
		}
		else if (multiDataTrigger && multiDataTrigger->match(v))
		{
			StyleMultiDataTrigger.invoke({ multiDataTrigger });
		}
		else
		{
			nbThrowException(std::runtime_error, "unsupported SetterBase subclass in style triggers [%s]", typeid(triggerBase).name());
		}
	}
}
