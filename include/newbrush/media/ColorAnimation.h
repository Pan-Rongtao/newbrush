#pragma once
#include "newbrush/media/AnimationTimeline.h"
#include "newbrush/media/Color.h"

namespace nb {
	
class NB_API ColorAnimationBase : public AnimationTimeline
{
public:
	

protected:
	ColorAnimationBase() = default;
};

class NB_API ColorAnimation : public ColorAnimationBase
{
public:
	ColorAnimation();
	ColorAnimation(const Color &toValue, const Duration &duration);
	ColorAnimation(const Color &toValue, const Duration &duration, FillBehaviorE fillBehavior);
	ColorAnimation(const Color &fromValue, const Color &toValue, const Duration &duration);
	ColorAnimation(const Color &fromValue, const Color &toValue, const Duration &duration, FillBehaviorE fillBehavior);

	static DependencyPropertyPtr FromProperty();			//起始值（optional<Color>，默认值nullopt）
	static DependencyPropertyPtr ToProperty();				//终点值（optional<Color>，默认值nullopt）
	static DependencyPropertyPtr ByProperty();				//步进值（optional<Color>，默认值nullopt）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

protected:
	virtual void onProcessing() override;

private:
	static void onPropertyChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	void validateFromTo();

	Color m_actualFrom;
	Color m_actualTo;
	bool m_needToValidationFromTo{ false };
};

class NB_API ColorKeyFrame : public DependencyObject
{
public:
	ColorKeyFrame();
	ColorKeyFrame(const TimeSpan &keyTime, const Color &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（Color，默认值0）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const ColorKeyFrame &other) const;
};

class NB_API ColorAnimationUsingKeyFrames : public ColorAnimationBase
{
public:
	std::set<ColorKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<ColorKeyFrame> m_keyFrames;
};


}