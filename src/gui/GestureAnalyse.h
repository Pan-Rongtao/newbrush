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
	Time m_time;
	Point m_pos;
};

public:
	void GesturePress(Point pos);
	void GestureMove(Point pos);
	void GestureRelease(Point pos);
	float GetHorizontalSpeed() const;
	float GetVerticalSpeed() const;
private:
	void onTick(const Timer::TickArgs &args);

	void AddPos(Point pos);
	inline void ClearNodeQueue();
private:
	std::queue<Node *> m_queueNode;
	bool m_bPress;
	bool m_bOffsetActive;
	Point m_ptPress;
	Point m_ptOffset;
	Point m_ptPrev;
	Time m_timePrev;
	Point m_ptLast;
	Time m_timeLast;
	float m_fSpeed;
	Timer m_timer;
};

}}
