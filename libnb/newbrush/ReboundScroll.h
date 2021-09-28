#pragma once
#include "Object.h"
#include "newbrush/UserControl.h"
#include "KineticMove.h"

namespace nb
{

class SignalScrollEventArgs : public EventArgs
{
public:
	float m_space;
};

class SignalScrollEndEventArgs : public EventArgs
{
};

class CKineticMove;
class CReboundScroll : public Object
{
/*
Q_SIGNALS:
    void SignalScroll(int nSpace);
	void SignalScrollEnd();*/

public:
	CReboundScroll();
	~CReboundScroll();
	void UseRebound(bool bUse);

	// 启动运动
	void Start(float fAccel, float fStartSpeed, float fStartPos, float fPageHeight, float fContentHeight);

	// 停止运动
	void Stop();

	// 是否正在运行
	bool IsRunning() const;

	// 偏移运动的开始位置
	void OffsetStartPos(float fStartPosOffset);

	float m_fTopLeftReboundPos;			//顶部（左侧）回滚点，当向下（向右）滚动时，超过回滚点，将向上（向左）弹回
	float m_fBottomRightReboundPos;		//底部（右侧）回滚点，当向上（向左）滚动时，超过会滚点，将向下（向右）弹回
	float m_fReboundStopLength;			//距回滚点的距离，为阻止点，当运动到该点时，将会遇到无限大的阻力。负数表明该数据无效

	float m_fReboundAccel;

	Event<SignalScrollEventArgs> SignalScroll;
	Event<SignalScrollEndEventArgs> SignalScrollEnd;

private:
	ref<CKineticMove> m_pKineticMove;
	inline void ScrollEndEvent();

private:
	void OnKineticScroll(const MoveDistanceEventArgs & e);
	void OnKineticScrollEnd(const MoveEndEventArgs & e);

private:
	bool m_bUseRebound;
	bool m_bElastic;
	float m_fElasticSpace;
	bool m_bElasticDec;

	float m_fContentHeight;
	float m_fPageHeight;

	bool m_bScrollDown;
	bool m_bIsRuning;
};
};