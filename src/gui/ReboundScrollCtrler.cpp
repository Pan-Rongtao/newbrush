#include "ReboundScrollCtrler.h"

using namespace nb::core;
using namespace nb::gui;

ReboundScrollCtrler::ReboundScrollCtrler()
: m_bScrollByIncDec(false)
, m_fPressFirstItemOffset(0.0f)
, m_fOffsetOfPressPosToPressItemBegin(0.0f)
, m_nPressFirstItem(-1)
{
	m_pReboundScroll = std::make_shared<ReboundScroll>();
	m_pReboundScroll->ScrollEvent.addHandler(std::bind(&ReboundScrollCtrler::OnKineticScroll, this, std::placeholders::_1));
	m_pReboundScroll->ScrollEndEvent.addHandler(std::bind(&ReboundScrollCtrler::OnKineticScrollEnd, this, std::placeholders::_1));
	m_pMovePositionAnalyse = std::make_shared<MovePositionAnalyse>();
	m_pGestureAnalyse = std::make_shared<GestureAnalyse>();
	ItemSize = 10.0f;
	PageSize = 100.0f;
	ItemCount = 0;
	FirstItem = 0;
	FirstItemOffset = 0.0f;
	WorkMode = WorkMode_Hor;
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
	return m_pReboundScroll->IsRuning;
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
	return static_cast<int>(PageSize / ItemSize);
}

inline void ReboundScrollCtrler::AdjustFirstItem()
{
	bool bCycMode = CycMode;
	if(!bCycMode) return;

	int nItemCount = ItemCount;
	if(nItemCount == 0) return;

	int nFirstItem = FirstItem;
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
	m_pReboundScroll->stop();
	m_pMovePositionAnalyse->Cancel();
}

void ReboundScrollCtrler::ZeroItemOffset()
{
	StopScroll();

	float nPageSize = PageSize;
	float nItemSize = ItemSize;
	int nFirstItem = FirstItem;
	int nItemCount = ItemCount;
	float fFirstItemOffset = FirstItemOffset;
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

			m_pReboundScroll->start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*nItemSize, nVisibleItems*nItemSize, nItemCount*nItemSize);
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
	m_pReboundScroll->stop();
	int nItemCount = ItemCount;
	int nFirstItem = FirstItem;
	float fFirstItemOffset = FirstItemOffset;
	float fItemSize = ItemSize;

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
	m_pReboundScroll->start(fAccel, v, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);

	m_bScrollByIncDec = true;
}

void ReboundScrollCtrler::ScrollDecrease(int nItems, float fAccel)
{
	int nItemCount = ItemCount;
	int nFirstItem = FirstItem;
	float fFirstItemOffset = FirstItemOffset;
	float fItemSize = ItemSize;
	float fPageSize = PageSize;
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
	m_pReboundScroll->start(fAccel, v, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);

	m_bScrollByIncDec = true;
}

void ReboundScrollCtrler::ScrollDistance(float fDistance, float fAccel)
{
	if(fDistance == 0) return;

	if(fAccel < 0) fAccel = -fAccel;
	if(fDistance > 0) fAccel = -fAccel;

	float fFirstItemOffset = FirstItemOffset;
	float fItemSize = ItemSize;
	int nFirstItem = FirstItem;

	float k = fFirstItemOffset+fItemSize*nFirstItem;

	k += fDistance;
	
	float v;
	KineticMove::ComputeVelocity(fAccel, fDistance, v);

	ScrollWork(v, fAccel, false);

	m_bScrollByIncDec = true;
}

void ReboundScrollCtrler::PointerPressEvent(Point pos)
{
	float fItemSize = ItemSize;
	int nItemCount = ItemCount;
	if(nItemCount == 0) return;

	m_bScrollByIncDec = false;

	m_pReboundScroll->stop();

	m_pMovePositionAnalyse->Start(pos);
	m_pGestureAnalyse->GesturePress(pos);

	m_fPressFirstItemOffset = FirstItemOffset;
	m_nPressFirstItem = FirstItem;


	int nOffset = (int)(pos.y()-m_fPressFirstItemOffset);
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

void ReboundScrollCtrler::PointerMoveEvent(Point pos)
{
	int nItemCount = ItemCount;
	int nFirstItem = FirstItem;
	float fFirstItemOffset = FirstItemOffset;
	float fItemSize = ItemSize;
	float fPageSize = PageSize;
	if(nItemCount == 0) return;

	m_pMovePositionAnalyse->Move(pos);
	if(!m_pMovePositionAnalyse->IsActive())
		return;


	Point ptOrigin = m_pMovePositionAnalyse->GetActivePos();

	AdjustDragPos(ptOrigin, pos);
	m_pGestureAnalyse->GestureMove(pos);

	float fOffset;
	EnumWorkMode nWorkMode = WorkMode;
	if(nWorkMode == WorkMode_Hor)
		fOffset = pos.x() - ptOrigin.x();
	else
		fOffset = pos.y() - ptOrigin.y();

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

		nFirstItem = FirstItem;
		fFirstItemOffset = FirstItemOffset;
		ScrollArgs args;
		args.m_nFirstItem = nFirstItem;
		args.m_fFirstItemOffset = fFirstItemOffset;
		args.m_nWorkMode = WorkMode;
		ScrollEvent.dispatch(args);
		if(nOldFirstItem != nFirstItem)
		{
			FirstItemChangedArgs p;
			p.oldItem = nOldFirstItem;
			p.newItem = nFirstItem;
			FirstItemChangedEvent.dispatch(p);
		}
	}
}

