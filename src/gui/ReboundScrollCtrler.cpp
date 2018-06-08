#include "ReboundScrollCtrler.h"
#include "system/System.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(ReboundScrollCtrler, nbObject, NULL, NULL);


NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, ItemCount, aInt, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, FirstItem, aInt, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, ItemSize, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, FirstItemOffset, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, PageSize, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, Accel, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, ReboundAccel, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, MaxSpeed, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, HoldBackSpeed, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, CycMode, aBool, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, PressItem, aInt, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(ReboundScrollCtrler, WorkMode, nb::Core::EnumObject, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, MinScrollItem, aInt, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScrollCtrler, MaxScrollItem, aInt, NULL);

ReboundScrollCtrler::ReboundScrollCtrler()
: m_bScrollByIncDec(false)
, m_fPressFirstItemOffset(0.0f)
, m_fOffsetOfPressPosToPressItemBegin(0.0f)
, m_nPressFirstItem(-1)
{
	m_pReboundScroll = new ReboundScroll();
	m_pReboundScroll->ScrollEvent.Add(this, &ReboundScrollCtrler::OnKineticScroll);
	m_pReboundScroll->ScrollEndEvent.Add(this, &ReboundScrollCtrler::OnKineticScrollEnd);
	m_pMovePositionAnalyse = new MovePositionAnalyse();
	m_pGestureAnalyse = new GestureAnalyse();
	ItemSize = 10.0f;
	PageSize = 100.0f;
	ItemCount = 0;
	FirstItem = 0;
	FirstItemOffset = 0.0f;
	WorkMode() = nb::Gui::WorkMode_Hor;
	PressItem = -1;
	Accel = 120.0f;
	HoldBackSpeed = 300.0f;
	MinScrollItem = -1;
	MaxScrollItem = -1;
	MaxSpeed = -1;
	CycMode = false;
}

ReboundScrollCtrler::~ReboundScrollCtrler()
{
}


void ReboundScrollCtrler::SetGestureLock(int xGestureLock, int yGestureLock)
{
	m_pMovePositionAnalyse->SetLock((float)xGestureLock, (float)yGestureLock);
}

bool ReboundScrollCtrler::IsScrolling() const
{
	return (Boolx)m_pReboundScroll->IsRuning;
}

bool ReboundScrollCtrler::IsActiveScroll() const
{
	return m_pMovePositionAnalyse->IsActive();
}

float ReboundScrollCtrler::GetOffsetOfPressPosToPressItemBegin() const
{
	return m_fOffsetOfPressPosToPressItemBegin;
}

inline int ReboundScrollCtrler::GetVisibleItems() /*const*/
{
	return static_cast<int>((Float)PageSize / (Float)ItemSize);
}

inline void ReboundScrollCtrler::AdjustFirstItem()
{
	bool bCycMode = (Boolx)CycMode;
	if(!bCycMode) return;

	int nItemCount = (Int)ItemCount;
	if(nItemCount == 0) return;

	int nFirstItem = (Int)FirstItem;
	if(nFirstItem < 0)
	{
		FirstItem = nItemCount - 1 - ((-nFirstItem-1) % nItemCount);
	}
	else if(nFirstItem >= nItemCount)
	{
		FirstItem = nFirstItem%nItemCount;
	}
}

void ReboundScrollCtrler::StopScroll()
{
	m_pReboundScroll->Stop();
	m_pMovePositionAnalyse->Cancel();
}

