#pragma once
#include <vector>
#include <typeindex>
#include "newbrush/gui/Setter.h"
#include "newbrush/gui/Trigger.h"

namespace nb{

class UIElement;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

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

	void attach(UIElement * uie);

	void handlePropertyChanged(UIElement * uie, DependencyPropertyPtr dp, const var &v);
	
	struct StyleDataTriggerArgs { std::shared_ptr<DataTrigger> dataTrigger; };
	Event<StyleDataTriggerArgs> StyleDataTrigger;
	struct StyleMultiDataTriggerArgs { std::shared_ptr<MultiDataTrigger> multiDataTrigger; };
	Event<StyleMultiDataTriggerArgs> StyleMultiDataTrigger;

private:
	void checkTargetType(UIElement * uie);
	//void onBingingDataChanged(const Binding::BindDataChangedEventArgs & args);

	std::type_index				m_targetType;
	std::vector<SetterBasePtr>	m_setters;
	std::vector<TriggerBasePtr>	m_triggers;
	bool	m_handlingPropertyChanged;
};

}