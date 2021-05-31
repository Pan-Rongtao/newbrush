#pragma once
#include "../Common.h"

using namespace nb;

class NormalNode : public Node2D
{
public:
	NormalNode();

	void setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle);


private:
	void onTick(const EventArgs & e);

	void moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle);
	void moveEffectNumberCircle(ref<Node2D> node, float angle);


	ref<Node2D> m_dots0;
	ref<Node2D> m_dots1;
	ref<Node2D> m_secondPointer;
	ref<Node2D> m_hourParent;
	ref<Node2D> m_minuteParent;
	ref<Node2D> m_hourShadowParent;
	ref<Node2D> m_minuteShadowParent;
	ref<Node2D> m_hourShadow;
	ref<Node2D> m_minuteShadow;

	Timer m_timer;
	FloatAnimation m_secondPointerAnimation;
};