#pragma once
#include <vector>
#include "system/CriticalSection.h"
#include "Sync.h"
#include "TcpMesssageMonitor.h"
#include "Packet.h"

namespace nb{ namespace Network{

class TcpInboxEvent;
class TcpInbox : public TcpMessageMonitorEvent
{
public:
	TcpInbox();
	~TcpInbox();

	//
	void SetSocket(Socket *socket);

	//开启消息监听收取信件
	void Work();

	//关闭消息监听
	void UnWork();

	void PopPackets(std::vector<Packet> &vtPkgs);

	void PushPacket(const Packet &pkg);

	void SetEventInterface(TcpInboxEvent *pInterface);

private:
	TcpInbox(const TcpInbox &other);
	void operator = (const TcpInbox &other);

	virtual void TcpMessageMonitor_OnPacketArrived(const Packet &pkg);
	virtual void TcpMessageMonitor_OnErrorPacket();

	std::vector<Packet>				m_vtPkgs;
	nb::System::CriticalSection		m_PacketsLock;
	TcpMessageMonitor				m_MessageMonitor;
	TcpInboxEvent					*m_pEventInterface;

	std::vector<Packet>				m_vtHandling;
};

class TcpInboxEvent
{
public:
	//有新的请求
	virtual void TcpInbox_OnRequestArrived(const Packet &toRemoteFeedback) {(void)toRemoteFeedback;}

	//有新的回复
	virtual void TcpInbox_OnReplyArrived(const Packet &fromRemoteFeedback) {(void)fromRemoteFeedback;}

	//链接未知原因断开了
	virtual void TcpInbox_OnRemoteUnknownReasonDisconnected() {}

};

}}
