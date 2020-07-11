#include "newbrush/media/BooleanAnimation.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Easing.h"

using namespace nb;

BooleanKeyFrame::BooleanKeyFrame()
{
}

BooleanKeyFrame::BooleanKeyFrame(const TimeSpan & keyTime, const bool &value)
{
	setValue(KeyTimeProperty(), keyTime);
	setValue(ValueProperty(), value);
}

DependencyPropertyPtr BooleanKeyFrame::KeyTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<BooleanKeyFrame, TimeSpan>("KeyTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr BooleanKeyFrame::ValueProperty()
{
	static auto dp = DependencyProperty::registerDependency<BooleanKeyFrame, bool>("Value", bool());
	return dp;
}

DependencyPropertyPtr BooleanKeyFrame::EasingFunctionProperty()
{
	static auto dp = DependencyProperty::registerDependency<BooleanKeyFrame, std::shared_ptr<EasingBase>>("EasingFunction", nullptr);
	return dp;
}

bool BooleanKeyFrame::operator < (const BooleanKeyFrame &other) const
{
	auto keyTime = getValue<TimeSpan>(KeyTimeProperty());
	auto keyTimeOther = other.getValue<TimeSpan>(KeyTimeProperty());
	return keyTime < keyTimeOther;
}

std::set<BooleanKeyFrame>& BooleanAnimationUsingKeyFrames::keyFrames()
{
	return m_keyFrames;
}

void BooleanAnimationUsingKeyFrames::onProcessing()
{
	auto target = getValue<std::weak_ptr<DependencyObject>>(TargetProperty());
	auto targetProperty = getValue<DependencyPropertyPtr>(TargetPropertyProperty());
	if (!target.lock() || m_keyFrames.empty())
		return;
	auto progress = getCurrentProgress();
	auto curTicks = (int64_t)(getActualDurationTimespan().totalMilliseconds() * progress);
	for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
	{
		auto k = (*iter).getValue<TimeSpan>(BooleanKeyFrame::KeyTimeProperty()).totalMilliseconds();
		if (curTicks < k)
		{
			//前一个关键帧不为空
			if (--iter != m_keyFrames.end())
				target.lock()->setValue(targetProperty, (iter++)->getValue<bool>(BooleanKeyFrame::ValueProperty()));
			break;
		}
	}
	if (curTicks == m_keyFrames.crbegin()->getValue<TimeSpan>(BooleanKeyFrame::KeyTimeProperty()).totalMilliseconds())
	{
		target.lock()->setValue(targetProperty, m_keyFrames.crbegin()->getValue<bool>(BooleanKeyFrame::ValueProperty()));
	}
}
