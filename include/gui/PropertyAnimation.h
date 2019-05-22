#pragma once
#include "AnimationTimeline.h"
#include "Easing.h"
#include "../core/Color.h"
#include <type_traits>

namespace nb { namespace gui {

//平凡动画
template<class T>
class NB_API PropertyAnimation : public AnimationTimeline
{
public:
	//限制类型为基础类型（不限制，否则Point这些无法编译通过）
	PropertyAnimation() : TargetProperty(nullptr) , Easing(std::make_shared<LinearEase>())
	{
	//	static_assert(std::is_trivial<T>::value, "PropertyAnimation<T> only surpport trivial(basic) type");
	}
	virtual ~PropertyAnimation() = default;

	template<class T>
	void beginAinimation(core::Property_rw<T> *property)
	{
		TargetProperty = property;
		start();
	}

	core::Property_rw<T>							From;
	core::Property_rw<T>							To;
	core::Property_rw<T>							By;
	core::Property_rw<T>							*TargetProperty;
	core::Property_rw<std::shared_ptr<EasingBase>>	Easing;

protected:
	//要求属性必须实现了operator +, operator -, operator *
	virtual void progressing(double progress) override
	{
		auto ft = Easing()->easeInCore(progress);
		*TargetProperty = From() + (To() - From()) * ft;
	}
};

//颜色动画
class NB_API ColorAnimation : public AnimationTimeline
{
public:
	ColorAnimation();
	virtual ~ColorAnimation() = default;

	void beginAinimation(core::Property_rw<core::Color> *property);

	core::Property_rw<core::Color>					From;
	core::Property_rw<core::Color>					To;
	core::Property_rw<core::Color>					By;
	core::Property_rw<core::Color>					*TargetProperty;
	core::Property_rw<std::shared_ptr<EasingBase>>	Easing;

protected:
	virtual void progressing(double progress) override;
};

}}