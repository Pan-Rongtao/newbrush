#include "gui/ControlTemplate.h"

using namespace nb::gui;

ControlTemplate::ControlTemplate()
{
}

void ControlTemplate::setRoot(UIElementPtr root)
{
	m_root = root;
}

UIElementPtr ControlTemplate::root()
{
	return m_root;
}

std::vector<TriggerBase> ControlTemplate::triggers()
{
	return m_triggers;
}
