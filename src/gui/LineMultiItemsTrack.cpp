#include "gui/LineMultiItemsTrack.h"
#include "LineMultiItemsTrackPrivate.h"
#include "ReboundScrollCtrler.h"


using namespace nb::Gui;
NB_OBJECT_TYPE_IMPLEMENT(LineMultiItemsTrack, BaseTrack, NULL, NULL);



LineMultiItemsTrack::LineMultiItemsTrack()
{
	m_private = new LineMultiItemsTrackPrivate(this);
}

LineMultiItemsTrack::~LineMultiItemsTrack()
{
	delete m_private;
}

LineMultiItemsTrackPrivate *LineMultiItemsTrack::GetPrivate()
{
	return m_private;
}


//ILineMultiItemsTrackHandle Interfaces			
//ILineMultiItemsTrackHandleEvent *LineMultiItemsTrack::SetEventInterface(ILineMultiItemsTrackHandleEvent *pEvent)
//{
//	return GetPrivate()->SetEventInterface(pEvent);
//}

void LineMultiItemsTrack::SetOrientation(nb::Gui::TrackOrientation nTrackOrientation)
{
	GetPrivate()->SetOrientation(nTrackOrientation);
}

void LineMultiItemsTrack::SetItemCount(int nCount)
{
	GetPrivate()->SetItemCount(nCount);
}

int LineMultiItemsTrack::GetItemCount() /*const*/
{
	return GetPrivate()->GetItemCount();
}

void LineMultiItemsTrack::SetItemSize(int nSize)
{
	GetPrivate()->SetItemSize(nSize);
}

int LineMultiItemsTrack::GetItemSize() /*const*/
{
	return GetPrivate()->GetItemSize();
}

void LineMultiItemsTrack::SetPageSize(int nSize)
{
	GetPrivate()->SetPageSize(nSize);
}

int LineMultiItemsTrack::GetPageSize() /*const*/
{
	return GetPrivate()->GetPageSize();
}

void LineMultiItemsTrack::SetFirstItem(int nItem)
{
	GetPrivate()->SetFirstItem(nItem);
}

void LineMultiItemsTrack::SetFirstItemOffset(float fOffset)
{
	GetPrivate()->SetFirstItemOffset(fOffset);
}

void LineMultiItemsTrack::ZeroItemOffset()
{
	GetPrivate()->ZeroItemOffset();
}

void LineMultiItemsTrack::SetAccel(float fAccel)
{
	GetPrivate()->SetAccel(fAccel);
}

void LineMultiItemsTrack::SetMaxSpeed(float fSpeed)
{
	GetPrivate()->SetMaxSpeed(fSpeed);
}

void LineMultiItemsTrack::SetHoldBackSpeed(float fSpeed)
{
	GetPrivate()->SetHoldBackSpeed(fSpeed);
}

void LineMultiItemsTrack::SetReboundAccel(float fAccel)
{
	GetPrivate()->SetReboundAccel(fAccel);
}


void LineMultiItemsTrack::SetCycMode(bool bCycMode)
{
	GetPrivate()->SetCycMode(bCycMode);
}


int LineMultiItemsTrack::GetFirstItem() /*const*/
{
	return GetPrivate()->GetFirstItem();
}

float LineMultiItemsTrack::GetFirstItemOffset() /*const*/
{
	return GetPrivate()->GetFirstItemOffset();
}


int LineMultiItemsTrack::GetPressItem() /*const*/
{
	return GetPrivate()->GetPressItem();
}


void LineMultiItemsTrack::ScrollIncrease(int nItems, float fAccel)
{
	GetPrivate()->ScrollIncrease(nItems, fAccel);
}

void LineMultiItemsTrack::ScrollDecrease(int nItems, float fAccel)
{
	GetPrivate()->ScrollDecrease(nItems, fAccel);
}

void LineMultiItemsTrack::ScrollDistance(float fDistance, float fAccel)
{
	GetPrivate()->ScrollDistance(fDistance, fAccel);
}

void LineMultiItemsTrack::StopScroll()
{
	GetPrivate()->StopScroll();
}

bool LineMultiItemsTrack::IsScrolling() /*const*/
{
	return GetPrivate()->IsScrolling();
}

bool LineMultiItemsTrack::IsPointerActive() /*const*/
{
	return GetPrivate()->IsPointerActive();
}

void LineMultiItemsTrack::TrackEnable(bool bEnable)
{
	Enable() = bEnable;
}

void LineMultiItemsTrack::SetMonopolizePointer(bool bMonopolizePointer)
{
	MonopolizePointer() = bMonopolizePointer;
}

void LineMultiItemsTrack::LimitScrollItems(int nItems)
{
	GetPrivate()->LimitScrollItems(nItems);
}
//BaseTrack methods
void LineMultiItemsTrack::OnPointerPress(const nb::System::Point &point)
{
	BaseTrack::OnPointerPress(point);
	GetPrivate()->OnPointerPress(point);
}

void LineMultiItemsTrack::OnPointerMove(const nb::System::Point &point)
{
	BaseTrack::OnPointerMove(point);
	GetPrivate()->OnPointerMove(point);

	PointerMoveEventParam param;
	param.m_ptPosition = point;
	PointerMoveEvent.Dispatch(param);
}

void LineMultiItemsTrack::OnPointerRelease(const nb::System::Point &point)
{
	BaseTrack::OnPointerRelease(point);
	GetPrivate()->OnPointerRelease(point);

	PointerReleasedEventParam param;
	param.m_ptPosition = point;
	PointerReleasedEvent.Dispatch(param);
}

void LineMultiItemsTrack::On_LineMultiItemsTrack_Move(int nFirstItem, float fFirstItemOffset, nb::Gui::TrackOrientation nTrackOrientation)
{
	TrackMoveEventParam param;
	param.m_nFirstItem = nFirstItem;
	param.m_fFirstItemOffset = fFirstItemOffset;
	param.m_nTrackOrientation = nTrackOrientation;
	TrackMoveEvent.Dispatch(param);
}

void LineMultiItemsTrack::On_LineMultiItemsTrack_End()
{
	TrackMoveEndEventParam param;
	TrackMoveEndEvent.Dispatch(param);
}

void LineMultiItemsTrack::On_LineMultiItemsTrack_FirstItemChanged(int nNewFirstItem, int nOldFirstItem)
{
	TrackFirstItemChangedEventParam param;
	param.m_nOldFirstItem = nOldFirstItem;
	param.m_nNewFirstItem = nNewFirstItem;
	TrackFirstItemChangedEvent.Dispatch(param);
}
