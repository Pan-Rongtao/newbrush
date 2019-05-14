#include "gui/DockPanel.h"
#include "gui/AttachedProperty.h"

using namespace nb::core;
using namespace nb::gui;

#define DOCKPANEL_ATTACHED_PROPERTY_DOCK	"DockPanel.Dock"

DockPanel::DockPanel()
{
}

DockPanel::~DockPanel()
{
}

void DockPanel::setDock(std::shared_ptr<UIElement> element, DockE dock)
{
	if (std::find(Children().begin(), Children().end(), element) != Children().end())
	{
		AttachedProperties::registerAttached(element, DOCKPANEL_ATTACHED_PROPERTY_DOCK, dock);
	}
}

DockE DockPanel::getDock(std::shared_ptr<UIElement> element)
{
	auto v = AttachedProperties::findAttached(element, DOCKPANEL_ATTACHED_PROPERTY_DOCK);
	return v.empty() ? DockE::Left : any_cast<DockE>(v);
}

nb::core::Size DockPanel::measureOverride(const nb::core::Size & availableSize)
{
	return nb::core::Size();
}

nb::core::Size DockPanel::arrangeOverride(const nb::core::Size & finalSize)
{
	return nb::core::Size();
}
