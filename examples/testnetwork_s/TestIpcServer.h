#pragma once
#include "network/IpcServer.h"
#include "TestSessionSv.h"
#include "../testnetwork_c/TestSession.h"


class TestIpcServer : public nb::Network::IpcServerEvent
{
public:
	TestIpcServer();
	~TestIpcServer();

	void SendOne();

	void SendEvents();


private:
	virtual void IpcServer_OnNewConnection(const nb::System::String &name, nb::System::FarCallServer *pFarCallServer);
	virtual void IpcServer_OnConnectionDisconnected(nb::System::FarCallServer *pFarCallServer);

	nb::Network::IpcServer		m_IpcServer;
};