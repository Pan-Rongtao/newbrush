#pragma once

#include "../testnetwork_c/TestSession.h"
#include <set>
#include <vector>

class TestSessionSv;
class SessionMgr
{
public:
	static SessionMgr *GetInstance();

	TestSessionSv *GetSession(int index) {return m_Sessions[index];}

	void Push(TestSessionSv *p)
	{
		m_Sessions.push_back(p);
	}
	void Remove(TestSessionSv *p)
	{
		for(int i = 0; i != m_Sessions.size(); ++i)
		{
			if(m_Sessions[i] == p)
			{
				m_Sessions.erase(m_Sessions.begin() + i);
				break;
			}
		}
	}

	int GetSessionCount() const 
	{
		return (int)m_Sessions.size();
	}


private:
	std::vector<TestSessionSv *>	m_Sessions;

private:
	static SessionMgr *g_sInstance;
};

class TestSessionSv : public TestSession
{
public:
	TestSessionSv();
	virtual ~TestSessionSv();
//	static TestSessionSv *GetInstance();
//	void Release();

//	TestSessionSv *m_child;
	void AddSendEventCount()
	{
		++m_nSendCount;
	}

	int GetSendEventCount() const
	{
		return m_nSendCount;
	}

	GenericVariant TestSv(TestSession::TestParam &param)
	{
		TestSessionSv *pSession = SessionMgr::GetInstance()->GetSession(0);
		TestEventParam p;
		p.m_a = 1111;
		if(pSession)
		{
			try{
			pSession->TestEvet.Send(p);
			}
			catch(...)
			{

			}
		}
		return 20;
	}

private:
	int						m_value;

	int m_nSendCount;
//	static nbObjectPtrDerive<TestSessionSv, nbObjectPtr> g_sInstance;
};