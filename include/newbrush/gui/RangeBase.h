#pragma once
#include "newbrush/gui/Control.h"
#include "newbrush/core/Event.h"

namespace nb{

class NB_API RangeBase : public Control
{
public:
	RangeBase();
	virtual ~RangeBase();

	static DependencyProperty ValueProperty();
	static DependencyProperty MaximumProperty();
	static DependencyProperty MinimumProperty();
	static DependencyProperty SmallChangeProperty();	//最小改变值，当获取焦点时键盘反向键的变化值
	static DependencyProperty LargeChangeProperty();	//最大变化值，当点击空白区域的变化值

	Event<RoutedProperyChangedEventArgs>	ValueChanged;

protected:
	virtual void onValueChanged(float oldValue, float newValue);
	virtual void onMaxinumChanged(float oldValue, float newValue);
	virtual void onMininumChanged(float oldValue, float newValue);
			
private:
	static Var coerceValue(DependencyObject *d, Var baseValue);
	static Var coerceMaximum(DependencyObject *d, Var baseValue);
	static Var coerceMinimum(DependencyObject *d, Var baseValue);

	static void onValuePropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);
	static void onMaxinumPropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);
	static void onMinimumPropertyChanged(DependencyObject *d, DependencyPropertyChangedEventArgs *e);

};

}