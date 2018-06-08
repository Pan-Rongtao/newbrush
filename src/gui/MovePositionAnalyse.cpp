#include "MovePositionAnalyse.h"
#include "system/System.h"

using namespace nb::Gui;
NB_OBJECT_TYPE_IMPLEMENT(MovePositionAnalyse, nbObject, NULL, NULL);

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

void MovePositionAnalyse::Start(nb::System::Point pos)
{
	m_bStart = true;
	m_bActive = false;
	m_ptOrigin = pos;
	m_ptActive = pos;
}

void MovePositionAnalyse::Move(nb::System::Point pos)
{
	if(!m_bActive)
	{
		//尚未激活偏移，计算是否能激活
		bool xActive = false;
		bool yActive = false;

		if(m_xLock >= 0)
		{
			if(nb::System::Abs(pos.GetX() - m_ptOrigin.GetX()) >= m_xLock)
				xActive = true;
		}
		else
		{
			xActive = true;
		}

		if(m_yLock >= 0)
		{
			if(nb::System::Abs(pos.GetY() - m_ptOrigin.GetY()) >= m_yLock)
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

nb::System::Point MovePositionAnalyse::GetStartPos() const
{
	return m_ptOrigin;
}

nb::System::Point MovePositionAnalyse::GetActivePos() const
{
	return m_ptActive;
}
