#include "KineticMove.h"
#include <math.h>

using namespace nb::core;
using namespace nb::gui;

KineticMove::KineticMove()
	: InitSpeed(0.0)
	, Speed(0.0)
	, Accel(0.0)
	, StartPos(0.0)
	, CurrentPos(0.0)
	, TimeStart(Time::now())
{
	m_timer.TickEvent.addHandler(std::bind(&KineticMove::onTick, this, std::placeholders::_1));
}

KineticMove::~KineticMove()
{
}

void KineticMove::onTick(const Timer::TickArgs &args)
{
	Time timeNow = Time::now();

	double dt = 0.0;
	if(timeNow >= TimeStart)	//跨天的话，也许会出现 timeNow < TimeStart()的情况
	{
		dt = (timeNow - TimeStart).totalMilliseconds() / 1000.0;
	}

    double speed = Speed + Accel * dt;

	bool bEnd = false;
	if((InitSpeed > 0 && speed < 0) || (InitSpeed < 0 && speed > 0))
	{
		bEnd = true;
		Stop();

		speed = 0;
		dt = -Speed / Accel;
	}
    double fSpace = Speed * dt + Accel * dt * dt / 2;

	Speed = speed;
	CurrentPos = CurrentPos + fSpace;
	TimeStart = timeNow;

	int nPos = (int)CurrentPos;
	if(CurrentPos >= 0)
	{
		if(CurrentPos - nPos >= 0.5) nPos++;
	}
	else
	{
		if(CurrentPos - nPos <= -0.5) nPos--;
	}
	
	MoveDistanceArgs pmd;
	pmd.m_nSpace = nPos;
	MoveDistanceEvent.dispatch(pmd);

	if(bEnd)
	{
		MoveEndArgs pme;
		pme.m_fSpace = CurrentPos;
		MoveEndEvent.dispatch(pme);
	}
}

void KineticMove::Start(float fAccel, float fStartSpeed, float fStartPos)
{
	Accel = fAccel;
	Speed = fStartSpeed;
	StartPos = fStartPos;
	CurrentPos = fStartPos;
	m_timer.start(15);

	TimeStart = Time::now();

	InitSpeed = fStartSpeed;

}

void KineticMove::OffsetStartPos(float fStartPosOffset)
{
	StartPos = StartPos + fStartPosOffset;
	CurrentPos = CurrentPos + fStartPosOffset;
}

void KineticMove::SetAccel(float fAccel)
{
	Accel = fAccel;
}

void KineticMove::Stop()
{
	m_timer.stop();
}

float KineticMove::GetSpeed() /*const*/
{
	//return (Float)const_cast<KineticMove *>(this)->Speed();
	return (float)Speed;
}

/******************************************************************************
*
*	功能：	计算加速度
*
*	参数：	fStartSpeed 开始速度； fSpace 打算运行的距离； fTime 运行时间
*
*******************************************************************************/
float KineticMove::ComputeAccel(float fStartSpeed, float fSpace, float fTime)
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
float KineticMove::ComputeAccel(float s, float v)
{
	return -v*v/(2*s);
}

/******************************************************************************
*
*	功能：	已知加速度(a)，运行距离(s)，求初始速度(v)
*			（运行距离 s 后，速度为零）
*
*******************************************************************************/
void KineticMove::ComputeVelocity(float a, float s, float &v)
{
	float f = -2*a*s;
	v = (float)sqrt(f);
	if(s < 0) v = -v;
}

/******************************************************************************
*
*	功能：	假设要在fTime的时间内运行fSpace的距离（在经过fTime时间后，速度为零），
*			计算起始速度和加速度
*
*******************************************************************************/
void KineticMove::ComputeStartSpeedAndAccel(float fSpace, float fTime, float &fSpeed, float &fAccel)
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
void KineticMove::ComputeSpace(float v, float a, float &s)
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
bool KineticMove::IsRunning() const
{
	return m_timer.isActive();
}
