#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API DoubleAnimationBase : public AnimationTimeline
{
public:
	

protected:
	DoubleAnimationBase() = default;
};

class NB_API DoubleAnimation : public DoubleAnimationBase
{
public:
	DoubleAnimation();
	DoubleAnimation(double toValue, const Duration &duration);
	DoubleAnimation(double toValue, const Duration &duration, FillBehaviorE fillBehavior);
	DoubleAnimation(double fromValue, double toValue, const Duration &duration);
	DoubleAnimation(double fromValue, double toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<double>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<double>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<double>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	double m_actualFrom;
	double m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API DoubleKeyFrame : public DependencyObject
{
public:
	DoubleKeyFrame();
	DoubleKeyFrame(const TimeSpan &keyTime, double value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（double，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const DoubleKeyFrame &other) const;
};

class NB_API DoubleAnimationUsingKeyFrames : public DoubleAnimationBase
{
public:
	std::set<DoubleKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<DoubleKeyFrame> m_keyFrames;
};


}