#pragma once
#include "TcpConnection.h"
#include "system/FarCallConnectObject.h"

namespace nb{ namespace Network{

class FarCallConnectionEvent;
class TcpServer;
class FarCallConnection : public nb::System::FarCallServer
{
public:
	FarCallConnection(TcpConnection *Conn, TcpServer *pTcpServer);

	TcpConnection *GetConnection() const;

	void SetEventInterface(FarCallConnectionEvent *pInterface);
protected:
	virtual void SendDataOverride(nb::System::FarCallSerial &dataSerial, nb::System::FarCallSerial &resultSerial);

private:
	TcpConnection			*m_pTcpConnection;
	TcpServer				*m_pTcpServer;
	FarCallConnectionEvent	*m_pEventInterface;
};
typedef nbObjectPtrDerive<FarCallConnection, nb::System::FarCallServerPtr> FarCallConnectionPtr;

}}
