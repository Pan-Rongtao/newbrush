#pragma once
#include "newbrush/media/AnimationTimeline.h"

namespace nb {
	
class NB_API StringAnimationBase : public AnimationTimeline
{
public:
	

protected:
	StringAnimationBase() = default;
};

class NB_API StringKeyFrame : public DependencyObject
{
public:
	StringKeyFrame();
	StringKeyFrame(const TimeSpan &keyTime, const std::string &value);

	static DependencyPropertyPtr KeyTimeProperty();	//起始值（TimeSpan，默认值TimeSpan(0)）
	static DependencyPropertyPtr ValueProperty();	//终点值（std::string，默认值""）
	static DependencyPropertyPtr EasingFunctionProperty();	//起始值（std::shared_ptr<EasingBase>，默认值nullptr）

	bool operator < (const StringKeyFrame &other) const;
};

class NB_API StringAnimationUsingKeyFrames : public StringAnimationBase
{
public:
	std::set<StringKeyFrame> &keyFrames();

protected:
	virtual void onProcessing() override;

private:
	std::set<StringKeyFrame> m_keyFrames;
};


}