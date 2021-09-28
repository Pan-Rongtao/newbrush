#include "GestureAnalyse.h"

using namespace nb;

CGestureAnalyse::CGestureAnalyse()
	: m_bPress(false)
	, m_bOffsetActive(false)
{
	m_timeLast = getMilliseconds();
	m_timePrev = getMilliseconds();

	m_timer.setSingleShot(true);
	m_timer.Tick += nbBindEventFunction(CGestureAnalyse::onTick);
}

CGestureAnalyse::~CGestureAnalyse()
{
	ClearNodeQueue();
}

void CGestureAnalyse::onTick(const EventArgs & e)
{
	int nCount = m_queueNode.size();
	
	ref<Node> pLast = m_queueNode.back();
	
	AddPos(pLast->m_pos);
	m_timer.start(25);
}

inline void CGestureAnalyse::ClearNodeQueue()
{
	int nCount = m_queueNode.size();
	for (int i = 0; i < nCount; i++)
		m_queueNode.pop();
}

void CGestureAnalyse::GesturePress(Point pos)
{
	ClearNodeQueue();
	m_bPress = true;
	m_bOffsetActive = false;


	m_ptPress = pos;

	ref<Node> pNode = createRef<Node>();
	pNode->m_pos = pos;
	pNode->m_time = getMilliseconds();
	m_queueNode.push(pNode);

	m_timer.start(25);
}

void CGestureAnalyse::AddPos(Point pos)
{
	auto pNode = createRef<Node>();
	pNode->m_pos = pos;
	pNode->m_time = getMilliseconds();
	m_queueNode.push(pNode);

	while((pNode->m_time - m_queueNode.front()->m_time) > 200)
	{
		m_queueNode.pop();
	}
}

void CGestureAnalyse::GestureMove(Point pos)
{
	if(!m_bPress) return;

	AddPos(pos);

	uint64_t timePrev = m_timeLast;
	Point ptPrev = m_ptLast;

	m_timeLast = getMilliseconds();
	m_ptLast = pos;

	uint64_t msecs = m_timeLast - m_timePrev;
//	if(msecs > 50)
	{
		m_timePrev = timePrev;
		m_ptPrev = ptPrev;
	}
	
	m_timer.stop();
	m_timer.start(25);
}

void CGestureAnalyse::GestureRelease(Point pos)
{
	m_bPress = false;

	m_timer.stop();
}

float CGestureAnalyse::GetVerticalSpeed() const
{
	int nCount = m_queueNode.size();
	if(nCount <= 1) return 0;

	auto pHead = m_queueNode.front();
	auto pLast = m_queueNode.back();
	//int msecs = pHead->m_time.msecsTo(pLast->m_time);

	uint64_t time = getMilliseconds();
	uint64_t msecs = time - pHead->m_time;
	if(msecs == 0) return 0;

	float fSpace = pLast->m_pos.y - pHead->m_pos.y;

	return float(fSpace / (msecs /1000.0) * .75);//.35;
}

float CGestureAnalyse::GetHorizontalSpeed() const
{
	int nCount = m_queueNode.size();
	if(nCount <= 1) return 0;

	auto pHead = m_queueNode.front();
	auto pLast = m_queueNode.back();
	uint64_t msecs = pLast->m_time - pHead->m_time;
	if(msecs == 0) return 0;

	float fSpace = pLast->m_pos.x - pHead->m_pos.x;

	return float(fSpace / (msecs /1000.0) * .35);
}

Point CGestureAnalyse::GetPressPos() const
{
	return m_ptPress;
}

//void CGestureAnalyse::SetOffsetActiveSpace(float x, float y)
//{
//}