void ReboundScrollCtrler::ZeroItemOffset()
{
	StopScroll();

	float nPageSize = (Float)PageSize;
	float nItemSize = (Float)ItemSize;
	int nFirstItem = (Int)FirstItem;
	int nItemCount = (Int)ItemCount;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float f = fFirstItemOffset - static_cast<int>(fFirstItemOffset / nItemSize) * nItemSize;

	if(nItemSize > nPageSize)
	{
		//待添加，未作处理
	}
	else
	{
		if(f > 0.001 || f < -0.001)
		{
			//加速度
			float fAccel = f > 0 ? 1000.0f : -1000.0f;

			//依据运行距离和加速度，计算初速度
			float fSpeed;
			KineticMove::ComputeVelocity(fAccel, -f, fSpeed);

			int nVisibleItems = GetVisibleItems();
			if(nVisibleItems == 0) nVisibleItems = 1;

			m_pReboundScroll->Start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*nItemSize, nVisibleItems*nItemSize, nItemCount*nItemSize);
		}
		else
		{
			FirstItemOffset = 0.0f;
//			emit SignalScrollEnd();
		}
	}
}


void ReboundScrollCtrler::ScrollIncrease(int nItems, float fAccel)
{
	m_pReboundScroll->Stop();
	int nItemCount = (Int)ItemCount;
	int nFirstItem = (Int)FirstItem;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float fItemSize = (Float)ItemSize;

	if(nItemCount == 0)
	{
		FirstItem = 1;
		return;
	}


	float f = -fFirstItemOffset-fItemSize*nItems;

	//加速度
//	float fAccel = 1000;

	float v;
	KineticMove::ComputeVelocity(fAccel, f, v);


	int nVisibleItems = GetVisibleItems();
	if(nVisibleItems == 0) nVisibleItems = 1;
	m_pReboundScroll->Start(fAccel, v, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);

	m_bScrollByIncDec = true;
}

void ReboundScrollCtrler::ScrollDecrease(int nItems, float fAccel)
{
	int nItemCount = (Int)ItemCount;
	int nFirstItem = (Int)FirstItem;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float fItemSize = (Float)ItemSize;
	float fPageSize = (Float)PageSize;
	if(nItemCount == 0)
	{
		FirstItem = 1;
		return;
	}

	float f;
	if(fPageSize >= fItemSize)
		f = -fFirstItemOffset+fItemSize*nItems;
	else
		f = -fFirstItemOffset+fPageSize*nItems;

	//加速度
//	float fAccel = -1000;
	fAccel = -fAccel;

	float v;
	KineticMove::ComputeVelocity(fAccel, f, v);


	int nVisibleItems = GetVisibleItems();
	if(nVisibleItems == 0) nVisibleItems = 1;
	m_pReboundScroll->Start(fAccel, v, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);

	m_bScrollByIncDec = true;
}

void ReboundScrollCtrler::ScrollDistance(float fDistance, float fAccel)
{
	if(fDistance == 0) return;

	if(fAccel < 0) fAccel = -fAccel;
	if(fDistance > 0) fAccel = -fAccel;

	float fFirstItemOffset = (Float)FirstItemOffset;
	float fItemSize = (Float)ItemSize;
	int nFirstItem = (Int)FirstItem;

	float k = fFirstItemOffset+fItemSize*nFirstItem;

	k += fDistance;
	
	float v;
	KineticMove::ComputeVelocity(fAccel, fDistance, v);

	ScrollWork(v, fAccel, false);

	m_bScrollByIncDec = true;
}

void ReboundScrollCtrler::PointerPressEvent(nb::System::Point pos)
{
	float fItemSize = (Float)ItemSize;
	int nItemCount = (Int)ItemCount;
	if(nItemCount == 0) return;

	m_bScrollByIncDec = false;

	m_pReboundScroll->Stop();

	m_pMovePositionAnalyse->Start(pos);
	m_pGestureAnalyse->GesturePress(pos);

	m_fPressFirstItemOffset = (Float)FirstItemOffset;
	m_nPressFirstItem = (Int)FirstItem;


	int nOffset = (int)(pos.GetY()-m_fPressFirstItemOffset);
	int nPressItem = static_cast<int>(nOffset / fItemSize);
	PressItem = nPressItem;
	m_fOffsetOfPressPosToPressItemBegin = nOffset - nPressItem * fItemSize;

	nPressItem += m_nPressFirstItem;
	if(nPressItem >= nItemCount)
	{
		nPressItem = -1;
	}
	PressItem = nPressItem;
}

