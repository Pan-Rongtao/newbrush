/******************************************************************************
 *
 *	说明：
 *		线性动画控制类
 *
 *	-------------------------------------------------------------------------
 *
 *	修改：Nanshan Li
 *
 ******************************************************************************/
#pragma once

#include "EasingCurve.h"
#include "newbrush/Animation.h"

namespace nb{

template <class T>
class AnimationCtrlData
{
public:
	void SetAnimationData(const T& DataStart, const T& DataEnd)
	{
		m_dataStart = DataStart;
		m_dataEnd = DataEnd;
	}

	T Interpolate(const float offset) const
	{
		return m_dataStart + (T)((m_dataEnd - m_dataStart) * offset);
	}

private:
	T m_dataStart;
	T m_dataEnd;
};

struct AnimationArgs
{
	float fPercent;
	bool bStop;
};

//class AnimationMgr;
//typedef ref<AnimationMgr> AnimationMgrSharedPtr;
class AnimationMgr
{
public:
	explicit AnimationMgr();
	virtual ~AnimationMgr(void);

	Event<AnimationArgs> Tick;

	bool IsRunning(){ return m_bRunning; };
	void SetEasingType( EasingCurve::EasingType type );
	bool Start(const unsigned int nDuration = 200, const unsigned int nFramerate = 60);
	void Stop();

private:
	void onTimeout(const EventArgs & e);
	void update(unsigned int ms);

private:
	bool m_bRunning;
	unsigned int m_nLastUpdateTimestamp;
	unsigned int m_nElapsed;
	unsigned int m_nDuration;

	Timer m_timerToken;

	EasingCurve m_easing;
};
}
