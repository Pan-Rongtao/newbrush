#include "gui/Control.h"
#include "ControlPrivate.h"

using namespace nb::Gui;
using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(Control, UIElement, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(Control, Template, ControlTemplate, &Control::OnTemplateChanged);

Control::Control(void)
{
	m_private = new ControlPrivate(this);
}

Control::~Control(void)
{
	delete m_private;
}

IElementRender * Control::GetElementRender() const
{
	return m_private;
}

IElementRender * Control::GetElementRenderNoOveride() const
{
	return m_private;
}

void Control::OnTemplateChanged(PropertyValueChangedEventArgs &args)
{
	GetPrivate()->OnTemplateChanged();
}

nb::System::Size Control::MeasureOverride(const nb::System::Size &availableSize)
{
	return GetPrivate()->MeasureWork(availableSize);
}

nb::System::Size Control::ArrangeOverride(const nb::System::Size &finalSize)
{
	return GetPrivate()->ArrangeWork(finalSize);
}

void Control::GotoVisualState(const char *groupName, const char *stateName)
{
	UIElement::GotoVisualState(groupName, stateName);
	GetPrivate()->GotoVisualState(groupName, stateName);
}

NameRealm * Control::GetTemplateInstanceNameRealm() const
{
	return GetPrivate()->GetTemplateInstanceNameRealm();
}