void ReboundScrollCtrler::PointerMoveEvent(nb::System::Point pos)
{
	int nItemCount = (Int)ItemCount;
	int nFirstItem = (Int)FirstItem;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float fItemSize = (Float)ItemSize;
	float fPageSize = (Float)PageSize;
	if(nItemCount == 0) return;

	m_pMovePositionAnalyse->Move(pos);
	if(!m_pMovePositionAnalyse->IsActive())
		return;


	nb::System::Point ptOrigin = m_pMovePositionAnalyse->GetActivePos();

	AdjustDragPos(ptOrigin, pos);
	m_pGestureAnalyse->GestureMove(pos);

	float fOffset;
	EnumWorkMode nWorkMode = (EnumWorkMode)WorkMode();
	if(nWorkMode == WorkMode_Hor)
		fOffset = pos.GetX() - ptOrigin.GetX();
	else
		fOffset = pos.GetY() - ptOrigin.GetY();

//	if(fOffset != 0)
	{
		int nOldFirstItem = nFirstItem;
		float fOldOffset = fFirstItemOffset;

		fFirstItemOffset = m_fPressFirstItemOffset + fOffset;

		int k;
		if(fItemSize > fPageSize)
		{
			if(fFirstItemOffset < 0)
			{
				k = (int)((fFirstItemOffset - fPageSize/2) / fItemSize);
			}
			else
			{
				k = static_cast<int>(fFirstItemOffset / fItemSize);
				k += (fFirstItemOffset - k*fItemSize) >= fPageSize/2 ? 1 : 0;
			}
		}
		else
		{
			if(fFirstItemOffset < 0)
				k = (int)((fFirstItemOffset - fItemSize/2) / fItemSize);
			else
				k = static_cast<int>((fFirstItemOffset + fItemSize/2) / fItemSize);
		}

		nFirstItem = m_nPressFirstItem - k;
		FirstItem = nFirstItem;
		AdjustFirstItem();
		fFirstItemOffset -= k*fItemSize;
		FirstItemOffset = fFirstItemOffset;

		nFirstItem = (Int)FirstItem;
		fFirstItemOffset = (Float)FirstItemOffset;
		ScrollEventParam param;
		param.m_nFirstItem = nFirstItem;
		param.m_fFirstItemOffset = fFirstItemOffset;
		param.m_nWorkMode = (EnumWorkMode)WorkMode();
		ScrollEvent.Dispatch(param);
		if(nOldFirstItem != nFirstItem)
		{
			FirstItemChangedEventParam p;
			p.m_nNewFirstItem = nFirstItem;
			p.m_nOldFirstItem = nOldFirstItem;
			FirstItemChangedEvent.Dispatch(p);
		}
	}
}

void ReboundScrollCtrler::PointerReleaseEvent(nb::System::Point pos)
{
	int nItemCount = (Int)ItemCount;
	int nFirstItem = (Int)FirstItem;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float fItemSize = (Float)ItemSize;
	float fPageSize = (Float)PageSize;
	if(m_bScrollByIncDec) return;

	if(nItemCount == 0) return;

	if(m_pMovePositionAnalyse->IsActive())
	{
		nb::System::Point ptOrigin = m_pMovePositionAnalyse->GetActivePos();
		AdjustDragPos(ptOrigin, pos);
	}

	m_pGestureAnalyse->GestureRelease(pos);


	//获取速度
	float fSpeed;
	EnumWorkMode nWorkMode = (EnumWorkMode)WorkMode();
	if(nWorkMode == WorkMode_Hor)
		fSpeed = m_pGestureAnalyse->GetHorizontalSpeed();
	else
		fSpeed = m_pGestureAnalyse->GetVerticalSpeed();


	//加速度
	float accel = (Float)Accel;
	float fAccel = fSpeed > 0 ? -accel : accel;

	ScrollWork(fSpeed, fAccel, true);
}

