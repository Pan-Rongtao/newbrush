#include "TestIpcServer.h"
#include "system/Platform.h"

using namespace nb::Core;
using namespace nb::System;
using namespace nb::Network;


TestIpcServer::TestIpcServer()
: m_IpcServer("127.0.0.2", 8888)
{
//	m_IpcServer.SetTimeoutSpan(10 * 1000);
	bool b = m_IpcServer.Startup();
	printf("startup server %s. ip[%s], port[%d]\n", b ? "success" : "fail", m_IpcServer.GetIp().ToUtf8().GetData(), m_IpcServer.GetBindingPort());
	m_IpcServer.SetEventInterface(this);
}

TestIpcServer::~TestIpcServer()
{

}

int page = 10000;
void TestIpcServer::SendOne()
{
	AbcConnectObject::TestEventParam testEventParam;
	testEventParam.m_a = 1;
	testEventParam.m_b = 2.3f;
	testEventParam.m_r1 = 5;
	testEventParam.m_r2 = 6.8f;
	try
	{
		for(int i = 0; i != SessionMgr::GetInstance()->GetSessionCount(); ++i)
		{
			TestSessionSv *pSession = SessionMgr::GetInstance()->GetSession(i);
		//	printf("session[%d] Event[%d] send begin\r\n", i, pSession->GetSendEventCount());
			pSession->TestEvet.Send(testEventParam);
		//	printf("session[%d] Event[%d] send end\r\n", i, pSession->GetSendEventCount());
			pSession->AddSendEventCount();
		}
		for(int i = 0; i != SessionMgr::GetInstance()->GetSessionCount(); ++i)
		{
			TestSessionSv *pSession = SessionMgr::GetInstance()->GetSession(i);
			if(pSession->GetSendEventCount() % page == 0)
				printf("session[%d] send pkgs=%d\r\n", i, pSession->GetSendEventCount());
		}
	}
	catch(ExceptionPtr &e)
	{

	}

}

void TestIpcServer::SendEvents()
{
	while(1)
	{
		SendOne();
		m_IpcServer.Peek();
		SendOne();
	}
}

void TestIpcServer::IpcServer_OnNewConnection(const nb::System::String &name, nb::System::FarCallServer *pFarCallServer)
{
	pFarCallServer->RegServer<TestSessionSv>("Abc");
}

void TestIpcServer::IpcServer_OnConnectionDisconnected(nb::System::FarCallServer *pFarCallServer)
{
	printf("connection has disconnected!!!!!!\r\n");
}
