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
#include "Easing.h"

namespace nb { namespace gui {

//内置类型属性动画
template<class T>
class NB_API PropertyAnimation : public AnimationTimeline<T>
{
public:
	//限制类型为基础类型（不限制，否则Point这些无法编译通过）
	PropertyAnimation()
	{
	//	static_assert(std::is_trivial<T>::value, "PropertyAnimation<T> only surpport trivial(basic) type");
	}
	virtual ~PropertyAnimation() = default;

	core::Property_rw<T>							From;
	core::Property_rw<T>							To;
	core::Property_rw<T>							By;

protected:
	//要求属性必须实现了operator +, operator -, operator *
	virtual void progressing(double progress) override
	{
		if (!TargetProperty)	return;

		auto ft = Easing()->easeInCore(progress);
		*TargetProperty = From() + (To() - From()) * ft;
	}
};

//颜色动画
class NB_API ColorAnimation : public AnimationTimeline<core::Color>
{
public:
	ColorAnimation();
	virtual ~ColorAnimation() = default;

	core::Property_rw<core::Color>					From;
	core::Property_rw<core::Color>					To;
	core::Property_rw<core::Color>					By;

protected:
	virtual void progressing(double progress) override;
};

}}