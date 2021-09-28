#include "KineticMove.h"
#include <math.h>
using namespace nb;

CKineticMove::CKineticMove()
	: m_fSpeed(0)
	, m_fStartPos(0)
	, m_fCurrPos(0)
	, m_fAccel(0)
	, m_fSpeed_0(0)
{

}

CKineticMove::~CKineticMove()
{

}

void CKineticMove::Start(float fAccel, float fStartSpeed, float fStartPos)
{
	m_fAccel = fAccel;
	m_fSpeed = fStartSpeed;
	m_fStartPos = fStartPos;
	m_fCurrPos = fStartPos;

	m_timeStart = getMilliseconds();

	m_fSpeed_0 = m_fSpeed;

	m_timer.Tick += nbBindEventFunction(CKineticMove::onTick);
	m_timer.start(15);
}

void CKineticMove::OffsetStartPos(float fStartPosOffset)
{
	m_fStartPos += fStartPosOffset;
	m_fCurrPos += fStartPosOffset;
}

void CKineticMove::SetAccel(float fAccel)
{
	m_fAccel = fAccel;
}

void CKineticMove::Stop()
{
	m_timer.stop();
}

float CKineticMove::GetSpeed() const
{
	return m_fSpeed;
}

/******************************************************************************
*
*	功能：	定时器，定时发出移动消息
*
*******************************************************************************/
void CKineticMove::onTick(const EventArgs & e)
{
	auto timeNow = getMilliseconds();

	float dt = 0;
	if(timeNow >= m_timeStart)	//跨天的话，也许会出现 timeNow < m_timeStart的情况
	{
		//dt = (float)m_timeStart.msecsTo(timeNow) / 1000.0;
		dt = float((timeNow - m_timeStart)/1000.0f);
	}

	float speed = m_fSpeed + m_fAccel * dt;

	bool bEnd = false;
	if((m_fSpeed_0>0 && speed<0) || (m_fSpeed_0<0 && speed>0))
	{
		bEnd = true;
		Stop();

		speed = 0;
		dt = -m_fSpeed/m_fAccel;
	}
	float fSpace = m_fSpeed * dt + m_fAccel * dt * dt / 2;

	m_fSpeed = speed;
	m_fCurrPos += fSpace;
	m_timeStart = timeNow;

	int nPos = int(m_fCurrPos);
	if(m_fCurrPos >= 0)
	{
		if(m_fCurrPos - nPos >= 0.5) nPos++;
	}
	else
	{
		if(m_fCurrPos - nPos <= -0.5) nPos--;
	}
	
	MoveDistanceEventArgs MoveDistanceArgs;
	MoveDistanceArgs.sender = this;
	MoveDistanceArgs.m_space = float(nPos);
	MoveDistance.invoke(MoveDistanceArgs);

	if(bEnd)
	{
		MoveEndEventArgs MoveEndArgs;
		MoveEndArgs.sender = this;
		MoveEndArgs.m_space = m_fCurrPos;
		MoveEnd.invoke(MoveEndArgs);
	}
}

/******************************************************************************
*
*	功能：	计算加速度
*
*	参数：	fStartSpeed 开始速度； fSpace 打算运行的距离； fTime 运行时间
*
*******************************************************************************/
float CKineticMove::ComputeAccel(float fStartSpeed, float fSpace, float fTime)
{
	fTime /= 1000;
	return 2 * (fSpace - fStartSpeed * fTime) / (fTime * fTime);
}

/******************************************************************************
*
*	功能：	已知运行距离(s)，初始速度(v)，求加速度(a)
*			（运行距离 s 后，速度为零）
*			（由于末速度为零，依据公式vt = v0 + at，其中vt=0，可知(a)必须要与
*			(v)符号相反，所以，(s)、(v) 不能同为正数，或同为负数）
*
*******************************************************************************/
float CKineticMove::ComputeAccel(float s, float v)
{
	return -v*v/(2*s);
}

/******************************************************************************
*
*	功能：	已知加速度(a)，运行距离(s)，求初始速度(v)
*			（运行距离 s 后，速度为零）
*
*******************************************************************************/
void CKineticMove::ComputeVelocity(float a, float s, float &v)
{
	float f = -2*a*s;
 	v = sqrt(f);
	if(s < 0) v = -v;
}

/******************************************************************************
*
*	功能：	假设要在fTime的时间内运行fSpace的距离（在经过fTime时间后，速度为零），
*			计算起始速度和加速度
*
*******************************************************************************/
void CKineticMove::ComputeStartSpeedAndAccel(float fSpace, float fTime, float &fSpeed, float &fAccel)
{
	fTime /= 1000;

	fAccel = -fSpace * 2 / (fTime * fTime);
	fSpeed = -fAccel * fTime;
}

/******************************************************************************
*
*	功能：	已知初速度(v)，加速度(a)，计算当速度为零时的距离(s)
*			由于最终速度要为零， v、a 不能同为整数 或 同为负数
*
*******************************************************************************/
void CKineticMove::ComputeSpace(float v, float a, float &s)
{
	if(a == 0)		//除零处理
	{
		s = 0;
		return;
	}


	float t = -v / a;	//速度从 v 变为零的时间
	s = v*t + a*t*t/2;
}

/******************************************************************************
 *
 ******************************************************************************/
bool CKineticMove::IsRunning() const
{
	return m_timer.isActive();
}