#include "FarCallConnectionList.h"
#include "FarCallConnection.h"

using nb::Network::FarCallConnectionList;
using nb::Network::Packet;
using nb::Network::TcpServer;
using nb::Network::TcpConnection;
using nb::Network::FarCallConnectionPtr;

FarCallConnectionList::FarCallConnectionList()
{

}

FarCallConnectionList::~FarCallConnectionList()
{
}

void FarCallConnectionList::Push(TcpConnection *Conn, TcpServer *tcpServer)
{
	FarCallConnectionPtr fcc = new FarCallConnection(Conn, tcpServer);
	m_vtFarCallConnections.push_back(fcc);
}

void FarCallConnectionList::Remove(TcpConnection *Conn)
{
	for(int i = 0; i != m_vtFarCallConnections.size(); ++i)
	{
		FarCallConnectionPtr fcc = m_vtFarCallConnections[i];
		if(fcc->GetConnection() == Conn)
		{
			m_vtFarCallConnections.erase(m_vtFarCallConnections.begin() + i);
			break;
		}
	}
}

FarCallConnectionPtr FarCallConnectionList::FindFarCall(TcpConnection *Conn)
{
	for(int i = 0; i != m_vtFarCallConnections.size(); ++i)
	{
		FarCallConnectionPtr fcc = m_vtFarCallConnections[i];
		if(fcc->GetConnection() == Conn)
		{
			return fcc;
		}
	}
	return NULL;
}

Packet FarCallConnectionList::DecodePacket(TcpConnection *Conn, const Packet &pkg)
{
	for(int i = 0; i != m_vtFarCallConnections.size(); ++i)
	{
		FarCallConnectionPtr fcc = m_vtFarCallConnections[i];
		if(fcc->GetConnection() == Conn)
		{
			nb::System::FarCallSerial ret(nb::System::FarCallSerial::Mode_Storing);
			//解析的是bodydata，不是整个pkg的data
			fcc->AcceptData((const unsigned char *)pkg.GetBodyData(), pkg.GetHeader().GetBodySize(), ret);
			return AckBinaryStream(pkg.GetHeader().GetID(), pkg.GetHeader().GetPriority(), (const char *)ret.GetBuffer(), ret.GetDataSize());
		}
	}
	return Packet();
}
