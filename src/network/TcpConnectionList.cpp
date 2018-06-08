#include <algorithm>
#include "TcpConnectionList.h"

using nb::Network::TcpConnectionList;
using nb::Network::Socket;
using nb::Network::Packet;
using nb::Network::ReceivePacket;
using nb::Network::TcpConnection;
using nb::Network::TcpConnectionListEvent;

TcpConnectionList::TcpConnectionList()
: m_pEventInterface(NULL)
, m_nWaitTimeout(-1)
{
}

TcpConnectionList::~TcpConnectionList()
{
	Clear();
}

void TcpConnectionList::Append(Socket *socket)
{
	m_Lock.Lock();
	TcpConnection *Conn = new TcpConnection(socket);
	Conn->SetTimeoutSpan(m_nWaitTimeout);
	Conn->SetEventInterface(this);
	Conn->Work();
	m_vtConnection.push_back(Conn);
	m_Lock.Unlock();
}

void TcpConnectionList::Remove(TcpConnection *Conn)
{
	m_Lock.Lock();
	for(int i = 0; i != m_vtConnection.size(); ++i)
	{
		if(m_vtConnection[i] == Conn)
		{
			Conn->UnWork();
			delete Conn;
			m_vtConnection.erase(m_vtConnection.begin() + i);
			break;
		}
	}
	m_Lock.Unlock();
}

void TcpConnectionList::Clear()
{
	m_Lock.Lock();
	for(int i = 0; i != m_vtConnection.size(); ++i)
	{
		m_vtConnection[i]->UnWork();
		delete m_vtConnection[i];
	}
	m_vtConnection.clear();
	m_Lock.Unlock();
}

int TcpConnectionList::GetCount()
{
	m_Lock.Lock();
	int nRet = (int)m_vtConnection.size();
	m_Lock.Unlock();
	return nRet;
}

TcpConnection *TcpConnectionList::GetAt(int index)
{
	m_Lock.Lock();
	TcpConnection *ret = m_vtConnection[index];
	m_Lock.Unlock();
	return ret;
}

void TcpConnectionList::PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs)
{
	m_Lock.Lock();
	for(int i = 0; i != m_vtConnection.size(); ++i)
	{
		TcpConnection *Conn = m_vtConnection[i];
		std::vector<Packet> vtPkgs;
		Conn->PeekPacket(vtPkgs);
		for(int k = 0; k != vtPkgs.size(); ++k)
		{
			vtRpkgs.push_back(ReceivePacket(Conn, vtPkgs[k]));
		}
	}
	m_Lock.Unlock();
}

void TcpConnectionList::SetTimeoutSpan(int ms)
{
	m_Lock.Lock();
	m_nWaitTimeout = ms;
	for(int i = 0; i != m_vtConnection.size(); ++i)
	{
		TcpConnection *Conn = m_vtConnection[i];
		Conn->SetTimeoutSpan(ms);
	}
	m_Lock.Unlock();
}

int TcpConnectionList::GetTimeoutSpan() const
{
	return m_nWaitTimeout;
}

Packet TcpConnectionList::Send(TcpConnection *Conn, const Packet &pkg)
{
	m_Lock.Lock();
	Packet ret;
	for(int i = 0; i != m_vtConnection.size(); ++i)
	{
		if(m_vtConnection[i] == Conn)
		{
			ret = Conn->Request(pkg);
			break;
		}
	}
	m_Lock.Unlock();
	return ret;
}

void TcpConnectionList::Broadcast(const Packet &pkg)
{
	m_Lock.Lock();
	for(int i = 0; i != m_vtConnection.size(); ++i)
	{
		TcpConnection *Conn = m_vtConnection[i];
		Conn->Request(pkg);
	}
	m_Lock.Unlock();
}

void TcpConnectionList::SetEventInterface(TcpConnectionListEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void TcpConnectionList::TcpConnection_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequests, std::vector<Packet> &vtFeedbacks)
{
	if(m_pEventInterface)
		m_pEventInterface->TcpConnectionList_OnUrgentPacketHandleNeeded(Conn, vtRequests, vtFeedbacks);
}

void TcpConnectionList::TcpConnection_OnDisconnected(TcpConnection *Conn)
{
	Remove(Conn);
}