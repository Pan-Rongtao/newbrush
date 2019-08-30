#pragma once
#include <map>
#include "../gui/Binding.h"
#include "../gui/DependencyObject.h"

namespace nb{
namespace gui{

class NB_API BindingMaster
{
public:
	//添加一个绑定
	//target：目标依赖对象，可以是UI元素或非UI元素
	static void addBinding(DependencyObjectPtr target, const DependencyProperty &dp, BindingPtr bd);

private:
	static void onBingingDataChanged(const ValueDataBase::ValueChangedArgs & args);
	static std::map<BindingPtr, std::pair<DependencyObjectPtr, DependencyProperty>>	g_bindingmap;
};



}}