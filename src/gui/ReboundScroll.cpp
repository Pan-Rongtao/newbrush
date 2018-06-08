#include "ReboundScroll.h"
#include "system/System.h"

using namespace nb::Gui;

using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(ReboundScroll, nbObject, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, IsRuning, aBool, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, UseRebound, aBool, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, TopLeftReboundPos, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, BottomRightReboundPos, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, ReboundStopLength, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, ReboundAccel, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, ContentHeight, aFloat, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ReboundScroll, PageHeight, aFloat, NULL);

ReboundScroll::ReboundScroll()
: m_bElastic(false)
, m_bElasticDec(false)
, m_fElasticSpace(0.0f)
{
	IsRuning = false;
	UseRebound = true;
	ReboundAccel = 10000.0f;
	TopLeftReboundPos = -1.0f;
	BottomRightReboundPos = -1.0f;
	ReboundStopLength = -1.0f;

	m_pKineticMove = new KineticMove();
	m_pKineticMove->MoveDistanceEvent.Add(this, &ReboundScroll::OnKineticMove);
	m_pKineticMove->MoveEndEvent.Add(this, &ReboundScroll::OnKineticMoveEnd);
}

ReboundScroll::~ReboundScroll()
{
}

void ReboundScroll::OnKineticMove(KineticMove::MoveDistanceEventParam &param)
{
	ScrollEventParam p;
	p.m_nSpace = param.m_nSpace;
	this->ScrollEvent.Dispatch(p);

	bool bUseRebound = (Boolx)UseRebound;
	float fTopLeftReboundPos = (Float)TopLeftReboundPos;
	float fBottomRightReboundPos = (Float)BottomRightReboundPos;
	float fReboundAccel = (Float)ReboundAccel;
	float fReboundStopLength = (Float)ReboundStopLength;
	float fPageHeight = (Float)PageHeight;

	if(!bUseRebound) return;

	if(m_bScrollDown)
	{
		//向上滚动
		if(!m_bElastic)
		{
			if(param.m_nSpace > -fTopLeftReboundPos)
			{
				m_pKineticMove->SetAccel(-fReboundAccel);
			}
			if(fReboundStopLength >= 0)
			{
				if(param.m_nSpace >= -fTopLeftReboundPos + fReboundStopLength)
				{
					m_pKineticMove->SetAccel(-1e+38f);//-1e+256);
				}
			}
		}
		else
		{
			if(!m_bElasticDec)
			{
				if(param.m_nSpace < -fTopLeftReboundPos+2*(m_fElasticSpace-(-fTopLeftReboundPos))/3)
				{
					float fSpeed = m_pKineticMove->GetSpeed();

					m_pKineticMove->Stop();

					float f = -fTopLeftReboundPos-param.m_nSpace;
				//	if(f <= -0.00001 || f >= 0.00001)
					if(f <= -0.00001)
					{
						//依据运行距离和加速度，重新计算初速度
						float fAccel;
						fAccel = KineticMove::ComputeAccel(f, fSpeed);

						//启动滚动
						m_pKineticMove->Start(fAccel, fSpeed, (float)param.m_nSpace);
					}
					else
					{
						OnScrollEndEvent();
					}
					m_bElasticDec = true;
				}
			}
		}
	}
	else
	{
		//向下滚动
		if(!m_bElastic)
		{
			if(param.m_nSpace+fBottomRightReboundPos < fPageHeight)
			{
				m_pKineticMove->SetAccel(fReboundAccel);
			}

			if(fReboundStopLength >= 0)
			{
				if(param.m_nSpace+fBottomRightReboundPos < fPageHeight - fReboundStopLength)
				{
					m_pKineticMove->SetAccel(1e+38f);//1e+256);
				}
			}
		}
		else
		{
			if(!m_bElasticDec)
			{
				float fRight = m_fElasticSpace + fBottomRightReboundPos;
				if(param.m_nSpace + fBottomRightReboundPos > fRight + (fPageHeight-fRight)/3)
				{
					float fSpeed = m_pKineticMove->GetSpeed();

					m_pKineticMove->Stop();

					float f = fPageHeight - (param.m_nSpace + fBottomRightReboundPos);
				//	if(f <= -0.00001 || f >= 0.00001)
					if(f >= 0.00001)
					{
						//依据运行距离和加速度，重新计算初速度
						float fAccel;
						fAccel = KineticMove::ComputeAccel(f, fSpeed);

						//启动滚动
						m_pKineticMove->Start(fAccel, fSpeed, (float)param.m_nSpace);
					}
					else
					{
						OnScrollEndEvent();
					}
					m_bElasticDec = true;
				}
			}
		}
	}
}

void ReboundScroll::OnKineticMoveEnd(KineticMove::MoveEndEventParam &param)
{
	bool bUseRebound = (Boolx)UseRebound;
	float fTopLeftReboundPos = (Float)TopLeftReboundPos;
	float fBottomRightReboundPos = (Float)BottomRightReboundPos;
	float fPageHeight = (Float)PageHeight;
	if(!bUseRebound)
	{
		OnScrollEndEvent();
		return;
	}


	if(!m_bElastic)
	{
		if(m_bScrollDown)
		{
			if(param.m_fSpace > -fTopLeftReboundPos)
			{
				m_fElasticSpace = param.m_fSpace;

				//启动回弹
				m_pKineticMove->Start((-fTopLeftReboundPos - param.m_fSpace)*20, 0, param.m_fSpace);

				m_bElasticDec = false;
				m_bElastic = true;

				return;
			}
		}
		else
		{
			if(param.m_fSpace + fBottomRightReboundPos < fPageHeight)
			{
				m_fElasticSpace = param.m_fSpace;

				//启动滚动
				m_pKineticMove->Start(-(param.m_fSpace + fBottomRightReboundPos - fPageHeight)*20, 0, param.m_fSpace);

				m_bElasticDec = false;
				m_bElastic = true;

				return;
			}
		}
	}

	OnScrollEndEvent();
}

inline void ReboundScroll::OnScrollEndEvent()
{
	IsRuning = false;
	ScrollEndEventParam p;
	this->ScrollEndEvent.Dispatch(p);
}

void ReboundScroll::Start(float fAccel, float fStartSpeed, float fStartPos, float fPageHeight, float fContentHeight)
{
	ContentHeight = nb::System::Max(fContentHeight, fPageHeight);
	PageHeight = fPageHeight;

	m_bScrollDown = fStartSpeed > 0 ? true : false;

	TopLeftReboundPos = 0.0f;
	BottomRightReboundPos = ContentHeight;

	m_bElastic = false;
	m_pKineticMove->Start(fAccel, fStartSpeed, fStartPos);

	IsRuning = true;
}

void ReboundScroll::OffsetStartPos(float fStartPosOffset)
{
//	if(m_bElastic) return;		// 处于反弹过程中，设置将无效

	m_pKineticMove->OffsetStartPos(fStartPosOffset);

	BottomRightReboundPos = (Float)BottomRightReboundPos - fStartPosOffset;
	if(m_bElastic) 
	{
		m_fElasticSpace += fStartPosOffset;
	}
}

void ReboundScroll::Stop()
{
	m_pKineticMove->Stop();

	IsRuning = false;
}
