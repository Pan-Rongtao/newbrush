#pragma once
#include "network/IpcClient.h"
#include "TestSession.h"
#include "core/Object.h"

class TestIpcClient : public nbObject
{
public:
	TestIpcClient();

	void Send();

	void OnEvent(TestSession::TestEventParam &param);

private:
	
	TestSession				*m_pss;
	nb::Network::IpcClient	m_IpcClient;
};