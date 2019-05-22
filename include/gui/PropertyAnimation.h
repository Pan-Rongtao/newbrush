#pragma once
#include "AnimationTimeline.h"
#include "Easing.h"
#include "../core/Color.h"
#include <type_traits>

namespace nb { namespace gui {

//平凡动画
template<class T>
class NB_API TrivialAnimation : public AnimationTimeline
{
public:
	TrivialAnimation() : TargetProperty(nullptr) , Easing(std::make_shared<LinearEase>())
	{
	//限制类型为基础类型（不限制，否则Point这些无法编译通过）
	//	static_assert(std::is_trivial<T>::value, "TrivialAnimation<T> only surpport trivial(basic) type");
		ProgressEvent += std::bind(&TrivialAnimation::onProgress, this, std::placeholders::_1);
	}
	virtual ~TrivialAnimation() = default;

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

private:
	//要求属性必须实现了operator +, operator -, operator *
	void onProgress(const Timeline::ProgressArgs &args)
	{
		auto t = args.progress;
		auto ft = Easing()->easeInCore(t);
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

};

}}