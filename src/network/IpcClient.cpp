#include "network/IpcClient.h"
#include "IpcClient_Internal.h"

using nb::Network::IpcClient;

IpcClient::IpcClient()
{
	m_pInternal = new IpcClient_Internal();
}

IpcClient::IpcClient(const nb::System::String &name)
{
	m_pInternal = new IpcClient_Internal(name.ToUtf8().GetData());
}

IpcClient::~IpcClient()
{
	delete m_pInternal;
}

bool IpcClient::Login(const nb::System::String &sHostIp, unsigned int nHostPort)
{
	return m_pInternal->Login(sHostIp.ToUtf8().GetData(), nHostPort);
}

void IpcClient::Logout()
{
	m_pInternal->Logout();
}

nb::System::String IpcClient::GetName() const
{
	return m_pInternal->GetName().data();
}

nb::System::String IpcClient::GetHostIp() const
{
	return m_pInternal->GetHostIp().data();
}

unsigned int IpcClient::GetHostPort() const
{
	return m_pInternal->GetHostPort();
}

nb::System::FarCallClient *IpcClient::GetFarCallClient() const
{
	return m_pInternal->GetFarCallClient();
}

void IpcClient::Peek()
{
	m_pInternal->Peek();
}

void IpcClient::SetTimeoutSpan(int ms)
{
	m_pInternal->SetTimeoutSpan(ms);
}

int IpcClient::GetTimeoutSpan() const
{
	return m_pInternal->GetTimeoutSpan();
}