void ReboundScrollCtrler::PointerReleaseEvent(Point pos)
{
	int nItemCount = ItemCount;
	int nFirstItem = FirstItem;
	float fFirstItemOffset = FirstItemOffset;
	float fItemSize = ItemSize;
	float fPageSize = PageSize;
	if(m_bScrollByIncDec) return;

	if(nItemCount == 0) return;

	if(m_pMovePositionAnalyse->IsActive())
	{
		Point ptOrigin = m_pMovePositionAnalyse->GetActivePos();
		AdjustDragPos(ptOrigin, pos);
	}

	m_pGestureAnalyse->GestureRelease(pos);


	//获取速度
	float fSpeed;
	EnumWorkMode nWorkMode = WorkMode;
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
	int nFirstItem = FirstItem;
	int nOldFirstItem = nFirstItem;
	float fFirstItemOffset = FirstItemOffset;
	float fOldOffset = fFirstItemOffset;
	float fHoldBackSpeed = HoldBackSpeed;
	float fMaxSpeed = MaxSpeed;
	float fItemSize = ItemSize;
	float fPageSize = PageSize;
	bool bCycMode = CycMode;
	int nMinScrollItem = MinScrollItem;
	int nMaxScrollItem = MaxScrollItem;
	int nItemCount = ItemCount;

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
		m_pReboundScroll->start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*fItemSize, fPageSize, nItems*fItemSize);

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
			m_pReboundScroll->start(-80, 0.1f, fFirstItemOffset - nFirstItem*fItemSize, fPageSize, std::max(nItemCount*fItemSize, fPageSize));
		}
		else if(nFirstItem + nVisibleItems > nItemCount || (nFirstItem + nVisibleItems == nItemCount && fFirstItemOffset < 0))
		{
		//	m_pReboundScroll->Start(80, -0.1, m_fFirstItemOffset - m_nFirstItem*fItemSize, nVisibleItems*fItemSize, m_nItemCount*fItemSize);
			m_pReboundScroll->start(80, -0.1f, fFirstItemOffset - nFirstItem*fItemSize, fPageSize, std::max(nItemCount*fItemSize, fPageSize));
		}
		else
		{
loop:
			float f = fFirstItemOffset - static_cast<int>(fFirstItemOffset / fItemSize) * fItemSize;

			if(fItemSize > fPageSize)
			{
				if(f > -(fItemSize-fPageSize)-0.001f && f < 0.001f)
				{
					ScrollArgs param;
					param.m_nFirstItem = nFirstItem;
					param.m_fFirstItemOffset = fFirstItemOffset;
					param.m_nWorkMode = WorkMode;
					ScrollEvent.dispatch(param);
					if(nOldFirstItem != nFirstItem)
					{
						FirstItemChangedArgs p;
						p.newItem = nFirstItem;
						p.oldItem = nOldFirstItem;
						FirstItemChangedEvent.dispatch(p);
					}
					ScrollEndArgs pp;
					ScrollEndEvent.dispatch(pp);
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

					m_pReboundScroll->start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);
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

					m_pReboundScroll->start(fAccel, fSpeed, fFirstItemOffset - nFirstItem*fItemSize, nVisibleItems*fItemSize, nItemCount*fItemSize);
				}
				else
				{
					fFirstItemOffset = 0.0f;
					FirstItemOffset = fFirstItemOffset;
					ScrollEndArgs p;
					ScrollEndEvent.dispatch(p);
				}
			}
		}
	}
}

