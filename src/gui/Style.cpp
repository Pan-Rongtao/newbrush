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

void StyleHelpler::updateStyle(UIElement * uie, std::shared_ptr<Style> oldStyle, std::shared_ptr<Style> newStyle)
{
	if (!uie)
		nbThrowException(std::invalid_argument, "uie is nullptr");

	if (newStyle)
	{
		auto targetType = newStyle->targetType();
		auto setters = newStyle->setters();
		auto triggers = newStyle->triggers();
		for (auto triggerBase : triggers)
		{

		}
	}
	else
	{

	}
}

void StyleHelpler::processSetters(UIElement * uie, std::shared_ptr<Style> style)
{
	if (!style)
		return;

	for (auto setterBase : style->setters())
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
				nbThrowException(std::runtime_error, "unsupported SetterBase subclass in style triggers [%s]", typeid(setterBase).name());
		}
	}
}

void StyleHelpler::processTriggers(UIElement * uie, std::shared_ptr<Style> style)
{
}
