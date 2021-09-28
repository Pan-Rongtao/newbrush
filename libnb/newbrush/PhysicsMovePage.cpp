#include "newbrush/PhysicsMovePage.h"

using namespace nb;

PhysicsMovePage::PhysicsMovePage()
	:PhysicsMovePage(0,0,NAN,NAN)
{
	init();
}

PhysicsMovePage::PhysicsMovePage(const Rect &rc)
	: PhysicsMovePage(rc.x(), rc.y(), rc.width(), rc.height())
{
	init();
}

PhysicsMovePage::PhysicsMovePage(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
	, m_itemcount(0)
	, m_itemOrientation(OrientationE::Horizontal)
	, m_bIsRunning(false)
	, m_bIsPress(false)
	, m_MouseLastMovePos(Point(0.0f,0.0f))
	, m_flastOffset(0.0f)
	, m_fAccel(120)
{
	init();
}


void PhysicsMovePage::addPage(ref<Node2D> pageItem)
{
	nb::Size s = size();
	float length = (m_itemOrientation == nb::OrientationE::Horizontal) ? s.width * m_vecPageItems.size() : s.height * m_vecPageItems.size();
	m_vecPageItems.push_back(pageItem);
	nb::Point position(0.0);
	if (m_itemOrientation == nb::OrientationE::Horizontal)
	{
		position.x = length;
	}
	else
	{
		position.y = length;
	}
	pageItem->setPosition(position);
	addChild(pageItem);
	++m_itemcount;
	
	jumpToPosition(0.0f);
	m_flastOffset = 0.0f;
}

void PhysicsMovePage::onRender()
{
	Node2D::onRender();
}

void PhysicsMovePage::onTouch(const TouchEventArgs &e)
{
	switch (e.action)
	{
	case nb::TouchActionE::down:
	{
		Point pt(e.x, e.y);
		onMousePress(pt);
		break;
	}	
	case nb::TouchActionE::move:
	{
		Point pt(e.x, e.y);
		onMouseMove(pt);
		break;
	}	
	case nb::TouchActionE::up:
	{
		Point pt(e.x, e.y);
		onMouseRelease(pt);
		break;
	}	
	default:
		break;
	}
}

void PhysicsMovePage::init()
{
	m_pKineticMove = createRef<CKineticMove>();
	m_pGestureAnalyse = createRef<CGestureAnalyse>();
	m_pMovePositionAnalyse = createRef<CMovePositionAnalyse>();

	m_pKineticMove->MoveDistance += nbBindEventFunction(PhysicsMovePage::OnKineticScroll);
	m_pKineticMove->MoveEnd += nbBindEventFunction(PhysicsMovePage::OnKineticScrollEnd);
}

void PhysicsMovePage::onMousePress(Point pos)
{
	if (m_itemcount == 0) return;

	m_bIsPress = true;

	m_pKineticMove->Stop();
	m_pMovePositionAnalyse->Start(pos);
	m_pGestureAnalyse->GesturePress(pos);

	m_MouseLastMovePos = pos;
}

void PhysicsMovePage::onMouseMove(Point pos)
{
	if (m_itemcount == 0) return;
	if (!m_bIsPress) return;

	m_pMovePositionAnalyse->Move(pos);
	if (!m_pMovePositionAnalyse->IsActive())
	{
		return;
	}	

	m_pGestureAnalyse->GestureMove(pos);

	if (m_bIsPress)
	{
		float offset = pos.x - m_MouseLastMovePos.x;
		m_flastOffset += offset;
		jumpToPosition(m_flastOffset);
	}
	//Log::info("KineticScroll, m_flastOffset={}", m_flastOffset);

	m_MouseLastMovePos = pos;
}

void PhysicsMovePage::onMouseRelease(Point pos)
{
	m_bIsPress = false;

	if (m_itemcount == 0) return;
	
	if (!m_pMovePositionAnalyse->IsActive())
		return;

	m_pGestureAnalyse->GestureRelease(pos);


	//获取速度
	float fSpeed;
	if (m_itemOrientation == OrientationE::Horizontal)
		fSpeed = m_pGestureAnalyse->GetHorizontalSpeed();
	else
		fSpeed = m_pGestureAnalyse->GetVerticalSpeed();


	//加速度
	float fAccel = fSpeed > 0 ? -m_fAccel : m_fAccel;

	if (fSpeed == 0)
	{
		fAccel = 0;
	}

	m_pKineticMove->OffsetStartPos(m_flastOffset);
	m_pKineticMove->Start(fAccel, fSpeed,m_flastOffset);
	m_pMovePositionAnalyse->Cancel();
}

void PhysicsMovePage::jumpToPosition(float position)
{
	nb::Size s = size();
	float pos = 0.0;
	nb::Point point(0.0);
	for (int i = 0; i < m_itemcount; i++)
	{
		pos = (m_itemOrientation == nb::OrientationE::Horizontal) ? position + i * s.width : position + i * s.height;
		if (m_itemOrientation == nb::OrientationE::Horizontal)
		{
			point.x = pos;
			point.y = 0.0;
		}
		else
		{
			point.x = 0.0;
			point.y = pos;
		}
		auto item = m_vecPageItems.at(i);
		item->setPosition(point);
	}
}

void PhysicsMovePage::OnKineticScroll(const MoveDistanceEventArgs & e)
{
	float nSpace = float(e.m_space);
	//Log::info("KineticScroll, space={}", nSpace);

	jumpToPosition(nSpace);
	m_flastOffset = nSpace;
}

void PhysicsMovePage::OnKineticScrollEnd(const MoveEndEventArgs & e)
{}