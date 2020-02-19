#pragma once
#include <vector>
#include <typeindex>
#include "newbrush/gui/Setter.h"
#include "newbrush/gui/Trigger.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API Style
{
public:
	//构建一个空的样式
	Style();

	//构建一个目标类型为targetType的样式
	Style(std::type_index targetType);
	
	//目标类型
	void setTargetType(std::type_index targetType);
	std::type_index targetType() const;

	//设置器集合
	std::vector<SetterBasePtr> &setters();

	//触发器集合
	std::vector<TriggerBasePtr> &triggers();

	
private:
	std::type_index				m_targetType;
	std::vector<SetterBasePtr>	m_setters;
	std::vector<TriggerBasePtr>	m_triggers;

};

class NB_API StyleHelpler
{
public:
	static void updateStyle(UIElement *uie, std::shared_ptr<Style> oldStyle, std::shared_ptr<Style> newStyle);

private:
	static void processSetters(UIElement * uie, std::shared_ptr<Style> style);
	static void processTriggers(UIElement * uie, std::shared_ptr<Style> style);
};

}
}