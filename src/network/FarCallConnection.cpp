#include "FarCallConnection.h"
#include "TcpServer.h"

using nb::System::FarCallSerial;
using nb::Network::FarCallConnection;
using nb::Network::TcpConnection;
using nb::Network::TcpServer;
using nb::Network::FarCallConnectionEvent;

FarCallConnection::FarCallConnection(TcpConnection *Conn, TcpServer *pTcpServer)
: m_pTcpConnection(Conn)
, m_pTcpServer(pTcpServer)
, m_pEventInterface(NULL)
{

}

TcpConnection *FarCallConnection::GetConnection() const
{
	return m_pTcpConnection;
}

void FarCallConnection::SetEventInterface(FarCallConnectionEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void FarCallConnection::SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial)
{
	if(m_pTcpConnection->IsConnected() == false)
	{
		nb::System::FarCallDataSendExceptionPtr e = new nb::System::FarCallDataSendException("connection is disconnected.");
		throw e;
	}

	Packet pkg = m_pTcpServer->SendData(m_pTcpConnection, (const char *)dataSerial.GetBuffer(), dataSerial.GetDataSize());
	if(pkg.GetHeader().GetMessageType() == Header::Message_Unknow)
	{
		nb::System::FarCallDataSendExceptionPtr e = new nb::System::FarCallDataSendException("connection is disconnected.");
		throw e;
	}
	
	//写入的是bodydata，不是整个pkg的data
	resultSerial.Write((const unsigned char *)pkg.GetBodyData(), pkg.GetHeader().GetBodySize());
}