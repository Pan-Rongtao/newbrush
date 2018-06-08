#pragma once
#include "Packet.h"
#include "ClientSocket.h"
#include "TcpInbox.h"
#include <stack>
#include "PacketPair.h"

namespace nb{ namespace Network{

class TcpClientEvent;
class TcpClient_Internal : public TcpInboxEvent
{
public:
	TcpClient_Internal();
	TcpClient_Internal(const std::string &name);
	~TcpClient_Internal();

	bool Login(const std::string &sHostIp, int nPort);

	void Logout();

	bool IsConnected() const;

	std::string GetName() const;
	std::string GetHostIp() const;
	unsigned int GetHostPort() const;

	//Requst反馈了数据
	//pkg:Request反馈的数据
	Packet Request(const Packet &pkg);

	//回复，异步
	void Reply(const Packet &pkg);

	//拾取服务端信件
	void PeekPacket(std::vector<Packet> &vtPkgs);

	//拾取信件回复
	//feedback：处理server数据后的返回数据
	void PeekFeedback(std::vector<Packet> &feedbackPkgs);

	void SetTimeoutSpan(int ms);

	int GetTimeoutSpan() const;

	void SetEventInterface(TcpClientEvent *pEvent);

private:
	TcpClient_Internal(const TcpClient_Internal &other) {}
	void operator = (const TcpClient_Internal &other) {}

	virtual void TcpInbox_OnRequestArrived(const Packet &pkg);
	virtual void TcpInbox_OnReplyArrived(const Packet &pkg);
	virtual void TcpInbox_OnRemoteUnknownReasonDisconnected();

	//发送过程中如果有client请求包，优先处理
	void CheckUrgentPackets();

	bool							m_bConnected;
	ClientSocket					*m_pSocket;
	std::string						m_Name;

	Sync							m_RequestSync;
	nb::System::CriticalSection		m_Lock;
	TcpInbox						m_Inbox;
	TcpClientEvent					*m_pEventInterface;

	bool							m_bUrgentReplyNeeded;
	bool							m_bRequestWaitAgain;
	int								m_nWaitTimeout;
	std::vector<Packet>				m_UrgentPackets;
	std::stack<PacketPair>			m_RequestSession;
};

}}