#pragma once
#include "newbrush/core/media/animation/AnimationTimeline.h"
#include "newbrush/core/base/Thickness.h"

namespace nb {
	
class NB_API ThicknessAnimationBase : public AnimationTimeline
{
public:
	

protected:
	ThicknessAnimationBase() = default;
};

class NB_API ThicknessAnimation : public ThicknessAnimationBase
{
public:
	ThicknessAnimation();
	ThicknessAnimation(const Thickness &toValue, const Duration &duration);
	ThicknessAnimation(const Thickness &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	ThicknessAnimation(const Thickness &fromValue, const Thickness &toValue, const Duration &duration);
	ThicknessAnimation(const Thickness &fromValue, const Thickness &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<Thickness>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<Thickness>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<Thickness>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Thickness m_actualFrom;
	Thickness m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API ThicknessKeyFrame : public DependencyObject
{
public:
	ThicknessKeyFrame();
	ThicknessKeyFrame(const TimeSpan &keyTime, const Thickness &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（Thickness，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const ThicknessKeyFrame &other) const;
};

class NB_API ThicknessAnimationUsingKeyFrames : public ThicknessAnimationBase
{
public:
	std::set<ThicknessKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<ThicknessKeyFrame> m_keyFrames;
};


}