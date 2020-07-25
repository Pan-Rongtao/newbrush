#include "newbrush/core/media/animation/StringAnimation.h"

using namespace nb;

StringKeyFrame::StringKeyFrame()
{
}

StringKeyFrame::StringKeyFrame(const TimeSpan & keyTime, const std::string &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr StringKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<StringKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr StringKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<StringKeyFrame, std::string>("Value", std::string());
	return dp;
}

DependencyPropertyPtr StringKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<StringKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool StringKeyFrame::operator < (const StringKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<StringKeyFrame>& StringAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void StringAnimationUsingKeyFrames::onProcessing()
{
	auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
	auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
	if (!target.lock() || m_keyFrames.empty())
		return;

	auto progress = getCurrentProgress();
	auto curTicks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
	for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
	{
		auto k = (*iter).getValue<TimeSpan>(StringKeyFrame::KeyTimeProperty()).totalMilliseconds();
		if (curTicks < k)
		{
			//前一个关键帧不为空
			if (--iter != m_keyFrames.end())
				target.lock()->setValue(targetProperty, (iter++)->getValue<std::string>(StringKeyFrame::ValueProperty()));
			break;
		}
	}
	if (curTicks == m_keyFrames.crbegin()->getValue<TimeSpan>(StringKeyFrame::KeyTimeProperty()).totalMilliseconds())
	{
		target.lock()->setValue(targetProperty, m_keyFrames.crbegin()->getValue<std::string>(StringKeyFrame::ValueProperty()));
	}
}
