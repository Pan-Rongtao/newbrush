#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../core/DependencyObject.h"

namespace nb{
namespace gui{

class NB_API RepeatBehavior : public DependencyObject
{
public:
	RepeatBehavior();
	RepeatBehavior(int count);
	RepeatBehavior(const TimeSpan &ts);
	static RepeatBehavior forever();

	void operator =(const RepeatBehavior &other);
	bool operator ==(const RepeatBehavior &other) const;
	bool operator !=(const RepeatBehavior &other) const;

	static DependencyProperty	CountProperty();	//重复次数的依赖属性
	static DependencyProperty	DurationProperty();	//持续时间的依赖属性

};

}}