#pragma once
#include <map>
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/DataContext.h"

namespace nb{

class Binding;
class NB_API BindingMaster
{
public:
	//添加一个绑定
	//target：目标依赖对象，可以是UI元素或非UI元素
	static void addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty &dp, std::shared_ptr<Binding> bd);

private:
	static void onBingingDataChanged(const DataContext::ValueChangedArgs & args);
	static void setToTarget(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<DataContext> dataNode);

	static std::map<std::shared_ptr<Binding>, std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>>	g_bindingmap;
};


}