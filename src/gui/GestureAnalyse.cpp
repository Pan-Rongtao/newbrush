#include "GestureAnalyse.h"

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(GestureAnalyse, nbObject, NULL, NULL);
GestureAnalyse::GestureAnalyse()
: m_bPress(false)
, m_bOffsetActive(false)
{
	m_timeLast = nb::System::Time::CurrentTime();
	m_timePrev = nb::System::Time::CurrentTime();
	m_timer = new nb::System::Timer();
	m_timer->SetSingleShot(true);
	m_timer->TimeoutEvent.Add(this, &GestureAnalyse::OnTimeout);
}

GestureAnalyse::~GestureAnalyse()
{
	ClearNodeQueue();
}

void GestureAnalyse::OnTimeout(nb::System::Timer::TimeoutParam &param)
{
	//int nCount = (int)m_queueNode.size();
	
	Node *pLast = m_queueNode.back();
	
	AddPos(pLast->m_pos);
	m_timer->Start(25);
}

inline void GestureAnalyse::ClearNodeQueue()
{
	while(!m_queueNode.empty())
	{
		Node *pNode = m_queueNode.front();
		delete pNode;
		m_queueNode.pop();
	}
}

void GestureAnalyse::AddPos(nb::System::Point pos)
{
	Node *pNode = new Node;
	pNode->m_pos = pos;
	pNode->m_time = nb::System::Time::CurrentTime();
	m_queueNode.push(pNode);

	Node *pHead = m_queueNode.front();
	while(pHead && (pHead->m_time - pNode->m_time).ToMilliSeconds() > 200)
	{
		delete pHead;
		m_queueNode.pop();
	}
}
void GestureAnalyse::GesturePress(nb::System::Point pos)
{
	ClearNodeQueue();
	m_bPress = true;
	m_bOffsetActive = false;


	m_ptPress = pos;

	Node *pNode = new Node;
	pNode->m_pos = pos;
	pNode->m_time = nb::System::Time::CurrentTime();
	m_queueNode.push(pNode);

	m_timer->Start(25);
}

void GestureAnalyse::GestureMove(nb::System::Point pos)
{
	if(!m_bPress) return;

	AddPos(pos);

	nb::System::Time timePrev = m_timeLast;
	nb::System::Point ptPrev = m_ptLast;

	m_timeLast = nb::System::Time::CurrentTime();
	m_ptLast = pos;

	int msecs = (int)(m_timePrev - m_timeLast).ToMilliSeconds();
//	if(msecs > 50)
	{
		m_timePrev = timePrev;
		m_ptPrev = ptPrev;
	}
	
	m_timer->Stop();
	m_timer->Start(25);
}

void GestureAnalyse::GestureRelease(nb::System::Point pos)
{
	m_bPress = false;

	m_timer->Stop();
}

float GestureAnalyse::GetHorizontalSpeed() const
{
	int nCount = (int)m_queueNode.size();
	if(nCount <= 1) return 0;

	Node *pHead = m_queueNode.front();
	Node *pLast = m_queueNode.back();
	//int msecs = pHead->m_time.msecsTo(pLast->m_time);

	nb::System::Time time = nb::System::Time::CurrentTime();
	int msecs = (int)(time - pHead->m_time).ToMilliSeconds();
	if(msecs == 0) return 0;

	float fSpace = pLast->m_pos.GetX() - pHead->m_pos.GetX();

	return fSpace / (msecs /1000.0f) * .75f;//.35f;
}

float GestureAnalyse::GetVerticalSpeed() const
{
	int nCount = (int)m_queueNode.size();
	if(nCount <= 1) return 0;

	Node *pHead = m_queueNode.front();
	Node *pLast = m_queueNode.back();
	int msecs = (int)(pLast->m_time - pHead->m_time).ToMilliSeconds();
	if(msecs == 0) return 0;

	float fSpace = pLast->m_pos.GetY() - pHead->m_pos.GetY();

	return fSpace / (msecs /1000.0f) * .35f;
}