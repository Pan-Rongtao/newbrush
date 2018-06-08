#include "ReceivePacket.h"

using nb::Network::ReceivePacket;
using nb::Network::TcpConnection;
using nb::Network::Packet;

ReceivePacket::ReceivePacket(TcpConnection *Conn, const Packet &pkg)
: m_pConnection(Conn)
, m_Packet(pkg)
{

}

TcpConnection *ReceivePacket::GetConnection() const
{
	return m_pConnection;
}

const Packet &ReceivePacket::GetPacket() const
{
	return m_Packet;
}