#include "AnimationTimeline.h"
#include "core/DependencyObject.h"
#include "core/Rect.h"
#include "core/Color.h"
#include "media/Thickness.h"

namespace nb{

template<class T>
class NB_API PropertyAnimation : public AnimationTimeline
{
public:
	PropertyAnimation() : m_from(T()), m_to(T()), m_hasSetFrom(false), m_hasSetTo(false) { }
	PropertyAnimation(T to) : m_from(T()), m_to(to), m_hasSetFrom(false), m_hasSetTo(true) { }
	PropertyAnimation(T from, T to) : m_from(from) , m_to(to), m_hasSetFrom(true), m_hasSetTo(true) { }

	void setFrom(T from) & { m_from = from; m_hasSetFrom = true; }
	T from() const { return m_from; }

	void setTo(T to) & { m_to = to; m_hasSetTo = true; }
	T to() const { return m_to; }

	void setEasingFunction(std::shared_ptr<EasingBase> easing) & { m_easingFunction = easing; }
	std::shared_ptr<EasingBase> easingFunction() const { return m_easingFunction; }

protected:
	virtual void onStateChanged() override
	{
		AnimationTimeline::onStateChanged();
		if (currentState() == Timeline::StateE::Active)
		{
			try {
				m_actualFrom = m_hasSetFrom ? m_from : target().lock()->get<T>(targetProperty());
			}
			catch (...) {
				nbThrowException(std::logic_error, "unmatch property animation type[%s] for property type[%s]", typeid(T).name(), targetProperty().propertyType().name());
			}
			m_actualTo = m_hasSetTo ? m_to : m_actualFrom;
		}
	}
	virtual void onProcessing() override
	{
		AnimationTimeline::onProcessing();
		if (!target().lock() || targetProperty().isInvalid())
			return;

		auto progress = getCurrentProgress();
		auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
		auto ft = easing->easeInCore(progress);
		auto value = m_actualFrom + (m_actualTo - m_actualFrom) * ft;
		target().lock()->set(targetProperty(), value);
	}

private:
	T						m_from;
	T						m_to;
	T						m_actualFrom;
	T						m_actualTo;
	bool					m_hasSetFrom;
	bool					m_hasSetTo;
	std::shared_ptr<EasingBase>	m_easingFunction;
};

template<>
void PropertyAnimation<float>::onStateChanged()
{
	AnimationTimeline::onStateChanged();
	if (currentState() == Timeline::StateE::Active)
	{
		m_actualFrom = m_hasSetFrom ? m_from : target().lock()->get<float>(targetProperty());
		m_actualTo = m_hasSetTo ? m_to : m_actualFrom;
		if (std::isnan(m_actualFrom))	nbThrowException(std::runtime_error, "can't calculated 'from value' for animation.");
		if (std::isnan(m_actualTo))		nbThrowException(std::runtime_error, "can't calculated 'to value' for animation.");
	}
}
template<>
void PropertyAnimation<double>::onStateChanged()
{
	AnimationTimeline::onStateChanged();
	if (currentState() == Timeline::StateE::Active)
	{
		m_actualFrom = m_hasSetFrom ? m_from : target().lock()->get<double>(targetProperty());
		m_actualTo = m_hasSetTo ? m_to : m_actualFrom;
		if (std::isnan(m_actualFrom))	nbThrowException(std::runtime_error, "can't calculated 'from value' for animation.");
		if (std::isnan(m_actualTo))		nbThrowException(std::runtime_error, "can't calculated 'to value' for animation.");
	}
}
template<>
void PropertyAnimation<Point>::onProcessing()
{
	AnimationTimeline::onProcessing();
	if (!target().lock() || targetProperty().isInvalid())
		return;

	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto ft = easing->easeInCore(progress);
	//	int r = (int)((int)m_from.red() + ft * ((int)m_to.red() - (int)m_from.red()));
	//	int g = (int)((int)m_from.green() + ft * ((int)m_to.green() - (int)m_from.green()));
	//	int b = (int)((int)m_from.blue() + ft * ((int)m_to.blue() - (int)m_from.blue()));
	target().lock()->set(targetProperty(), Point());
}
template<> void PropertyAnimation<Size>::onProcessing()
{
	AnimationTimeline::onProcessing();
	if (!target().lock() || targetProperty().isInvalid())
		return;

	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto ft = easing->easeInCore(progress);
	//	int r = (int)((int)m_from.red() + ft * ((int)m_to.red() - (int)m_from.red()));
	//	int g = (int)((int)m_from.green() + ft * ((int)m_to.green() - (int)m_from.green()));
	//	int b = (int)((int)m_from.blue() + ft * ((int)m_to.blue() - (int)m_from.blue()));
	target().lock()->set(targetProperty(), Size());
}

template<>void PropertyAnimation<Rect>::onProcessing()
{
	AnimationTimeline::onProcessing();
	if (!target().lock() || targetProperty().isInvalid())
		return;

	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto ft = easing->easeInCore(progress);
	//	int r = (int)((int)m_from.red() + ft * ((int)m_to.red() - (int)m_from.red()));
	//	int g = (int)((int)m_from.green() + ft * ((int)m_to.green() - (int)m_from.green()));
	//	int b = (int)((int)m_from.blue() + ft * ((int)m_to.blue() - (int)m_from.blue()));
	target().lock()->set(targetProperty(), Rect());
}

template<> void PropertyAnimation<Color>::onProcessing()
{
	AnimationTimeline::onProcessing();
	if (!target().lock() || targetProperty().isInvalid())
		return;

	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto ft = easing->easeInCore(progress);
	int r = (int)((int)m_from.red() + ft * ((int)m_to.red() - (int)m_from.red()));
	int g = (int)((int)m_from.green() + ft * ((int)m_to.green() - (int)m_from.green()));
	int b = (int)((int)m_from.blue() + ft * ((int)m_to.blue() - (int)m_from.blue()));
	target().lock()->set(targetProperty(), Color(r, g, b));
}

template<> void PropertyAnimation<Thickness>::onProcessing()
{
	AnimationTimeline::onProcessing();
	if (!target().lock() || targetProperty().isInvalid())
		return;

	auto progress = getCurrentProgress();
	auto easing = m_easingFunction ? m_easingFunction : std::make_shared<LinearEase>();
	auto ft = easing->easeInCore(progress);
	//	int r = (int)((int)m_from.red() + ft * ((int)m_to.red() - (int)m_from.red()));
	//	int g = (int)((int)m_from.green() + ft * ((int)m_to.green() - (int)m_from.green()));
	//	int b = (int)((int)m_from.blue() + ft * ((int)m_to.blue() - (int)m_from.blue()));
	target().lock()->set(targetProperty(), Thickness());
}

using Int8Animation = PropertyAnimation<int8_t>;
using Int16Animation = PropertyAnimation<int16_t>;
using Int32Animation = PropertyAnimation<int32_t>;
using Int64Animation = PropertyAnimation<int64_t>;
using FloatAnimation = PropertyAnimation<float>;
using DoubleAnimation = PropertyAnimation<double>;
using PointAnimation = PropertyAnimation<Point>;
using SizeAnimation = PropertyAnimation<Size>;
using RectAnimation = PropertyAnimation<Rect>;
using ThicknessAnimation = PropertyAnimation<Thickness>;
using ColorAnimation = PropertyAnimation<Color>;

}