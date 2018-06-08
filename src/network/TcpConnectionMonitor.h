#pragma once
#include "system/Thread.h"
#include "system/CriticalSection.h"
#include "TcpConnection.h"
#include "ServerSocket.h"

namespace nb{ namespace Network{

class TcpConnectionMonitorEvent;
class TcpConnectionMonitor : public nb::System::Thread
{
public:
	TcpConnectionMonitor(const std::string &sServerIp, int nServerPort);
	~TcpConnectionMonitor();

	bool Start();
	void Stop();

	bool IsRunning();

	std::string GetServerIp();
	unsigned int GetServerPort();
	void SetEventInterface(TcpConnectionMonitorEvent *pInterface);

private:
	TcpConnectionMonitor(const TcpConnectionMonitor &other);
	void operator = (const TcpConnectionMonitor &other);

	virtual void Run();

	std::string					m_sIp;
	unsigned					m_nPort;
	bool						m_bStopFlag;
	nb::System::CriticalSection	m_Lock;
	ServerSocket				*m_pServerSocket;
	TcpConnectionMonitorEvent	*m_pEventInterface;
};

class TcpConnectionMonitorEvent
{
public:
	//此消息只是socket层面的连接
	virtual void TcpConnectionMonitor_OnNewConnection(Socket *socket) {(void)socket;}
};

}}
