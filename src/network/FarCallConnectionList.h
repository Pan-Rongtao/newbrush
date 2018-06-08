#pragma once
#include <vector>
#include "FarCallConnection.h"

namespace nb{ namespace Network {

class FarCallConnection;
class FarCallConnectionEvent;
class FarCallConnectionListEvent;
class FarCallConnectionList
{
public:
	FarCallConnectionList();
	virtual ~FarCallConnectionList();

	void Push(TcpConnection *Conn, TcpServer *tcpServer);
	void Remove(TcpConnection *Conn);

	FarCallConnectionPtr FindFarCall(TcpConnection *Conn);

	Packet DecodePacket(TcpConnection *Conn, const Packet &pkg);

	void SetEventInterface(FarCallConnectionListEvent *pInterface);

private:
	FarCallConnectionList(const FarCallConnectionList &other) {}
	void operator = (const FarCallConnectionList &other) {}

	std::vector<FarCallConnectionPtr>	m_vtFarCallConnections;
};

}}