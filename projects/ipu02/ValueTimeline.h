#pragma once
#include "newbrush/Animation.h"

namespace nb
{
template<class T>
class ValueEventArgsT : public EventArgs
{
public:
	T m_value;
};

template<class T>
class NB_API ValueTimelineT : public Timeline
{
	RTTR_ENABLE(Timeline)
public:
	ValueTimelineT() : m_from(T(0)), m_to(T(0)) {}
	ValueTimelineT(T from, T to) : m_from(from), m_to(to) {}
	virtual ~ValueTimelineT() {}
	void setFrom(T from) { m_from = from; }
	T from() const { return m_from; }
	void setTo(T to) { m_to = to; }
	T to() const { return m_to; }
	void setEasingFunction(ref<EasingBase> easing) { m_easingFunction = easing; }
	ref<EasingBase> easingFunction() const { return m_easingFunction; }

	
	Event<ValueEventArgsT<T>> ValueProcessT;

protected:
	virtual void onProcessing() override
	{
		auto progress = getCurrentProgress();
		if (m_easingFunction)
		{
			progress = (float)m_easingFunction->easeInCore(progress);
		}
		auto value = m_from + (m_to - m_from) * progress;

		ValueEventArgsT<T> e;
		e.sender = this;
		e.m_value = (T)value;
		ValueProcessT.invoke(e);
	}

private:
	T m_from;
	T m_to;
	ref<EasingBase> m_easingFunction;
};

template<> inline void ValueTimelineT<Color>::onProcessing()
{	
	auto progress = getCurrentProgress();
	if (m_easingFunction)
	{
		progress = (float)m_easingFunction->easeInCore(progress);
	}
	int r = (int)((int)m_from.r + progress * ((int)m_to.r - (int)m_from.r));
	int g = (int)((int)m_from.g + progress * ((int)m_to.g - (int)m_from.g));
	int b = (int)((int)m_from.b + progress * ((int)m_to.b - (int)m_from.b));
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	
	ValueEventArgsT<Color> e;
	e.sender = this;
	e.m_value = Color(r, g, b);
	ValueProcessT.invoke(e);
}

using ValueTimelineInt8 = ValueTimelineT<int8_t>;
using ValueTimelineint16 = ValueTimelineT<int16_t>;
using ValueTimelineint32 = ValueTimelineT<int32_t>;
using ValueTimelineint64 = ValueTimelineT<int64_t>;
using ValueTimelinefloat = ValueTimelineT<float>;
using ValueTimelinedouble = ValueTimelineT<double>;
using ValueTimelinePoint = ValueTimelineT<Point>;
using ValueTimelineSize = ValueTimelineT<Size>;
using ValueTimelineColor = ValueTimelineT<Color>;
using ValueTimelineVec2 = ValueTimelineT<glm::vec2>;
using ValueTimelineVec3 = ValueTimelineT<glm::vec3>;
using ValueTimelineVec4 = ValueTimelineT<glm::vec4>;

}