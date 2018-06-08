#include "LineMultiItemsTrackPrivate.h"
#include "system/System.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;


LineMultiItemsTrackPrivate::LineMultiItemsTrackPrivate(LineMultiItemsTrack *owner)
: m_owner(owner)
//, m_pEvent(NULL)
{
	m_pRSC = new ReboundScrollCtrler();
	m_pRSC->ScrollEvent.Add(this, &LineMultiItemsTrackPrivate::OnScrollCtrlerScroll);
	m_pRSC->ScrollEndEvent.Add(this, &LineMultiItemsTrackPrivate::OnScrollCtrlerScrollEnd);
	m_pRSC->FirstItemChangedEvent.Add(this, &LineMultiItemsTrackPrivate::OnScrollCtrlerFirstItemChanged);
	SetOrientation(nb::Gui::TrackOrientation_Vert);
}

LineMultiItemsTrackPrivate::~LineMultiItemsTrackPrivate()
{
}

//ILineMultiItemsTrackHandle Interfaces			
//ILineMultiItemsTrackHandleEvent *LineMultiItemsTrackPrivate::SetEventInterface(ILineMultiItemsTrackHandleEvent *pEvent)
//{
//	ILineMultiItemsTrackHandleEvent *pOld = m_pEvent;
//	m_pEvent = pEvent;
//	return pOld;
//}

void LineMultiItemsTrackPrivate::SetOrientation(nb::Gui::TrackOrientation nTrackOrientation)
{
	if(nTrackOrientation == nb::Gui::TrackOrientation_Hor)
	{
		m_pRSC->SetGestureLock(15, 10000);
	}
	else
	{
		m_pRSC->SetGestureLock(10000, 15);
	}
	m_pRSC->WorkMode() = (nb::Gui::EnumWorkMode)nTrackOrientation;
}

void LineMultiItemsTrackPrivate::SetItemCount(int nCount)
{
	m_pRSC->ItemCount = nCount;
}

int LineMultiItemsTrackPrivate::GetItemCount() /*const*/
{
	int nItemCount = (Int)m_pRSC->ItemCount;
	return nItemCount;
}

void LineMultiItemsTrackPrivate::SetItemSize(int nSize)
{
	m_pRSC->ItemSize = (float)nSize;
}

int LineMultiItemsTrackPrivate::GetItemSize() /*const*/
{
	float fItemSize = (Float)m_pRSC->ItemSize;
	return (int)fItemSize;
}

void LineMultiItemsTrackPrivate::SetPageSize(int nSize)
{
	m_pRSC->PageSize = (float)nSize;
}

int LineMultiItemsTrackPrivate::GetPageSize() /*const*/
{
	float fPageSize = (Float)m_pRSC->PageSize;
	return (int)fPageSize;
}

void LineMultiItemsTrackPrivate::SetFirstItem(int nItem)
{
	m_pRSC->FirstItem = nItem;
}

void LineMultiItemsTrackPrivate::SetFirstItemOffset(float fOffset)
{
	m_pRSC->FirstItemOffset = fOffset;
}

void LineMultiItemsTrackPrivate::ZeroItemOffset()
{
	m_pRSC->ZeroItemOffset();
}

void LineMultiItemsTrackPrivate::SetAccel(float fAccel)
{
	m_pRSC->Accel = fAccel;
}

void LineMultiItemsTrackPrivate::SetMaxSpeed(float fSpeed)
{
	m_pRSC->MaxSpeed = fSpeed;
}

void LineMultiItemsTrackPrivate::SetHoldBackSpeed(float fSpeed)
{
	m_pRSC->HoldBackSpeed = fSpeed;
}

void LineMultiItemsTrackPrivate::SetReboundAccel(float fAccel)
{
	m_pRSC->ReboundAccel = fAccel;
}

void LineMultiItemsTrackPrivate::SetCycMode(bool bCycMode)
{
	m_pRSC->CycMode = bCycMode;
}


int LineMultiItemsTrackPrivate::GetFirstItem() /*const*/
{
	int nFirstItem = (Int)m_pRSC->FirstItem;
	return nFirstItem;
}

float LineMultiItemsTrackPrivate::GetFirstItemOffset() /*const*/
{
	float fFirstItemOffset = (Float)m_pRSC->FirstItemOffset;
	return fFirstItemOffset;
}


int LineMultiItemsTrackPrivate::GetPressItem() /*const*/
{
	int nPressItem = (Int)m_pRSC->PressItem;
	return nPressItem;
}

void LineMultiItemsTrackPrivate::ScrollIncrease(int nItems, float fAccel)
{
	m_pRSC->ScrollIncrease(nItems, fAccel);
	//if(m_pRSC->IsScrolling()) m_pView->OnTrackAutoBeginScroll(m_owner);
}

