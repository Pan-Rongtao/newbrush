#pragma once
#include "../Common.h"

using namespace nb;

class ECONode : public Node2D
{
public:
	ECONode();

private:
	void onTick(const EventArgs & e);

	void setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle);

	void moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle);
	void moveEffectNumberCircle(ref<Node2D> node, float angle);

	void makeDots(float startAngle, float angleRange, float r);
	void setDotsAngle(float angle, float angleRange, float r);

	ref<Node2D> m_pionter;
	ref<Node2D> m_hourParent;
	ref<Node2D> m_minuteParent;
	ref<Node2D> m_hourShadowParent;
	ref<Node2D> m_minuteShadowParent;
	ref<Node2D> m_hourShadow;
	ref<Node2D> m_minuteShadow;
	ref<Node2D> m_dotPanel;
#define LineCount 16
	ref<Node2D> m_dots[(LineCount + 1) * (LineCount) / 2];

	std::vector<ref<Vec2Animation>> m_scaleAnimations;
	Timer m_timer;
};