#include "MovePositionAnalyse.h"
#include <cmath>

using namespace nb::core;
using namespace nb::gui;

MovePositionAnalyse::MovePositionAnalyse()
: m_xLock(-1)
, m_yLock(15)
{
}

MovePositionAnalyse::MovePositionAnalyse(float xLock, float yLock)
: m_xLock(xLock)
, m_yLock(yLock)
, m_bActive(false)
, m_bStart(false)
{
}

MovePositionAnalyse::~MovePositionAnalyse()
{
}

void MovePositionAnalyse::SetLock(float xLock, float yLock)
{
	m_xLock = xLock;
	m_yLock = yLock;
}

void MovePositionAnalyse::Start(Point pos)
{
	m_bStart = true;
	m_bActive = false;
	m_ptOrigin = pos;
	m_ptActive = pos;
}

void MovePositionAnalyse::Move(Point pos)
{
	if(!m_bActive)
	{
		//尚未激活偏移，计算是否能激活
		bool xActive = false;
		bool yActive = false;

		if(m_xLock >= 0)
		{
			if(abs(pos.x() - m_ptOrigin.x()) >= m_xLock)
				xActive = true;
		}
		else
		{
			xActive = true;
		}

		if(m_yLock >= 0)
		{
			if(abs(pos.y() - m_ptOrigin.y()) >= m_yLock)
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

void MovePositionAnalyse::Cancel()
{
	m_bStart = false;
	m_bActive = false;
}

bool MovePositionAnalyse::IsActive() const
{
	return m_bActive;
}

Point MovePositionAnalyse::GetStartPos() const
{
	return m_ptOrigin;
}

Point MovePositionAnalyse::GetActivePos() const
{
	return m_ptActive;
}
