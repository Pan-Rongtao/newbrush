#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API PointAnimationBase : public AnimationTimeline
{
public:
	

protected:
	PointAnimationBase() = default;
};

class NB_API PointAnimation : public PointAnimationBase
{
public:
	PointAnimation();
	PointAnimation(const Point &toValue, const Duration &duration);
	PointAnimation(const Point &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	PointAnimation(const Point &fromValue, const Point &toValue, const Duration &duration);
	PointAnimation(const Point &fromValue, const Point &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<Point>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<Point>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<Point>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Point m_actualFrom;
	Point m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API PointKeyFrame : public DependencyObject
{
public:
	PointKeyFrame();
	PointKeyFrame(const TimeSpan &keyTime, const Point &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（Point，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const PointKeyFrame &other) const;
};

class NB_API PointAnimationUsingKeyFrames : public PointAnimationBase
{
public:
	std::set<PointKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<PointKeyFrame> m_keyFrames;
};


}