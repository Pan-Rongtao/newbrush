#include "newbrush/gui/ControlTemplate.h"
#include "newbrush/gui/VisualTreeHelper.h"

using namespace nb;

ControlTemplate::ControlTemplate()
{
}

std::shared_ptr<UIElement> ControlTemplate::instance()
{
	std::shared_ptr<UIElement> instance;
	//loopTree(m_root.get(), instance);
	instance = m_root->clone();
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

std::vector<TriggerBasePtr> &ControlTemplate::triggers()
{
	return m_triggers;
}

std::type_index ControlTemplate::nodeType(UIElement * node) const
{
	return typeid(*node);
}

void ControlTemplate::loopTree(UIElement* node, UIElementPtr &instance) const
{
	if (!m_root) return;

	instance = node->clone();
	for (auto i = 0; i < node->childrenCount(); ++i)
	{
		auto sourceChild = node->getChild(i);
		auto newChild = sourceChild->clone();
		newChild->setParent(instance.get());
		if (sourceChild->childrenCount() >= 1)
		{
			loopTree(sourceChild, newChild);
		}
	}
}