inline void ReboundScrollCtrler::AdjustDragPos(Point posOrigin, Point &pos) /*const*/
{
	int nFirstItem = FirstItem;
	int nOldFirstItem = nFirstItem;
	float fFirstItemOffset = FirstItemOffset;
	float fOldOffset = fFirstItemOffset;
	float fHoldBackSpeed = HoldBackSpeed;
	float fMaxSpeed = MaxSpeed;
	float fItemSize = ItemSize;
	float fPageSize = PageSize;
	bool bCycMode = CycMode;
	int nMinScrollItem = MinScrollItem;
	int nMaxScrollItem = MaxScrollItem;
	int nItemCount = ItemCount;

	if(bCycMode) return;

	//压下点位置的总体偏移
	float fPressOffset = m_fPressFirstItemOffset - m_nPressFirstItem * fItemSize;

	float fOffset;
	EnumWorkMode nWorkMode = WorkMode;
	if(nWorkMode == WorkMode_Hor)
		fOffset = pos.x() - posOrigin.x();
	else
		fOffset = pos.y() - posOrigin.y();

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
				if(fPressOffset + nLeftReboundItem*fItemSize >= 0) pos.setX(pos.x() - (fPredictOffset - fPressOffset)/2);
				else pos.setX(pos.x() - (fPredictOffset + nLeftReboundItem*fItemSize)/2);

				fOffset = pos.x() - posOrigin.x();
				fPredictOffset = fPressOffset + fOffset;
				if(fPredictOffset > nLeftReboundItem*fItemSize + fPageSize/2)
				{
					pos.setX(pos.x() - (fPredictOffset + nLeftReboundItem*fItemSize - fPageSize/2));
				}
			}
			else
			{
				if(fPressOffset >= nLeftReboundItem*fItemSize) pos.setY(pos.y() - (fPredictOffset - fPressOffset)/2);
				else pos.setY(pos.y() - (fPredictOffset + nLeftReboundItem*fItemSize)/2);

				fOffset = pos.y() - posOrigin.y();
				fPredictOffset = fPressOffset + fOffset;
				if(fPredictOffset > nLeftReboundItem*fItemSize + fPageSize/2)
				{
					pos.setY(pos.y() - (fPredictOffset + nLeftReboundItem*fItemSize - fPageSize/2));
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
					if(fPressOffset + nRightReboundItem*fItemSize <= fPageSize) pos.setX(pos.x() - (fPredictOffset - fPressOffset)/2);
					else pos.setX(pos.x() + (fPageSize - (fPredictOffset+nRightReboundItem*fItemSize))/2);

					fOffset = pos.x() - posOrigin.x();
					fPredictOffset = fPressOffset + fOffset;
					if(fPredictOffset + nRightReboundItem*fItemSize < fPageSize/2)
					{
						pos.setX(pos.x() - (fPredictOffset + nRightReboundItem*fItemSize - fPageSize/2));
					}
				}
				else
				{
					pos.setX(posOrigin.x());
				}
			}
			else
			{
				if((nRightReboundItem-nLeftReboundItem)*fItemSize > fPageSize/2)
				{
					if(fPressOffset + nRightReboundItem*fItemSize <= fPageSize) pos.setY(pos.y() - (fPredictOffset - fPressOffset)/2);
					else pos.setY(pos.y() + (fPageSize - (fPredictOffset+nRightReboundItem*fItemSize))/2);

					fOffset = pos.y() - posOrigin.y();
					fPredictOffset = fPressOffset + fOffset;
					if(fPredictOffset + nRightReboundItem*fItemSize < fPageSize/2)// && fPredictOffset + nLeftReboundItem*fItemSize > 0)
					{
						pos.setY(pos.y() - (fPredictOffset + nRightReboundItem*fItemSize - fPageSize/2));
					}
				}
				else
				{
					pos.setY(posOrigin.y());
				}
			}
		}
	}
}

void ReboundScrollCtrler::OnKineticScroll(const ReboundScroll::ScrollArgs &param)
{
	int nOldFirstItem = FirstItem;
	float fOldOffset = FirstItemOffset;
	float fItemSize = ItemSize;
	float fPageSize = PageSize;

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


	EnumWorkMode nWorkMode = WorkMode;
	ScrollArgs pse;
	pse.m_nFirstItem = FirstItem;
	pse.m_fFirstItemOffset = FirstItemOffset;
	pse.m_nWorkMode = nWorkMode;
	ScrollEvent.dispatch(pse);
	int nFirstItem = FirstItem;
	if(nOldFirstItem != nFirstItem)
	{
		FirstItemChangedArgs p;
		p.newItem = nFirstItem;
		p.oldItem = nOldFirstItem;
		FirstItemChangedEvent.dispatch(p);
	}
}

void ReboundScrollCtrler::OnKineticScrollEnd(const ReboundScroll::ScrollEndArgs &param)
{
	m_bScrollByIncDec = false;
	ScrollEndArgs p;
	ScrollEndEvent.dispatch(p);
}