void LineMultiItemsTrackPrivate::ScrollDecrease(int nItems, float fAccel)
{
	m_pRSC->ScrollDecrease(nItems, fAccel);
	//if(m_pRSC->IsScrolling()) m_pView->OnTrackAutoBeginScroll(m_owner);
}

void LineMultiItemsTrackPrivate::ScrollDistance(float fDistance, float fAccel)
{
	if(fDistance != 0.0f)
	{
		m_pRSC->ScrollDistance(fDistance, fAccel);
		//m_pView->OnTrackAutoBeginScroll(m_owner);
	}
}

void LineMultiItemsTrackPrivate::StopScroll()
{
	m_pRSC->StopScroll();
}


bool LineMultiItemsTrackPrivate::IsScrolling() /*const*/
{
	return m_pRSC->IsScrolling();
}

bool LineMultiItemsTrackPrivate::IsPointerActive() /*const*/
{
	return m_pRSC->IsActiveScroll();
}

void LineMultiItemsTrackPrivate::LimitScrollItems(int nItems)
{
	m_nLimitScrollItems = nItems;
}
//BaseTrack methods
void LineMultiItemsTrackPrivate::OnPointerPress(const nb::System::Point &point)
{
	m_pRSC->StopScroll();
	m_pRSC->PointerPressEvent(point);

	if(m_nLimitScrollItems > 0)
	{
		int nFirstItem = (Int)m_pRSC->FirstItem;
		int nItemCount = (Int)m_pRSC->ItemCount;
		int nLeftLimit = nb::System::Max(nFirstItem-m_nLimitScrollItems, 0);
		int nRightLimit = nb::System::Min(nFirstItem+m_nLimitScrollItems, nItemCount-1);
		//m_pRSC->LimitScrollRange(nLeftLimit, nRightLimit);
		m_pRSC->MinScrollItem = nLeftLimit;
		m_pRSC->MaxScrollItem = nRightLimit;
	}

	//if(m_pEvent)
	//{
	//	m_pEvent->On_LineMultItemsTrack_Prep(m_owner);
	//}
}

void LineMultiItemsTrackPrivate::OnPointerMove(const nb::System::Point &point)
{
	m_pRSC->PointerMoveEvent(point);

	//if(m_pEvent)
	//{
	//	int nFirstItem = (Int)m_pRSC->FirstItem;
	//	float fFirstItemOffset = (Float)m_pRSC->FirstItemOffset;
	//	m_pEvent->On_LineMultItemsTrack_PointerMove(m_owner, nFirstItem, fFirstItemOffset);
	//}
}

void LineMultiItemsTrackPrivate::OnPointerRelease(const nb::System::Point &point)
{
	m_pRSC->PointerReleaseEvent(point);

	//if(m_pEvent)
	//{
	//	int nFirstItem = (Int)m_pRSC->FirstItem;
	//	float fFirstItemOffset = (Float)m_pRSC->FirstItemOffset;
	//	m_pEvent->On_LineMultItemsTrack_PointerHasReleased(m_owner, nFirstItem, fFirstItemOffset);
	//}
}

void LineMultiItemsTrackPrivate::OnScrollCtrlerScroll(nb::Gui::ReboundScrollCtrler::ScrollEventParam &param)
{
	//if(m_pEvent)
	//{
	//	m_pEvent->On_LineMultItemsTrack_Move(m_owner, param.m_nFirstItem, param.m_fFirstItemOffset, param.m_nWorkMode);
	//}
	m_owner->On_LineMultiItemsTrack_Move(param.m_nFirstItem, param.m_fFirstItemOffset, (nb::Gui::TrackOrientation)param.m_nWorkMode);
}

void LineMultiItemsTrackPrivate::OnScrollCtrlerScrollEnd(nb::Gui::ReboundScrollCtrler::ScrollEndEventParam &param)
{
	//m_pView->OnTrackFinish(this);

	//if(m_pEvent)
	//{
	//	m_pEvent->On_LineMultItemsTrack_End(m_owner);
	//}
	m_owner->On_LineMultiItemsTrack_End();
}

void LineMultiItemsTrackPrivate::OnScrollCtrlerFirstItemChanged(nb::Gui::ReboundScrollCtrler::FirstItemChangedEventParam &param)
{
	//if(m_pEvent)
	//{
	//	m_pEvent->On_LineMultItemsTrack_FirstItemChanged(m_owner, param.m_nNewFirstItem, param.m_nOldFirstItem);
	//}
	m_owner->On_LineMultiItemsTrack_FirstItemChanged(param.m_nNewFirstItem, param.m_nOldFirstItem);
}
