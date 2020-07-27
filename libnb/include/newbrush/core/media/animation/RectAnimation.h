#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"
#include "newbrush/core/base/Rect.h"

namespace nb {
	
class NB_API RectAnimationBase : public AnimationTimeline
{
public:
	

protected:
	RectAnimationBase() = default;
};

class NB_API RectAnimation : public RectAnimationBase
{
public:
	RectAnimation();
	RectAnimation(const Rect &toValue, const Duration &duration);
	RectAnimation(const Rect &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	RectAnimation(const Rect &fromValue, const Rect &toValue, const Duration &duration);
	RectAnimation(const Rect &fromValue, const Rect &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<Rect>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<Rect>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<Rect>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Rect m_actualFrom;
	Rect m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API RectKeyFrame : public DependencyObject
{
public:
	RectKeyFrame();
	RectKeyFrame(const TimeSpan &keyTime, const Rect &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（Rect，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const RectKeyFrame &other) const;
};

class NB_API RectAnimationUsingKeyFrames : public RectAnimationBase
{
public:
	std::set<RectKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<RectKeyFrame> m_keyFrames;
};


}