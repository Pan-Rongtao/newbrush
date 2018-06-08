#include "TcpServer_Internal.h"
#include "TcpServer.h"

using nb::Network::TcpServer_Internal;
using nb::Network::TcpConnection;
using nb::Network::ReceivePacket;
using nb::Network::Socket;
using nb::Network::Packet;
using nb::Network::TcpServerEvent;

TcpServer_Internal::TcpServer_Internal(const std::string &sIp, unsigned int nPort)
: m_ConnectionMonitor(sIp, nPort)
, m_pEventInterface(NULL)
, m_PacketID(1)
{
	m_ConnectionMonitor.SetEventInterface(this);
	m_ConnectionList.SetEventInterface(this);
}

TcpServer_Internal::~TcpServer_Internal()
{
	Shutdown();
}

std::string TcpServer_Internal::GetIp()
{
	return m_ConnectionMonitor.GetServerIp();
}

unsigned int TcpServer_Internal::GetBindingPort()
{
	return m_ConnectionMonitor.GetServerPort();
}

bool TcpServer_Internal::Startup()
{
	return m_ConnectionMonitor.Start();
}

void TcpServer_Internal::Shutdown()
{
	if(HasStartupped())
	{
		m_ConnectionList.Clear();
		m_ConnectionMonitor.Stop();
	}
}

bool TcpServer_Internal::HasStartupped()
{
	return m_ConnectionMonitor.IsRunning() == false;
}

Packet TcpServer_Internal::Send(TcpConnection *Conn, const char *pData, int nLenBytes)
{
	return m_ConnectionList.Send(Conn, SignalBinaryStream(m_PacketID++, Conn->IsSessioning() ? Header::Priority_Urgent : Header::Priority_Normal, pData, nLenBytes));
}

void TcpServer_Internal::Broadcast(const char *pData, int nLenBytes)
{
	m_ConnectionList.Broadcast(SignalBinaryStream(m_PacketID++, Header::Priority_Normal, pData, nLenBytes));
}

void TcpServer_Internal::PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs)
{
	m_ConnectionList.PeekClientPackets(vtRpkgs);
}

void TcpServer_Internal::SetTimeoutSpan(int ms)
{
	return m_ConnectionList.SetTimeoutSpan(ms);
}

int TcpServer_Internal::GetTimeoutSpan() const
{
	return m_ConnectionList.GetTimeoutSpan();
}

bool TcpServer_Internal::IsClientOnline(TcpConnection *Conn)
{
	Packet ret = m_ConnectionList.Send(Conn, SignalHello(1, Header::Priority_Normal));
	return ret.GetHeader().GetMessageType() == Header::Message_Unknow;
}

void TcpServer_Internal::SetEventInterface(TcpServerEvent *pEvent)
{
	m_pEventInterface = pEvent;
}

void TcpServer_Internal::RemoveConnection(TcpConnection *Conn)
{
	m_ConnectionList.Remove(Conn);
}

void TcpServer_Internal::TcpConnectionMonitor_OnNewConnection(Socket *socket)
{
	m_ConnectionList.Append(socket);
}

void TcpServer_Internal::TcpConnectionList_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequests, std::vector<Packet> &vtFeedbacks)
{
	if(m_pEventInterface)
		m_pEventInterface->TcpServer_OnUrgentPacketHandleNeeded(Conn, vtRequests, vtFeedbacks);
}