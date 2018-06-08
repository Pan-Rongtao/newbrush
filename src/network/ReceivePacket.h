#pragma once
#include "Packet.h"
#include "TcpConnection.h"

namespace nb{ namespace Network {

class  ReceivePacket
{
public:
	ReceivePacket(TcpConnection *Conn, const Packet &pkg);

	TcpConnection *GetConnection() const;
	const Packet &GetPacket() const;

private:
	TcpConnection		*m_pConnection;
	Packet				m_Packet;
};

}}