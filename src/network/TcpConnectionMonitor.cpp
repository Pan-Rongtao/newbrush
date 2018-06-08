#include "TcpConnectionMonitor.h"

using nb::Network::TcpConnectionMonitor;
using nb::Network::ServerSocket;
using nb::Network::TcpConnectionMonitorEvent;

TcpConnectionMonitor::TcpConnectionMonitor(const std::string &sServerIp, int nServerPort)
: m_sIp(sServerIp)
, m_nPort(nServerPort)
, m_bStopFlag(true)
, m_pServerSocket(NULL)
, m_pEventInterface(NULL)
{

}

TcpConnectionMonitor::~TcpConnectionMonitor()
{

}

bool TcpConnectionMonitor::Start()
{
	m_Lock.Lock();
	if(m_pServerSocket == NULL)
		m_pServerSocket = new ServerSocket(m_sIp, m_nPort);

	bool bSuccess = m_pServerSocket->Bind();
	if(bSuccess)
	{
		m_bStopFlag = false;
		Thread::Start();
	}
	m_Lock.Unlock();
	return bSuccess;
}

void TcpConnectionMonitor::Stop()
{
	m_Lock.Lock();
	m_bStopFlag = true;
	m_Lock.Unlock();
}

bool TcpConnectionMonitor::IsRunning()
{
	m_Lock.Lock();
	bool bRet = !m_bStopFlag;
	m_Lock.Unlock();
	return bRet;
}

std::string TcpConnectionMonitor::GetServerIp()
{
	m_Lock.Lock();
	std::string sRet = m_pServerSocket->GetIp();
	m_Lock.Unlock();
	return sRet;
}

unsigned int TcpConnectionMonitor::GetServerPort()
{
	m_Lock.Lock();
	unsigned int nRet = m_pServerSocket->GetPort();
	m_Lock.Unlock();
	return nRet;
}

void TcpConnectionMonitor::SetEventInterface(TcpConnectionMonitorEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void TcpConnectionMonitor::Run()
{
	while(true)
	{
		Socket *ConnSocket = m_pServerSocket->Listen();
		//连接后客户端会把自身信息发送过来，需要接收一次信息。
		if(ConnSocket == NULL)
		{
			printf("tcp server is on error. break.\r\n");
			m_bStopFlag = true;
		}
		else
		{
			if(m_pEventInterface)
				m_pEventInterface->TcpConnectionMonitor_OnNewConnection(ConnSocket);

		}
		if(m_bStopFlag)
		{
			break;
		}

	}

	m_Lock.Lock();
	delete m_pServerSocket;
	m_pServerSocket = NULL;
	m_Lock.Unlock();
}