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

	//根
	void setRoot(UIElementPtr root);
	UIElementPtr root();

	//触发器集合
	std::vector<TriggerBase> triggers();

private:
	UIElementPtr				m_root;
	std::vector<TriggerBase>	m_triggers;
};

}}