void ReboundScrollCtrler::ScrollWork(float fSpeed, float fAccel, bool bUseHoldBackSpeed)
{
	int nFirstItem = (Int)FirstItem;
	int nOldFirstItem = nFirstItem;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float fOldOffset = fFirstItemOffset;
	float fHoldBackSpeed = (Float)HoldBackSpeed;
	float fMaxSpeed = (Float)MaxSpeed;
	float fItemSize = (Float)ItemSize;
	float fPageSize = (Float)PageSize;
	bool bCycMode = (Boolx)CycMode;
	int nMinScrollItem = (Int)MinScrollItem;
	int nMaxScrollItem = (Int)MaxScrollItem;
	int nItemCount = (Int)ItemCount;

	if(!bUseHoldBackSpeed || (fSpeed > fHoldBackSpeed || fSpeed < -fHoldBackSpeed))
	{
		//限制速度范围
		if(fMaxSpeed > 0)
		{
			if(fSpeed < -fMaxSpeed) fSpeed = -fMaxSpeed;
			else if(fSpeed > fMaxSpeed) fSpeed = fMaxSpeed;
		}

		//获取运行距离
		float fSpace;
		KineticMove::ComputeSpace(fSpeed, fAccel, fSpace);

		float f = fFirstItemOffset - static_cast<int>(fFirstItemOffset / fItemSize) * fItemSize;

		
		bool bAdjustSpace = false;
		int nLeftItem = nMinScrollItem >= 0 ? nMinScrollItem : 0;
		int nRightItem = nMaxScrollItem >= 0 ? nMaxScrollItem : nItemCount-1;

		if(bCycMode)
		{
			bAdjustSpace = true;
		}
		else
		{

			float fBeginOffet = -nFirstItem * fItemSize + f;
			float fStopOffset = fBeginOffet + fSpace;
			if(fSpeed < 0)
			{
				//向左（向上）移动
				float fRightStopOffset = fStopOffset + (nRightItem+1) * fItemSize;
				if(fRightStopOffset >= fPageSize)
				{
					if(fItemSize <= fPageSize)
					{
						bAdjustSpace = true;
					}
					else
					{
						float fItemStopOffset = fStopOffset + (nFirstItem+1)*fItemSize;
						if(fItemStopOffset < fPageSize || fItemStopOffset - fItemSize > 0)
						{
							//停止位置在后一项
							bAdjustSpace = true;
						}
					}
				}
			}
			else
			{
				//向右（向下）移动
				float fLeftStopOffset = fStopOffset + nLeftItem * fItemSize;
				if(fLeftStopOffset <= 0)
				{
					if(fItemSize <= fPageSize)
					{
						bAdjustSpace = true;
					}
					else
					{
						float fItemStopOffset = fStopOffset + nFirstItem*fItemSize;
						if(fItemStopOffset > 0 || fItemStopOffset + fItemSize < fPageSize)
						{
							//停止位置在前一项
							bAdjustSpace = true;
						}
					}
				}
			}
		}
	
		//调整运行距离
		int nSpace = (int)fSpace;
		if(bAdjustSpace)
		{
			nSpace /= (int)fItemSize;
			nSpace *= (int)fItemSize;

			if(fAccel > 0)
			{
				nSpace -= (int)fItemSize;
			}
			else if(fAccel < 0)
			{
				if(fItemSize > fPageSize) nSpace += (int)fPageSize;
				else nSpace += (int)fItemSize;
			}

			//依据运行距离和加速度，重新计算初速度
			KineticMove::ComputeVelocity(fAccel, nSpace-f, fSpeed);
		}


		//启动滚动

		int nVisibleItems = GetVisibleItems();
		if(nVisibleItems == 0) nVisibleItems = 1;

		int nItems = nItemCount;
		if(nItems < nVisibleItems) nItems = nVisibleItems;
//		m_pReboundScroll->Start(fAccel, fSpeed, m_fFirstItemOffset - m_nFirstItem*fItemSize, nVisibleItems*fItemSize, nItems*fItemSize);
		m_pReboundScroll->Start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*fItemSize, fPageSize, nItems*fItemSize);

		m_pReboundScroll->TopLeftReboundPos = nLeftItem >= 0 ? nLeftItem*fItemSize : 0;
		m_pReboundScroll->BottomRightReboundPos = nRightItem >= 0 ? (nRightItem+1)*fItemSize : nItems*fItemSize;
		m_pReboundScroll->ReboundStopLength = fPageSize / 2;
	}
	else
	{
		int nVisibleItems = GetVisibleItems();
		if(nVisibleItems == 0) nVisibleItems = 1;

		if(bCycMode) goto loop;
		if(nFirstItem < 0 || (nFirstItem == 0 && fFirstItemOffset > 0))
		{
		//	m_pReboundScroll->Start(-80, 0.1, m_fFirstItemOffset - m_nFirstItem*fItemSize, nVisibleItems*fItemSize, m_nItemCount*fItemSize);
			m_pReboundScroll->Start(-80, 0.1f, fFirstItemOffset - nFirstItem*fItemSize, fPageSize, nb::System::Max(nItemCount*fItemSize, fPageSize));
		}
		else if(nFirstItem + nVisibleItems > nItemCount || (nFirstItem + nVisibleItems == nItemCount && fFirstItemOffset < 0))
		{
		//	m_pReboundScroll->Start(80, -0.1, m_fFirstItemOffset - m_nFirstItem*fItemSize, nVisibleItems*fItemSize, m_nItemCount*fItemSize);
			m_pReboundScroll->Start(80, -0.1f, fFirstItemOffset - nFirstItem*fItemSize, fPageSize, nb::System::Max(nItemCount*fItemSize, fPageSize));
		}
		else
		{
loop:
			float f = fFirstItemOffset - static_cast<int>(fFirstItemOffset / fItemSize) * fItemSize;

			if(fItemSize > fPageSize)
			{
				if(f > -(fItemSize-fPageSize)-0.001f && f < 0.001f)
				{
					ScrollEventParam param;
					param.m_nFirstItem = nFirstItem;
					param.m_fFirstItemOffset = fFirstItemOffset;
					param.m_nWorkMode = (EnumWorkMode)WorkMode();
					ScrollEvent.Dispatch(param);
					if(nOldFirstItem != nFirstItem)
					{
						FirstItemChangedEventParam p;
						p.m_nNewFirstItem = nFirstItem;
						p.m_nOldFirstItem = nOldFirstItem;
						FirstItemChangedEvent.Dispatch(p);
					}
					ScrollEndEventParam pp;
					ScrollEndEvent.Dispatch(pp);
					return;
				}
				else
				{
					fAccel = f > 0 ? 280.0f : -280.0f;

					//依据运行距离和加速度，计算初速度
					float fSpeed;
					if(f >= 0)
					{
						if(f <= fPageSize/2)
							KineticMove::ComputeVelocity(fAccel, -f, fSpeed);
						else
						{
							fAccel = -fAccel;
							KineticMove::ComputeVelocity(fAccel, fPageSize-f, fSpeed);
						}
					}
					else
					{
						KineticMove::ComputeVelocity(fAccel, -f+fPageSize-fItemSize, fSpeed);
					}

					int nVisibleItems = GetVisibleItems();
					if(nVisibleItems == 0) nVisibleItems = 1;

					m_pReboundScroll->Start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);
				}
			}
			else
			{
				if(f > 0.001f || f < -0.001f)
				{
					//加速度
					fAccel = f > 0 ? 280.0f : -280.0f;

					//依据运行距离和加速度，计算初速度
					float fSpeed;
					KineticMove::ComputeVelocity(fAccel, -f, fSpeed);

					int nVisibleItems = GetVisibleItems();
					if(nVisibleItems == 0) nVisibleItems = 1;

					m_pReboundScroll->Start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);
				}
				else
				{
					fFirstItemOffset = 0.0f;
					FirstItemOffset = fFirstItemOffset;
					ScrollEndEventParam p;
					ScrollEndEvent.Dispatch(p);
				}
			}
		}
	}
}

