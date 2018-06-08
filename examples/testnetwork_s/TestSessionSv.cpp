#include "TestSessionSv.h"

// nbObjectPtrDerive<TestSessionSv, nbObjectPtr> TestSessionSv::g_sInstance;

/*
TestSessionSv *TestSessionSv::GetInstance()
{
	return g_sInstance;
}
*/
SessionMgr *SessionMgr::g_sInstance = NULL;
SessionMgr *SessionMgr::GetInstance()
{
	if(g_sInstance == NULL)
		g_sInstance = new SessionMgr();
	return g_sInstance;
}

TestSessionSv::TestSessionSv() 
: m_value(0)
, m_nSendCount(0)
{
	SessionMgr::GetInstance()->Push(this);
}

TestSessionSv::~TestSessionSv()
{
	SessionMgr::GetInstance()->Remove(this);
}
/*
void TestSessionSv::Release()
{
	g_sInstance = NULL;
}
*/