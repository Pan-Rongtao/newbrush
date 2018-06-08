#pragma once
#include <string>
#include "TcpConnectionMonitor.h"
#include "TcpConnectionList.h"

namespace nb{ namespace Network{

class TcpServerEvent;
class TcpServer_Internal : public TcpConnectionMonitorEvent, public TcpConnectionListEvent
{
public:
	std::string GetIp();

	unsigned int GetBindingPort();

	bool Startup();

	void Shutdown();

	bool HasStartupped();

	Packet Send(TcpConnection *Conn, const char *pData, int nLenBytes);

	void Broadcast(const char *pData, int nLenBytes);

	bool IsClientOnline(TcpConnection *Conn);

	void PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs);

	void SetTimeoutSpan(int ms);

	int GetTimeoutSpan() const;

	void SetEventInterface(TcpServerEvent *pEvent);

	void RemoveConnection(TcpConnection *Conn);

public:
	TcpServer_Internal(const std::string &sIp, unsigned int nPort);
	~TcpServer_Internal();

private:
	TcpServer_Internal(const TcpServer_Internal &other);
	void operator = (const TcpServer_Internal &other);

	virtual void TcpConnectionMonitor_OnNewConnection(Socket *socket);
	virtual void TcpConnectionList_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkgs, std::vector<Packet> &vtFeedbackPkgs);

	TcpConnectionMonitor		m_ConnectionMonitor;
	TcpConnectionList			m_ConnectionList;
	TcpServerEvent				*m_pEventInterface;
	unsigned int				m_PacketID;
};

}}