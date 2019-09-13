#pragma once
#include <vector>
#include <typeindex>
#include "../gui/Setter.h"
#include "../gui/Trigger.h"

namespace nb{
namespace gui{

class NB_API Style
{
public:
	//构建一个空的样式
	Style();

	//构建一个目标类型为targetType的样式
	Style(const std::type_index &targetType);
	
	//构建一个目标类型为targetType的样式，它继承于baseOn
	Style(const std::type_index &targetType, std::shared_ptr<Style> baseOn);

	//目标类型
	void setTargetType(const std::type_index &targetType);
	std::type_index targetType() const;

	//继承的样式
	void setBaseOn(std::shared_ptr<Style> baseOn);
	std::shared_ptr<Style> baseOn() const;

	//设置器集合
	std::vector<Setter> &setters();

	//触发器集合
	std::vector<TriggerBase> &triggers();

	
private:
	std::type_index				m_targetType;
	std::shared_ptr<Style>		m_baseOn;
	std::vector<Setter>			m_setters;
	std::vector<TriggerBase>	m_triggers;

};

}
}