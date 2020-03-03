#pragma once
#include "newbrush/core/Property.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Trigger.h"

namespace nb{
namespace gui{

class NB_API ControlTemplate
{
public:
	ControlTemplate();
	virtual ~ControlTemplate() = default;

	//实例化，返回该实例的根节点
	std::shared_ptr<UIElement> instance();

	//节点树根
	void setRoot(UIElementPtr root);
	UIElementPtr root();

	//触发器集合
	std::vector<TriggerBase> &triggers();

private:
	std::type_index nodeType(UIElement* node) const;
	void loopTree(UIElement* node, UIElementPtr instance) const;

	UIElementPtr				m_root;
	std::vector<TriggerBase>	m_triggers;
};

}}