inline void ReboundScrollCtrler::AdjustDragPos(nb::System::Point posOrigin, nb::System::Point &pos) /*const*/
{
	int nFirstItem = (Int)FirstItem;
	int nOldFirstItem = nFirstItem;
	float fFirstItemOffset = (Float)FirstItemOffset;
	float fOldOffset = fFirstItemOffset;
	float fHoldBackSpeed = (Float)HoldBackSpeed;
	float fMaxSpeed = (Float)MaxSpeed;
	float fItemSize = (Float)ItemSize;
	float fPageSize = (Float)PageSize;
	bool bCycMode = (Boolx)CycMode;
	int nMinScrollItem = (Int)MinScrollItem;
	int nMaxScrollItem = (Int)MaxScrollItem;
	int nItemCount = (Int)ItemCount;

	if(bCycMode) return;

	//压下点位置的总体偏移
	float fPressOffset = m_fPressFirstItemOffset - m_nPressFirstItem * fItemSize;

	float fOffset;
	EnumWorkMode nWorkMode = (EnumWorkMode)WorkMode();
	if(nWorkMode == WorkMode_Hor)
		fOffset = pos.GetX() - posOrigin.GetX();
	else
		fOffset = pos.GetY() - posOrigin.GetY();

	//假如不对pos进行调整，拖动到pos后的预计总体偏移
	float fPredictOffset = fPressOffset + fOffset;

	
	///////////////////////////////////////////////////////////////////////////
	//对pos进行调整校正处理

	int nLeftReboundItem = nMinScrollItem < 0 ? 0 : nMinScrollItem;
	int nRightReboundItem = nMaxScrollItem < 0 ? nItemCount : nMaxScrollItem+1;

	if(fPredictOffset + nLeftReboundItem*fItemSize > 0)
	{
		if(fPredictOffset > fPressOffset)
		{
			if(nWorkMode == WorkMode_Hor)
			{
				if(fPressOffset + nLeftReboundItem*fItemSize >= 0) pos.SetX(pos.GetX() - (fPredictOffset - fPressOffset)/2);
				else pos.SetX(pos.GetX() - (fPredictOffset + nLeftReboundItem*fItemSize)/2);

				fOffset = pos.GetX() - posOrigin.GetX();
				fPredictOffset = fPressOffset + fOffset;
				if(fPredictOffset > nLeftReboundItem*fItemSize + fPageSize/2)
				{
					pos.SetX(pos.GetX() - (fPredictOffset + nLeftReboundItem*fItemSize - fPageSize/2));
				}
			}
			else
			{
				if(fPressOffset >= nLeftReboundItem*fItemSize) pos.SetY(pos.GetY() - (fPredictOffset - fPressOffset)/2);
				else pos.SetY(pos.GetY() - (fPredictOffset + nLeftReboundItem*fItemSize)/2);

				fOffset = pos.GetY() - posOrigin.GetY();
				fPredictOffset = fPressOffset + fOffset;
				if(fPredictOffset > nLeftReboundItem*fItemSize + fPageSize/2)
				{
					pos.SetY(pos.GetY() - (fPredictOffset + nLeftReboundItem*fItemSize - fPageSize/2));
				}
			}
		}
	}
	else if(fPredictOffset + nRightReboundItem*fItemSize < fPageSize)
	{
		if(fPredictOffset < fPressOffset)
		{
			if(nWorkMode == WorkMode_Hor)
			{
				if((nRightReboundItem-nLeftReboundItem)*fItemSize > fPageSize/2)
				{
					if(fPressOffset + nRightReboundItem*fItemSize <= fPageSize) pos.SetX(pos.GetX() - (fPredictOffset - fPressOffset)/2);
					else pos.SetX(pos.GetX() + (fPageSize - (fPredictOffset+nRightReboundItem*fItemSize))/2);

					fOffset = pos.GetX() - posOrigin.GetX();
					fPredictOffset = fPressOffset + fOffset;
					if(fPredictOffset + nRightReboundItem*fItemSize < fPageSize/2)
					{
						pos.SetX(pos.GetX() - (fPredictOffset + nRightReboundItem*fItemSize - fPageSize/2));
					}
				}
				else
				{
					pos.SetX(posOrigin.GetX());
				}
			}
			else
			{
				if((nRightReboundItem-nLeftReboundItem)*fItemSize > fPageSize/2)
				{
					if(fPressOffset + nRightReboundItem*fItemSize <= fPageSize) pos.SetY(pos.GetY() - (fPredictOffset - fPressOffset)/2);
					else pos.SetY(pos.GetY() + (fPageSize - (fPredictOffset+nRightReboundItem*fItemSize))/2);

					fOffset = pos.GetY() - posOrigin.GetY();
					fPredictOffset = fPressOffset + fOffset;
					if(fPredictOffset + nRightReboundItem*fItemSize < fPageSize/2)// && fPredictOffset + nLeftReboundItem*fItemSize > 0)
					{
						pos.SetY(pos.GetY() - (fPredictOffset + nRightReboundItem*fItemSize - fPageSize/2));
					}
				}
				else
				{
					pos.SetY(posOrigin.GetY());
				}
			}
		}
	}
}

