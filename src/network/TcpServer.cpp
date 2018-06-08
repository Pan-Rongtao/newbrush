#include "TcpServer.h"
#include "TcpServer_Internal.h"

using nb::Network::TcpServer;
using nb::Network::TcpServerEvent;
using nb::Network::TcpConnection;
using nb::Network::Packet;
using nb::Network::ReceivePacket;

TcpServer::TcpServer(const std::string &sIp, unsigned int nPort)
{
	m_pInternal = new TcpServer_Internal(sIp, nPort);
}

TcpServer::~TcpServer()
{
	delete m_pInternal;
}

bool TcpServer::Startup()
{
	return m_pInternal->Startup();
}

void TcpServer::Shutdown()
{
	m_pInternal->Shutdown();
}

Packet TcpServer::SendData(TcpConnection *Conn, const char *pData, int nLenBytes)
{
	return m_pInternal->Send(Conn, pData, nLenBytes);
}

void TcpServer::PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs)
{
	m_pInternal->PeekClientPackets(vtRpkgs);
}

void TcpServer::SetTimeoutSpan(int ms)
{
	m_pInternal->SetTimeoutSpan(ms);
}

int TcpServer::GetTimeoutSpan() const
{
	return m_pInternal->GetTimeoutSpan();
}

std::string TcpServer::GetIp() const
{
	return m_pInternal->GetIp();
}

unsigned int TcpServer::GetBindingPort() const
{
	return m_pInternal->GetBindingPort();
}

void TcpServer::SetEventInterface(TcpServerEvent *pEventInterface)
{
	m_pInternal->SetEventInterface(pEventInterface);
}

void TcpServer::RemoveConnection(TcpConnection *Conn)
{
	m_pInternal->RemoveConnection(Conn);
}