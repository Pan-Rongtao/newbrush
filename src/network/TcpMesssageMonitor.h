#pragma once
#include "system/Thread.h"
#include "Socket.h"
#include "Packet.h"

namespace nb{ namespace Network{

class TcpMessageMonitorEvent;
class TcpMessageMonitor : public nb::System::Thread
{
public:
	TcpMessageMonitor();
	~TcpMessageMonitor();

	void SetSocket(Socket *socket);

	void Start();
	void Stop();

	void SetEventInterface(TcpMessageMonitorEvent *pInterface);

private:
	TcpMessageMonitor(const TcpMessageMonitor &other);
	void operator = (const TcpMessageMonitor &other);

	virtual void Run();

	bool					m_bStopFlag;
	Socket					*m_pSocket;
	TcpMessageMonitorEvent	*m_pEventInterface;
};

class TcpMessageMonitorEvent
{
public:
	virtual void TcpMessageMonitor_OnPacketArrived(const Packet &pkg) {(void)pkg;}
	virtual void TcpMessageMonitor_OnErrorPacket() {}
};

}}
