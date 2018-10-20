#include "GestureAnalyse.h"

using namespace nb::core;
using namespace nb::gui;

GestureAnalyse::GestureAnalyse()
: m_bPress(false)
, m_bOffsetActive(false)
{
	m_timeLast = Time::now();
	m_timePrev = Time::now();
	m_timer.setSingleShot(true);
	m_timer.TickEvent.addHandler(std::bind(&GestureAnalyse::onTick, this, std::placeholders::_1));
}

GestureAnalyse::~GestureAnalyse()
{
	ClearNodeQueue();
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

void GestureAnalyse::AddPos(Point pos)
{
/*	Node *pNode = new Node;
	pNode->m_pos = pos;
	pNode->m_time = Time::now();
	m_queueNode.push(pNode);

	Node *pHead = m_queueNode.front();
	while(pHead && (pHead->m_time - pNode->m_time).totalMilliseconds() > 200)
	{
		delete pHead;
		m_queueNode.pop();
	}*/
}
void GestureAnalyse::GesturePress(Point pos)
{
	ClearNodeQueue();
	m_bPress = true;
	m_bOffsetActive = false;


	m_ptPress = pos;

	Node *pNode = new Node;
	pNode->m_pos = pos;
	pNode->m_time = Time::now();
	m_queueNode.push(pNode);

	m_timer.start(25);
}

void GestureAnalyse::GestureMove(Point pos)
{
	if(!m_bPress) return;

	AddPos(pos);

	Time timePrev = m_timeLast;
	Point ptPrev = m_ptLast;

	m_timeLast = Time::now();
	m_ptLast = pos;

	int msecs = (int)(m_timePrev - m_timeLast).totalMilliseconds();
//	if(msecs > 50)
	{
		m_timePrev = timePrev;
		m_ptPrev = ptPrev;
	}
	
	m_timer.stop();
	m_timer.start(25);
}

void GestureAnalyse::GestureRelease(Point pos)
{
	m_bPress = false;

	m_timer.stop();
}

float GestureAnalyse::GetHorizontalSpeed() const
{
	int nCount = (int)m_queueNode.size();
	if(nCount <= 1) return 0;

	Node *pHead = m_queueNode.front();
	Node *pLast = m_queueNode.back();
	//int msecs = pHead->m_time.msecsTo(pLast->m_time);

	Time time = Time::now();
	int msecs = (int)(time - pHead->m_time).totalMilliseconds();
	if(msecs == 0) return 0;

	float fSpace = pLast->m_pos.x() - pHead->m_pos.x();

	return fSpace / (msecs /1000.0f) * .75f;//.35f;
}

float GestureAnalyse::GetVerticalSpeed() const
{
	int nCount = (int)m_queueNode.size();
	if(nCount <= 1) return 0;

	Node *pHead = m_queueNode.front();
	Node *pLast = m_queueNode.back();
	int msecs = (int)(pLast->m_time - pHead->m_time).totalMilliseconds();
	if(msecs == 0) return 0;

	float fSpace = pLast->m_pos.y() - pHead->m_pos.y();

	return fSpace / (msecs /1000.0f) * .35f;
}

void GestureAnalyse::onTick(const Timer::TickArgs & args)
{	
	//int nCount = (int)m_queueNode.size();

	Node *pLast = m_queueNode.back();

	AddPos(pLast->m_pos);
	m_timer.start(25);
}
