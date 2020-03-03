#include "newbrush/gui/ControlTemplate.h"
#include "newbrush/gui/VisualTreeHelper.h"

using namespace nb::gui;

ControlTemplate::ControlTemplate()
{
}

std::shared_ptr<UIElement> ControlTemplate::instance()
{
	std::shared_ptr<UIElement> instance;
	loopTree(m_root.get(), instance);
	return instance;
}

void ControlTemplate::setRoot(UIElementPtr root)
{
	m_root = root;
}

UIElementPtr ControlTemplate::root()
{
	return m_root;
}

std::vector<TriggerBase> &ControlTemplate::triggers()
{
	return m_triggers;
}

std::type_index ControlTemplate::nodeType(UIElement * node) const
{
	return typeid(*node);
}

void ControlTemplate::loopTree(UIElement* node, UIElementPtr instance) const
{
	if (!m_root) return;

	instance = std::make_shared<UIElement>();
	for (auto i = 0; i <= VisualTreeHelper::getChildrenCount(node); ++i)
	{
		auto newChild = std::make_shared<UIElement>();
		newChild->setParent(instance.get());
		auto childInTemplate = VisualTreeHelper::getChild(node, i);
		if (VisualTreeHelper::getChildrenCount(childInTemplate) >= 1)
		{
			loopTree(childInTemplate, instance);
		}
	}
}
