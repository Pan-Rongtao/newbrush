#include "newbrush/gui/Style.h"

using namespace nb;
using namespace nb::gui;

Style::Style()
	: Style(typeid(void), nullptr)
{
}

Style::Style(const std::type_index & targetType)
	: Style(targetType, nullptr)
{
}

Style::Style(const std::type_index & targetType, std::shared_ptr<Style> baseOn)
	: m_targetType(targetType)
	, m_baseOn(baseOn)
{
}

void Style::setTargetType(const std::type_index & targetType)
{
	m_targetType = targetType;
}

std::type_index Style::targetType() const
{
	return m_targetType;
}

void Style::setBaseOn(std::shared_ptr<Style> baseOn)
{
	m_baseOn = baseOn;
}

std::shared_ptr<Style> Style::baseOn() const
{
	return m_baseOn;
}

std::vector<Setter>& Style::setters()
{
	return m_setters;
}

std::vector<TriggerBase>& Style::triggers()
{
	return m_triggers;
}
