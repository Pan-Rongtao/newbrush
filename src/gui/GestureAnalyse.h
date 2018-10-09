#pragma once
#include "core/Event.h"
#include "core/Timer.h"
#include "core/DateTime.h"
#include "core/Point.h"
#include <queue>

namespace nb{ namespace gui {

class GestureAnalyse
{
public:
	GestureAnalyse();
	virtual ~GestureAnalyse();

struct Node
{
	nb::core::Time m_time;
	nb::core::Point m_pos;
};

public:
	void GesturePress(nb::core::Point pos);
	void GestureMove(nb::core::Point pos);
	void GestureRelease(nb::core::Point pos);
	float GetHorizontalSpeed() const;
	float GetVerticalSpeed() const;
private:
	void onTick(const nb::core::Timer::TickArgs &args);

	void AddPos(nb::core::Point pos);
	inline void ClearNodeQueue();
private:
	std::queue<Node *> m_queueNode;
	bool m_bPress;
	bool m_bOffsetActive;
	nb::core::Point m_ptPress;
	nb::core::Point m_ptOffset;
	nb::core::Point m_ptPrev;
	nb::core::Time m_timePrev;
	nb::core::Point m_ptLast;
	nb::core::Time m_timeLast;
	float m_fSpeed;
	nb::core::Timer m_timer;
};

}}
