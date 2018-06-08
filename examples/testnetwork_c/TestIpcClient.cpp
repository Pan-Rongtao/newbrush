#include "TestIpcClient.h"
#include "system/Platform.h"

using namespace nb::System;
using namespace nb::Network;

TestSession::TestParam testparam;

int nSendCount = 1;
TestIpcClient::TestIpcClient()
: m_IpcClient()
{
//	m_IpcClient.SetTimeoutSpan(10 * 1000);
	bool b = m_IpcClient.Login("127.0.0.2", 8888);
	printf("login %s. ip[%s], port[%d]\n", b ? "success" : "fail", m_IpcClient.GetHostIp().ToUtf8().GetData(), m_IpcClient.GetHostPort());
	m_pss = new TestSession(m_IpcClient.GetFarCallClient());
	m_IpcClient.GetFarCallClient()->Flush();
	m_pss->TestEvet.Add(this, &TestIpcClient::OnEvent);
	m_IpcClient.GetFarCallClient()->Flush();
}

void TestIpcClient::OnEvent(TestSession::TestEventParam &param)
{
	param.m_r1  = 1;
	param.m_r2 = 2;
//	return;
//	printf("TestIpcClient::OnEvent[%d|%.2f|%d|%.2f]\r\n", param.m_a, param.m_b, param.m_r1, param.m_r2);
	if(nSendCount % 3 == 1)
	{
		++nSendCount;
		int z = m_pss->Test(testparam);
	}
//	z = m_pss->Test(testparam);
//	printf("packet[%d] feedback z=%d-----------------------\r\n", i, z);
//	++nSendCount;
}

int nLastTick = 0;
void TestIpcClient::Send()
{
	testparam.a = 1;
	testparam.b = 2;
	while(1)
	{
		m_IpcClient.Peek();

//continue;
//		printf("packet[%d] start send!!!!!*****!\r\n", nSendCount);
		int x = m_pss->Test(testparam);
	//	printf("packet[%d] feedback x=%d-----------------------\r\n", i, x);
		++nSendCount;
		if(nSendCount % 10000 == 0)
		{
			printf("client send pkgs=%d, cost time[%d]\r\n", nSendCount, nb::System::Platform::GetTickCount() - nLastTick);
			nLastTick = nb::System::Platform::GetTickCount();
		}
	//	printf("packet[%d] start send!!!!!&&&&&!\r\n", i);
		int y = m_pss->Test(testparam);
	//	printf("packet[%d] feedback y=%d-----------------------\r\n", i, y);
		++nSendCount;
		if(nSendCount % 10000 == 0)
		{
			printf("client send pkgs=%d, cost time[%d]\r\n", nSendCount, nb::System::Platform::GetTickCount() - nLastTick);
			nLastTick = nb::System::Platform::GetTickCount();
		}
	}
}