void ReboundScrollCtrler::OnKineticScroll(ReboundScroll::ScrollEventParam &param)
{
	int nOldFirstItem = (Int)FirstItem;
	float fOldOffset = (Float)FirstItemOffset;
	float fItemSize = (Float)ItemSize;
	float fPageSize = (Float)PageSize;

	FirstItemOffset = param.m_nSpace;
	float fFirstItemOffset = param.m_nSpace;

	int k;
	if(fItemSize > fPageSize)
	{
		if(fFirstItemOffset < 0)
		{
			k = (fFirstItemOffset - fPageSize/2) / fItemSize;
		}
		else
		{
			k = static_cast<int>(fFirstItemOffset / fItemSize);
			k += (fFirstItemOffset - k*fItemSize) >= fPageSize/2 ? 1 : 0;
		}
	}
	else
	{
		if(fFirstItemOffset < 0)
			k = (fFirstItemOffset - fItemSize/2) / fItemSize;
		else
			k = (fFirstItemOffset + fItemSize/2) / fItemSize;
	}


	FirstItem = - k;
	AdjustFirstItem();
	fFirstItemOffset -= k*fItemSize;
	FirstItemOffset = fFirstItemOffset;


	EnumWorkMode nWorkMode = (EnumWorkMode)WorkMode();
	ScrollEventParam pse;
	pse.m_nFirstItem = (Int)FirstItem;
	pse.m_fFirstItemOffset = (Float)FirstItemOffset;
	pse.m_nWorkMode = nWorkMode;
	ScrollEvent.Dispatch(pse);
	int nFirstItem = (Int)FirstItem;
	if(nOldFirstItem != nFirstItem)
	{
		FirstItemChangedEventParam p;
		p.m_nNewFirstItem = nFirstItem;
		p.m_nOldFirstItem = nOldFirstItem;
		FirstItemChangedEvent.Dispatch(p);
	}
}

void ReboundScrollCtrler::OnKineticScrollEnd(ReboundScroll::ScrollEndEventParam &param)
{
	m_bScrollByIncDec = false;
	ScrollEndEventParam p;
	ScrollEndEvent.Dispatch(p);
}
