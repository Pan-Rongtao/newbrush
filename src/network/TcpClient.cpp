#include "TcpClient.h"
#include "TcpClient_Internal.h"

using nb::Network::TcpClient;
using nb::Network::TcpClient_Internal;
using nb::Network::Packet;
using nb::Network::TcpClientEvent;

TcpClient::TcpClient()
: m_PacketID(1)
{
	m_pInternal = new TcpClient_Internal();
}
TcpClient::TcpClient(const std::string &name)
{
	m_pInternal = new TcpClient_Internal(name);
}
TcpClient::~TcpClient()
{
	delete m_pInternal;
}

bool TcpClient::Login(const std::string &sHostIp, int nPort)
{
	return m_pInternal->Login(sHostIp, nPort);
}

void TcpClient::Logout()
{
	m_pInternal->Logout();
}

bool TcpClient::IsConnected() const
{
	return m_pInternal->IsConnected();
}

std::string TcpClient::GetName() const
{
	return m_pInternal->GetName();
}

std::string TcpClient::GetHostIp() const
{
	return m_pInternal->GetHostIp();
}

unsigned int TcpClient::GetHostPort() const
{
	return m_pInternal->GetHostPort();
}

Packet TcpClient::SendData(const char *pData, int nLenBytes)
{
	return m_pInternal->Request(SignalBinaryStream(m_PacketID++, Header::Priority_Urgent, pData, nLenBytes));
}

void TcpClient::PeekPacket(std::vector<Packet> &vtPkgs)
{
	m_pInternal->PeekPacket(vtPkgs);
}

void TcpClient::PeekFeedback(std::vector<Packet> &feedbackPkgs)
{
	m_pInternal->PeekFeedback(feedbackPkgs);
}

void TcpClient::SetTimeoutSpan(int ms)
{
	m_pInternal->SetTimeoutSpan(ms);
}

int TcpClient::GetTimeoutSpan() const
{
	return m_pInternal->GetTimeoutSpan();
}

void TcpClient::SetEventInterface(TcpClientEvent *pInterface)
{
	m_pInternal->SetEventInterface(pInterface);
}