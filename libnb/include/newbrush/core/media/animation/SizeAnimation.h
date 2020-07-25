#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"

namespace nb {
	
class NB_API SizeAnimationBase : public AnimationTimeline
{
public:
	

protected:
	SizeAnimationBase() = default;
};

class NB_API SizeAnimation : public SizeAnimationBase
{
public:
	SizeAnimation();
	SizeAnimation(const Size &toValue, const Duration &duration);
	SizeAnimation(const Size &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	SizeAnimation(const Size &fromValue, const Size &toValue, const Duration &duration);
	SizeAnimation(const Size &fromValue, const Size &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<Size>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<Size>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<Size>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Size m_actualFrom;
	Size m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API SizeKeyFrame : public DependencyObject
{
public:
	SizeKeyFrame();
	SizeKeyFrame(const TimeSpan &keyTime, const Size &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（Size，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const SizeKeyFrame &other) const;
};

class NB_API SizeAnimationUsingKeyFrames : public SizeAnimationBase
{
public:
	std::set<SizeKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<SizeKeyFrame> m_keyFrames;
};


}