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
#include "AnimationMgr.h"

#include "newbrush/Core.h"

inline unsigned int kzsClampui(unsigned int value, unsigned int minimum, unsigned int maximum)
{
	return (value <= minimum) ? minimum : ((value >= maximum) ? maximum : value);
}

using namespace nb;

AnimationMgr::AnimationMgr()
 : m_nLastUpdateTimestamp(0)
 , m_nElapsed(0)
 , m_nDuration(0)
 , m_bRunning(false)
 , m_easing(EasingCurve(EasingCurve::EasingType(EasingCurve::Linear), 1.1f, 1.70158f, 0.3f))
{
	m_timerToken.Tick += nbBindEventFunction(AnimationMgr::onTimeout);
}

AnimationMgr::~AnimationMgr(void)
{
	m_nElapsed = 0;
	m_nDuration = 0;
	m_bRunning = false;
	m_nLastUpdateTimestamp = 0;
}

void AnimationMgr::onTimeout(const EventArgs & e)
{
	unsigned int currentTime = getMilliseconds();
	unsigned int timeStep = currentTime - m_nLastUpdateTimestamp;
	m_nLastUpdateTimestamp = currentTime;
	update(timeStep);
}

void AnimationMgr::update(unsigned int ms)
{
	m_nElapsed = kzsClampui(m_nElapsed + ms, 0, m_nDuration);
	float percent = (float) m_nElapsed / (float) m_nDuration;

	bool bStop = false;
	float fPercent = m_easing.valueForProgress(percent);
	
	if (m_nElapsed >= m_nDuration) {
		m_bRunning = false;
		bStop = true;
		m_timerToken.stop();
	} else {
		bStop = false;
	}
	
	AnimationArgs e;
	e.fPercent = fPercent;
	e.bStop = bStop;
	Tick.invoke({ e });
}

void AnimationMgr::SetEasingType(EasingCurve::EasingType easingType)
{
	m_easing.setType(easingType);
}

bool AnimationMgr::Start(const unsigned int nDuration, const unsigned int nFramerate)
{
	if( m_bRunning ) return false;

	m_nDuration = nDuration;
	m_nElapsed = 0;
	m_bRunning = true;
	m_nLastUpdateTimestamp = getMilliseconds();
	m_timerToken.start(1000/nFramerate);
	return true;
}

void AnimationMgr::Stop()
{
	m_timerToken.stop();
	m_nElapsed = 0;
	m_nDuration = 0;
	m_bRunning = false;
	m_nLastUpdateTimestamp = 0;

	float fPercent = m_easing.valueForProgress(1.0f);
	bool bStop = true;

	AnimationArgs e;
	e.fPercent = fPercent;
	e.bStop = bStop;
	Tick.invoke({ e });
}