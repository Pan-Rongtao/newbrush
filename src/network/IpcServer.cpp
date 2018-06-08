#include "network/IpcServer.h"
#include "IpcServer_Internal.h"

using nb::Network::IpcServer;
using nb::Network::IpcServerEvent;

IpcServer::IpcServer(const nb::System::String &sIp, unsigned int nPort)
{
	m_pInternal = new IpcServer_Internal(sIp.ToUtf8().GetData(), nPort);
}

IpcServer::~IpcServer()
{
	delete m_pInternal;
}

nb::System::String IpcServer::GetIp() const
{
	return m_pInternal->GetIp().data();
}

unsigned int IpcServer::GetBindingPort() const
{
	return m_pInternal->GetBindingPort();
}

bool IpcServer::Startup()
{
	return m_pInternal->Startup();
}

void IpcServer::Shutdown()
{
	return m_pInternal->Shutdown();
}

void IpcServer::Peek()
{
	m_pInternal->Peek();
}

void IpcServer::SetTimeoutSpan(int ms)
{
	m_pInternal->SetTimeoutSpan(ms);
}

int IpcServer::GetTimeoutSpan() const
{
	return m_pInternal->GetTimeoutSpan();
}

void IpcServer::SetEventInterface(IpcServerEvent *pInterface)
{
	m_pInternal->SetEventInterface(pInterface);
}
