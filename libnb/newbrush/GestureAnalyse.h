#pragma once
#include "Object.h"
#include "newbrush/UserControl.h"
#include <queue>

namespace nb
{
class CGestureAnalyse : public Object
{
public:
	CGestureAnalyse();
	~CGestureAnalyse();

	// 鼠标压下
	void GesturePress(Point pos);

	// 鼠标移动
	void GestureMove(Point pos);

	// 鼠标释放
	void GestureRelease(Point pos);

	// 获取垂直方向的鼠标运动速度
	float GetVerticalSpeed() const;

	// 获取水平方向的鼠标运动速度
	float GetHorizontalSpeed() const;

	// 获取压下的位置点
	Point GetPressPos() const;

//	void SetOffsetActiveSpace(float x, float y);

private:
	struct Node
	{
		uint64_t m_time;
		Point m_pos;
	};

	void AddPos(Point pos);
	inline void ClearNodeQueue();

	uint64_t m_timePrev;
	Point m_ptPrev;
	uint64_t m_timeLast;
	Point m_ptLast;
	float m_fSpeed;	
	Timer m_timer;

	bool m_bPress;

	Point m_ptPress;
	Point m_ptOffset;			//偏移激活的原点
	bool m_bOffsetActive;

	std::queue<ref<Node>> m_queueNode;		//记录节点

private:
	void onTick(const EventArgs & e);
};
}