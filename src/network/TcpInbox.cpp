#include "TcpInbox.h"

using nb::Network::TcpInbox;
using nb::Network::Socket;
using nb::Network::Packet;
using nb::Network::TcpInboxEvent;

TcpInbox::TcpInbox()
: m_pEventInterface(NULL)
{
	m_MessageMonitor.SetEventInterface(this);
}

TcpInbox::~TcpInbox()
{
}

void TcpInbox::SetSocket(Socket *socket)
{
	m_MessageMonitor.SetSocket(socket);
}

void TcpInbox::Work()
{
	m_MessageMonitor.Start();
}

void TcpInbox::UnWork()
{
	m_MessageMonitor.Stop();
}

void TcpInbox::PopPackets(std::vector<Packet> &vtPkgs)
{
	m_PacketsLock.Lock();
	vtPkgs = m_vtPkgs;
	m_vtPkgs.erase(m_vtPkgs.begin(), m_vtPkgs.begin() + vtPkgs.size());;
	m_PacketsLock.Unlock();
}

void TcpInbox::PushPacket(const Packet &pkg)
{
	m_PacketsLock.Lock();
 	m_vtPkgs.push_back(pkg);
	m_PacketsLock.Unlock();
}

void TcpInbox::SetEventInterface(TcpInboxEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void TcpInbox::TcpMessageMonitor_OnPacketArrived(const Packet &pkg)
{
	Header::ActionProperty ap = pkg.GetHeader().GetActionProperty();
	Header::MessageType msgType = pkg.GetHeader().GetMessageType();
	if(m_pEventInterface)
		ap == Header::Property_Request ? m_pEventInterface->TcpInbox_OnRequestArrived(pkg) : m_pEventInterface->TcpInbox_OnReplyArrived(pkg);
}

void TcpInbox::TcpMessageMonitor_OnErrorPacket()
{
	UnWork();
	if(m_pEventInterface)
		m_pEventInterface->TcpInbox_OnRemoteUnknownReasonDisconnected();
}