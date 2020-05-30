#pragma once
#include <map>
#include "newbrush/core/DataContext.h"

namespace nb{

class Binding;
class DependencyProperty;
class DependencyObject;
using BindingPtr = std::shared_ptr<Binding>;
using DependencyObjectPtr = std::shared_ptr<DependencyObject>;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API BindingMaster
{
public:
	//添加一个绑定
	//target：目标依赖对象，可以是UI元素或非UI元素
	static void addBinding(DependencyObjectPtr target, DependencyPropertyPtr dp, BindingPtr bd);

private:
	static void setToTarget(DependencyObjectPtr target, DependencyPropertyPtr dp, const var &value);

	using ObjectPropertysContainer = std::vector<std::pair<DependencyObjectPtr, DependencyPropertyPtr>>;
	static std::map<BindingPtr, ObjectPropertysContainer>	g_bindingmap;
};


}