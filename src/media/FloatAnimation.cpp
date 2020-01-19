#include "media/FloatAnimation.h"
#include "core/DependencyObject.h"

using namespace nb;

FloatAnimation::FloatAnimation()
	: FloatAnimation(NAN, NAN)
{
}

FloatAnimation::FloatAnimation(float to)
	: FloatAnimation(NAN, to)
{
}

FloatAnimation::FloatAnimation(float from, float to)
	: m_from(from)
	, m_to(to)
	, m_easingFunction(nullptr)
	, m_actualFrom(NAN)
	, m_actualTo(NAN)
{
}

void FloatAnimation::setFrom(float from) &
{
	m_from = from;
}

float FloatAnimation::from() const
{
	return m_from;
}

void FloatAnimation::setTo(float to) &
{
	m_to = to;
}

float FloatAnimation::to() const
{
	return m_to;
}

void FloatAnimation::setEasingFunction(std::shared_ptr<EasingBase> easing)
{
	m_easingFunction = easing;
}

std::shared_ptr<EasingBase> FloatAnimation::easingFunction() const
{
	return m_easingFunction;
}

void FloatAnimation::onStateChanged()
{
	AnimationTimeline::onStateChanged();
	if (currentState() == Timeline::StateE::Active)
	{
		m_actualFrom = std::isnan(m_from) ? target().lock()->get(targetProperty()) : m_from;
		m_actualTo = std::isnan(m_to) ? m_actualFrom : m_to;
		if (std::isnan(m_actualFrom))	nbThrowException(std::runtime_error, "can't calculated from value for animation.");
		if (std::isnan(m_actualTo))		nbThrowException(std::runtime_error, "can't calculated to value for animation.");
	}
}

void FloatAnimation::onProcessing()
{
	if (!target().lock() || targetProperty().isInvalid())
		return;

	AnimationTimeline::onProcessing();
	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto easingProgress = easing->easeInCore(progress);
	auto value = m_actualFrom + (m_actualTo - m_actualFrom) * easingProgress;
	target().lock()->set(targetProperty(), value);
}

FloatKeyFrame::FloatKeyFrame(const TimeSpan & keyTime, float value)
{
	setKeyTime(keyTime);
}

void FloatKeyFrame::setKeyTime(const TimeSpan &keyTime) &
{
	if (keyTime < TimeSpan::zero())
		nbThrowException(std::underflow_error, "keyTime is negative");
	m_keyTime = keyTime;
}

const TimeSpan & FloatKeyFrame::keyTime() const
{
	return m_keyTime;
}

void FloatKeyFrame::setValue(float value) &
{
	m_value = value;
}

float FloatKeyFrame::value() const
{
	return m_value;
}

void FloatKeyFrame::setEasing(std::shared_ptr<EasingBase> easing) &
{
	m_easing = easing;
}

std::shared_ptr<EasingBase> FloatKeyFrame::easing() const
{
	return m_easing;
}

FloatAnimationUsingKeyFrames::FloatAnimationUsingKeyFrames()
{
}

FloatAnimationUsingKeyFrames::FloatAnimationUsingKeyFrames(const std::set<FloatKeyFrame>& keyFrames)
	: m_keyFrames(keyFrames)
{
}

void FloatAnimationUsingKeyFrames::setKeyFrames(const std::set<FloatKeyFrame>& keyFrames) &
{
	m_keyFrames = keyFrames;
}

const std::set<FloatKeyFrame> FloatAnimationUsingKeyFrames::keyFrames() const
{
	return m_keyFrames;
}

void FloatAnimationUsingKeyFrames::onProcessing()
{
	if (!target().lock() || m_keyFrames.empty())
		return;

	//根据ticks获取当前frame，找不到表示超出了范围
	auto getCurrentFrame = [&](int64_t ticks)->std::set<FloatKeyFrame>::iterator
	{
		for (auto iter = m_keyFrames.begin(); iter != m_keyFrames.end(); ++iter)
		{
			auto k = (*iter).keyTime().totalMilliseconds();
			if (ticks <= k)
				return iter;
		}
		return m_keyFrames.end();
	};

	auto progress = getCurrentProgress();
	int64_t ticks = (int64_t)(duration().totalMilliseconds() * progress);
	auto curFrameIter = getCurrentFrame(ticks);
	if (curFrameIter != m_keyFrames.end())
	{
		auto curFrame = *curFrameIter;
		auto prevFrameIter = (curFrameIter == m_keyFrames.begin()) ? m_keyFrames.end() : --curFrameIter;
		float fromValue = (prevFrameIter == m_keyFrames.end()) ? curFrame.value() : (*prevFrameIter).value();
		float toValue = curFrame.value();
		auto curFrameEasing = curFrame.easing() ? curFrame.easing() : std::make_shared<LinearEase>();
		auto easingProgress = curFrameEasing->easeInCore(progress);
		auto value = fromValue + (toValue - fromValue) * easingProgress;
		target().lock()->set(targetProperty(), value);
	}
}
