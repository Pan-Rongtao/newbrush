#include "newbrush/gui/Style.h"
#include "newbrush/gui/UIElement.h"

using namespace nb;

Style::Style()
	: Style(typeid(void))
{
}

Style::Style(std::type_index targetType)
	: m_targetType(targetType)
	, m_handlingPropertyChanged(false)
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
	checkTargetType(uie);
	//setters
	for (auto setterBase : setters())
	{
		setterBase->attach(uie);
	}
	//triggers
	for (auto triggerBase : triggers())
	{
		triggerBase->attach(uie);
	}
}

void Style::handlePropertyChanged(UIElement * uie, const DependencyProperty & dp, const var & v)
{
	//由于处理property改变时会set Property的值，会造成无限循环，判断m_handlingPropertyChanged避免循环
	if (m_handlingPropertyChanged)
		return;

	m_handlingPropertyChanged = true;
	for (auto triggerBase : triggers())
	{
		triggerBase->onElementPropertyChanged(uie);
	}
	m_handlingPropertyChanged = false;
}

void Style::checkTargetType(UIElement * uie)
{
	if (targetType() != std::type_index(typeid(*uie)))
		nbThrowException(std::logic_error, "style's targetType[%s] is mismatched for element[%s]", targetType().name(), typeid(*uie).name());
}
/*
void Style::onBingingDataChanged(const Binding::BindDataChangedEventArgs & args)
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
*/