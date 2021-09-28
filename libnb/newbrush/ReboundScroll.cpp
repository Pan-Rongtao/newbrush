#include "ReboundScroll.h"

using namespace nb;

CReboundScroll::CReboundScroll()
	: m_bIsRuning(false)
	, m_fReboundAccel(10000)
	, m_fElasticSpace(0)
	, m_bUseRebound(true)
	, m_fBottomRightReboundPos(-1)
	, m_fTopLeftReboundPos(-1)
	, m_fReboundStopLength(-1)
{
	m_pKineticMove = createRef<CKineticMove>();
	m_pKineticMove->MoveDistance += nbBindEventFunction(CReboundScroll::OnKineticScroll);
	m_pKineticMove->MoveEnd += nbBindEventFunction(CReboundScroll::OnKineticScrollEnd);
}

CReboundScroll::~CReboundScroll()
{
}

void CReboundScroll::UseRebound(bool bUse)
{
	m_bUseRebound = bUse;
}

void CReboundScroll::Start(float fAccel, float fStartSpeed, float fStartPos, float fPageHeight, float fContentHeight)
{
	m_fContentHeight = std::max(fContentHeight, fPageHeight);
	m_fPageHeight = fPageHeight;

	m_bScrollDown = fStartSpeed > 0 ? true : false;

	m_fTopLeftReboundPos = 0;
	m_fBottomRightReboundPos = m_fContentHeight;

	m_bElastic = false;
	m_pKineticMove->Start(fAccel, fStartSpeed, fStartPos);

	m_bIsRuning = true;
}

void CReboundScroll::OffsetStartPos(float fStartPosOffset)
{
//	if(m_bElastic) return;		// 处于反弹过程中，设置将无效

	m_pKineticMove->OffsetStartPos(fStartPosOffset);

	m_fBottomRightReboundPos -= fStartPosOffset;
	if(m_bElastic) m_fElasticSpace += fStartPosOffset;
}

void CReboundScroll::Stop()
{
	m_pKineticMove->Stop();

	m_bIsRuning = false;
}

void CReboundScroll::OnKineticScroll(const MoveDistanceEventArgs & e)
{
	float nSpace = e.m_space;

	SignalScrollEventArgs SignalScrollArgs;
	SignalScrollArgs.sender = this;
	SignalScrollArgs.m_space = nSpace;
	SignalScroll.invoke(SignalScrollArgs);

	if(!m_bUseRebound) return;

	if(m_bScrollDown)
	{
		//向上滚动
		if(!m_bElastic)
		{
			if(nSpace > -m_fTopLeftReboundPos)
			{
				m_pKineticMove->SetAccel(-m_fReboundAccel);
			}
			if(m_fReboundStopLength >= 0)
			{
				if(nSpace >= -m_fTopLeftReboundPos + m_fReboundStopLength)
				{
					m_pKineticMove->SetAccel(-1e+38f);//-1e+256);
				}
			}
		}
		else
		{
			if(!m_bElasticDec)
			{
				if(nSpace < -m_fTopLeftReboundPos+2*(m_fElasticSpace-(-m_fTopLeftReboundPos))/3)
				{
					float fSpeed = m_pKineticMove->GetSpeed();

					m_pKineticMove->Stop();

					float f = -m_fTopLeftReboundPos-nSpace;
				//	if(f <= -0.00001 || f >= 0.00001)
					if(f <= -0.00001)
					{
						//依据运行距离和加速度，重新计算初速度
						float fAccel;
						fAccel = CKineticMove::ComputeAccel(f, fSpeed);

						//启动滚动
						m_pKineticMove->Start(fAccel, fSpeed, nSpace);
					}
					else
					{
						ScrollEndEvent();
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
			if(nSpace+m_fBottomRightReboundPos < m_fPageHeight)
			{
				m_pKineticMove->SetAccel(m_fReboundAccel);
			}

			if(m_fReboundStopLength >= 0)
			{
				if(nSpace+m_fBottomRightReboundPos < m_fPageHeight - m_fReboundStopLength)
				{
					m_pKineticMove->SetAccel(1e+38f);//1e+256);
				}
			}
		}
		else
		{
			if(!m_bElasticDec)
			{
				float fRight = m_fElasticSpace+m_fBottomRightReboundPos;
				if(nSpace+m_fBottomRightReboundPos > fRight + (m_fPageHeight-fRight)/3)
				{
					float fSpeed = m_pKineticMove->GetSpeed();

					m_pKineticMove->Stop();

					float f = m_fPageHeight-(nSpace+m_fBottomRightReboundPos);
				//	if(f <= -0.00001 || f >= 0.00001)
					if(f >= 0.00001)
					{
						//依据运行距离和加速度，重新计算初速度
						float fAccel;
						fAccel = CKineticMove::ComputeAccel(f, fSpeed);

						//启动滚动
						m_pKineticMove->Start(fAccel, fSpeed, nSpace);
					}
					else
					{
						ScrollEndEvent();
					}
					m_bElasticDec = true;
				}
			}
		}
	}
}

void CReboundScroll::OnKineticScrollEnd(const MoveEndEventArgs &e)
{
	float fSpace = e.m_space;

	if(!m_bUseRebound)
	{
		ScrollEndEvent();
		return;
	}


	if(!m_bElastic)
	{
		if(m_bScrollDown)
		{
			if(fSpace > -m_fTopLeftReboundPos)
			{
				m_fElasticSpace = fSpace;

				//启动回弹
				m_pKineticMove->Start((-m_fTopLeftReboundPos - fSpace)*20, 0, fSpace);

				m_bElasticDec = false;
				m_bElastic = true;

				return;
			}
		}
		else
		{
			if(fSpace+m_fBottomRightReboundPos < m_fPageHeight)
			{
				m_fElasticSpace = fSpace;

				//启动滚动
				m_pKineticMove->Start(-(fSpace + m_fBottomRightReboundPos - m_fPageHeight)*20, 0, fSpace);

				m_bElasticDec = false;
				m_bElastic = true;

				return;
			}
		}
	}

	ScrollEndEvent();
}

inline void CReboundScroll::ScrollEndEvent()
{
	m_bIsRuning = false;
	SignalScrollEndEventArgs e;
	e.sender = this;
	SignalScrollEnd.invoke(e);
}

bool CReboundScroll::IsRunning() const
{
	return m_bIsRuning;
}