#include "MovePositionAnalyse.h"
#include <math.h>

namespace nb
{

CMovePositionAnalyse::CMovePositionAnalyse(int xLock, int yLock)
	: m_xLock(xLock)
	, m_yLock(yLock)
	, m_bActive(false)
	, m_bStart(false)
{
}

CMovePositionAnalyse::~CMovePositionAnalyse(void)
{
}

void CMovePositionAnalyse::Start(Point pos)
{
	m_bStart = true;
	m_bActive = false;
	m_ptOrigin = pos;
	m_ptActive = pos;
}

void CMovePositionAnalyse::Move(Point pos)
{
	if(!m_bActive)
	{
		//尚未激活偏移，计算是否能激活
		bool xActive = false;
		bool yActive = false;

		if(m_xLock >= 0)
		{
			if(fabs(pos.x - m_ptOrigin.x) >= m_xLock)
				xActive = true;
		}
		else
		{
			xActive = true;
		}

		if(m_yLock >= 0)
		{
			if(fabs(pos.y - m_ptOrigin.y) >= m_yLock)
				yActive = true;
		}
		else
		{
			yActive = true;
		}


		if(xActive || yActive)
		{
			//激活条件已满足
			m_bActive = true;
			m_ptActive = pos;
		}
		else
		{
			pos = m_ptOrigin;
		}
	}
	else
	{
	}
}

bool CMovePositionAnalyse::IsActive() const
{
	return m_bActive;
}

Point CMovePositionAnalyse::GetStartPos() const
{
	return m_ptOrigin;
}

Point CMovePositionAnalyse::GetActivePos() const
{
	return m_ptActive;
}

void CMovePositionAnalyse::Cancel()
{
	m_bStart = false;
	m_bActive = false;
}

void CMovePositionAnalyse::SetLock(int xLock, int yLock)
{
	m_xLock = xLock;
	m_yLock = yLock;
}

} // end namespace