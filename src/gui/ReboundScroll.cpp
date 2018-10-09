#include "ReboundScroll.h"
#include <algorithm>

using namespace nb::gui;
using namespace nb::core;

ReboundScroll::ReboundScroll()
: m_bElastic(false)
, m_bElasticDec(false)
, m_fElasticSpace(0.0)
{
	IsRuning = false;
	UseRebound = true;
	ReboundAccel = 10000.0f;
	TopLeftReboundPos = -1.0f;
	BottomRightReboundPos = -1.0f;
	ReboundStopLength = -1.0f;

	m_pKineticMove = std::make_shared<KineticMove>();
	m_pKineticMove->MoveDistanceEvent.addHandler(std::bind(&ReboundScroll::onKineticMove, this, std::placeholders::_1));
	m_pKineticMove->MoveEndEvent.addHandler(std::bind(&ReboundScroll::onKineticMoveEnd, this, std::placeholders::_1));
}

ReboundScroll::~ReboundScroll()
{
}

void ReboundScroll::onKineticMove(const KineticMove::MoveDistanceArgs &args)
{
	ScrollArgs p;
	p.m_nSpace = args.m_nSpace;
	this->ScrollEvent.dispatch(p);

	bool bUseRebound = UseRebound;
	float fTopLeftReboundPos = TopLeftReboundPos;
	float fBottomRightReboundPos = BottomRightReboundPos;
	float fReboundAccel = ReboundAccel;
	float fReboundStopLength = ReboundStopLength;
	float fPageHeight = PageHeight;

	if(!bUseRebound) return;

	if(m_bScrollDown)
	{
		//向上滚动
		if(!m_bElastic)
		{
			if(args.m_nSpace > -fTopLeftReboundPos)
			{
				m_pKineticMove->SetAccel(-fReboundAccel);
			}
			if(fReboundStopLength >= 0)
			{
				if(args.m_nSpace >= -fTopLeftReboundPos + fReboundStopLength)
				{
					m_pKineticMove->SetAccel(-1e+38f);//-1e+256);
				}
			}
		}
		else
		{
			if(!m_bElasticDec)
			{
				if(args.m_nSpace < -fTopLeftReboundPos+2*(m_fElasticSpace-(-fTopLeftReboundPos))/3)
				{
					float fSpeed = m_pKineticMove->GetSpeed();

					m_pKineticMove->Stop();

					float f = -fTopLeftReboundPos- args.m_nSpace;
				//	if(f <= -0.00001 || f >= 0.00001)
					if(f <= -0.00001)
					{
						//依据运行距离和加速度，重新计算初速度
						float fAccel;
						fAccel = KineticMove::ComputeAccel(f, fSpeed);

						//启动滚动
						m_pKineticMove->Start(fAccel, fSpeed, (float)args.m_nSpace);
					}
					else
					{
						onScrollEndEvent();
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
			if(args.m_nSpace+fBottomRightReboundPos < fPageHeight)
			{
				m_pKineticMove->SetAccel(fReboundAccel);
			}

			if(fReboundStopLength >= 0)
			{
				if(args.m_nSpace+fBottomRightReboundPos < fPageHeight - fReboundStopLength)
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
				if(args.m_nSpace + fBottomRightReboundPos > fRight + (fPageHeight-fRight)/3)
				{
					float fSpeed = m_pKineticMove->GetSpeed();

					m_pKineticMove->Stop();

					float f = fPageHeight - (args.m_nSpace + fBottomRightReboundPos);
				//	if(f <= -0.00001 || f >= 0.00001)
					if(f >= 0.00001)
					{
						//依据运行距离和加速度，重新计算初速度
						float fAccel;
						fAccel = KineticMove::ComputeAccel(f, fSpeed);

						//启动滚动
						m_pKineticMove->Start(fAccel, fSpeed, (float)args.m_nSpace);
					}
					else
					{
						onScrollEndEvent();
					}
					m_bElasticDec = true;
				}
			}
		}
	}
}

void ReboundScroll::onKineticMoveEnd(const KineticMove::MoveEndArgs &args)
{
	bool bUseRebound = UseRebound;
	float fTopLeftReboundPos = TopLeftReboundPos;
	float fBottomRightReboundPos = BottomRightReboundPos;
	float fPageHeight = PageHeight;
	if(!bUseRebound)
	{
		onScrollEndEvent();
		return;
	}


	if(!m_bElastic)
	{
		if(m_bScrollDown)
		{
			if(args.m_fSpace > -fTopLeftReboundPos)
			{
				m_fElasticSpace = args.m_fSpace;

				//启动回弹
				m_pKineticMove->Start((-fTopLeftReboundPos - args.m_fSpace)*20, 0, args.m_fSpace);

				m_bElasticDec = false;
				m_bElastic = true;

				return;
			}
		}
		else
		{
			if(args.m_fSpace + fBottomRightReboundPos < fPageHeight)
			{
				m_fElasticSpace = args.m_fSpace;

				//启动滚动
				m_pKineticMove->Start(-(args.m_fSpace + fBottomRightReboundPos - fPageHeight)*20, 0, args.m_fSpace);

				m_bElasticDec = false;
				m_bElastic = true;

				return;
			}
		}
	}

	onScrollEndEvent();
}

inline void ReboundScroll::onScrollEndEvent()
{
	IsRuning = false;
	ScrollEndArgs p;
	this->ScrollEndEvent.dispatch(p);
}

void ReboundScroll::start(float fAccel, float fStartSpeed, float fStartPos, float fPageHeight, float fContentHeight)
{
	ContentHeight = std::max(fContentHeight, fPageHeight);
	PageHeight = fPageHeight;

	m_bScrollDown = fStartSpeed > 0 ? true : false;

	TopLeftReboundPos = 0.0f;
	BottomRightReboundPos = ContentHeight;

	m_bElastic = false;
	m_pKineticMove->Start(fAccel, fStartSpeed, fStartPos);

	IsRuning = true;
}

void ReboundScroll::offsetStartPos(float fStartPosOffset)
{
//	if(m_bElastic) return;		// 处于反弹过程中，设置将无效

	m_pKineticMove->OffsetStartPos(fStartPosOffset);

	BottomRightReboundPos = BottomRightReboundPos - fStartPosOffset;
	if(m_bElastic) 
	{
		m_fElasticSpace += fStartPosOffset;
	}
}

void ReboundScroll::stop()
{
	m_pKineticMove->Stop();

	IsRuning = false;
}
