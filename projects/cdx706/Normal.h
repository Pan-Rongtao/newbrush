#pragma once
#include "../Common.h"

using namespace nb;

class NormalNode : public Node2D
{
public:
	NormalNode();

	void setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle);

	void updateDots(const glm::vec2 &center, float r, float centerAngle, float angleRange);

private:
	void onTick(const EventArgs & e);

	void moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle);
	void moveEffectNumberCircle(ref<Node2D> node, float angle);

	void setSecondPointerForTime(float r, float angle);

	ref<Node2D> m_secondPointer;
	ref<Node2D> m_hourParent;
	ref<Node2D> m_minuteParent;
	ref<Node2D> m_hourShadowParent;
	ref<Node2D> m_minuteShadowParent;
	ref<Node2D> m_hourShadow;
	ref<Node2D> m_minuteShadow;
	ref<Node2D> m_dotPanel;

	Timer m_timer;
	FloatAnimation m_secondPointerAnimation;
};