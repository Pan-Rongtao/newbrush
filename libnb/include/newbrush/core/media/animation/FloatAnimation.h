#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"

namespace nb {
	
class NB_API FloatAnimationBase : public AnimationTimeline
{
public:
	

protected:
	FloatAnimationBase() = default;
};

class NB_API FloatAnimation : public FloatAnimationBase
{
public:
	FloatAnimation();
	FloatAnimation(float toValue, const Duration &duration);
	FloatAnimation(float toValue, const Duration &duration, FillBehaviorE fillBehavior);
	FloatAnimation(float fromValue, float toValue, const Duration &duration);
	FloatAnimation(float fromValue, float toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<float>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<float>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<float>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	float m_actualFrom;
	float m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API FloatKeyFrame : public DependencyObject
{
public:
	FloatKeyFrame();
	FloatKeyFrame(const TimeSpan &keyTime, float value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（float，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const FloatKeyFrame &other) const;
};

class NB_API FloatAnimationUsingKeyFrames : public FloatAnimationBase
{
public:
	std::set<FloatKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<FloatKeyFrame> m_keyFrames;
};


}