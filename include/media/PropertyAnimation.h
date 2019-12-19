/*******************************************************
**	PropertyAnimation|ColorAnimation
**
**	属性动画
**
**	属性动画做为最常用的单动画体系，用来处理属性的变化过程。
**	它由TargetProperty指定目标属性，From、To指定属性的变化
**	初值和目标值，Easing指定缓动对象。
**
**	值得注意的是，使用PropertyAnimation模板类，必须实现了
**	operator +, operator -, operator *，来表达属性对于的
**	运算变化的支持
**
**		潘荣涛
**
********************************************************/
#pragma once
#include <type_traits>
#include "../core/Color.h"
#include "AnimationTimeline.h"
#include "../core/Easing.h"

namespace nb{
namespace gui{

//内置类型属性动画
template<class T>
class NB_API PropertyAnimation : public AnimationTimeline<T>
{
public:
	PropertyAnimation() : PropertyAnimation(T(), T(), TimeSpan(), nullptr) {}
	PropertyAnimation(const T &to) : PropertyAnimation(T(), to, TimeSpan(), nullptr) {}
	PropertyAnimation(const T &from, const T &to) : PropertyAnimation(from, to, TimeSpan(), nullptr) {}
	PropertyAnimation(const T &from, const T &to, const TimeSpan &duration, Property_rw<T> *target)
		: From([&](T v) {set(FromProperty(), v); }, [&]()->T & {return get<T>(FromProperty()); })
		, To([&](T v) {set(ToProperty(), v); }, [&]()->T & {return get<T>(ToProperty()); })
		, By([&](T v) {set(ByProperty(), v); }, [&]()->T & {return get<T>(ByProperty()); })
	{
		From = from;
		To = to;
		Duration = duration;
		TargetProperty = target;
	}

	Property_rw<T>				From;
	Property_rw<T>				To;
	Property_rw<T>				By;
	static DependencyProperty	FromProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, T>("From", T()); return dp; }
	static DependencyProperty	ToProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, T>("To", T()); return dp; }
	static DependencyProperty	ByProperty() { static auto dp = DependencyProperty::registerDependency<AnimationTimeline, T>("By", T()); return dp; }

protected:
	//要求属性必须实现了operator +, operator -, operator *，否则需要使用模板特化特性来重写
	virtual void progressing(float progress) override
	{
		if (!TargetProperty)	return;

		decltype(progress) ft = (decltype(progress))Easing()->easeInCore(progress);
		*TargetProperty = From() + (To() - From()) * ft;
	}
};

//特化Color
template<>
void PropertyAnimation<Color>::progressing(float progress)
{
	if (!TargetProperty)	return;

	decltype(progress) ft = (decltype(progress))Easing()->easeInCore(progress);
	int r = (int)((int)From().red() + ft * ((int)To().red() - (int)From().red()));
	int g = (int)((int)From().green() + ft * ((int)To().green() - (int)From().green()));
	int b = (int)((int)From().blue() + ft * ((int)To().blue() - (int)From().blue()));
	(*TargetProperty)().setRgb(r, g, b);
}

}
}