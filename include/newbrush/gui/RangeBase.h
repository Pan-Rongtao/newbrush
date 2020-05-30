#pragma once
#include "newbrush/gui/Control.h"
#include "newbrush/core/Event.h"

namespace nb{

class NB_API RangeBase : public Control
{
public:
	RangeBase();
	virtual ~RangeBase();

	static DependencyPropertyPtr ValueProperty();
	static DependencyPropertyPtr MaximumProperty();
	static DependencyPropertyPtr MinimumProperty();
	static DependencyPropertyPtr SmallChangeProperty();	//最小改变值，当获取焦点时键盘反向键的变化值
	static DependencyPropertyPtr LargeChangeProperty();	//最大变化值，当点击空白区域的变化值

	Event<RoutedProperyChangedEventArgs>	ValueChanged;

protected:
	virtual void onValueChanged(float oldValue, float newValue);
	virtual void onMaxinumChanged(float oldValue, float newValue);
	virtual void onMininumChanged(float oldValue, float newValue);
			
private:
	static var coerceValue(DependencyObject *d, var baseValue);
	static var coerceMaximum(DependencyObject *d, var baseValue);
	static var coerceMinimum(DependencyObject *d, var baseValue);

	static void onValuePropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);
	static void onMaxinumPropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);
	static void onMinimumPropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);

};

}