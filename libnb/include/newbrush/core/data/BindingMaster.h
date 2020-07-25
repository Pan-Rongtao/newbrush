#pragma once
#include <map>
#include <vector>
#include "newbrush/core/data/Binding.h"
#include "newbrush/core/DependencyObject.h"

namespace nb{

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