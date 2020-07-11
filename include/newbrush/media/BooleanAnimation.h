#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API BooleanAnimationBase : public AnimationTimeline
{
public:
	

protected:
	BooleanAnimationBase() = default;
};

class NB_API BooleanKeyFrame : public DependencyObject
{
public:
	BooleanKeyFrame();
	BooleanKeyFrame(const TimeSpan &keyTime, const bool &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（bool，默认值false）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const BooleanKeyFrame &other) const;
};

class NB_API BooleanAnimationUsingKeyFrames : public BooleanAnimationBase
{
public:
	std::set<BooleanKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<BooleanKeyFrame> m_keyFrames;
};


}