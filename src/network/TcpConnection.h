#pragma once
#include "Socket.h"
#include "Packet.h"
#include "Sync.h"
#include "system/Thread.h"
#include "system/CriticalSection.h"
#include "TcpInbox.h"
#include <stack>
#include "PacketPair.h"

namespace nb{ namespace Network{

class TcpConnectionEvent;
class TcpConnection : public TcpInboxEvent
{
public:
	TcpConnection(Socket *socket);
	~TcpConnection();

	//连接状态
	bool IsConnected() const;

	//启动/停止消息监听
	void Work();
	void UnWork();

	//Requst反馈的数据
	//pkg:Request反馈的数据
	//返回Packet()空包表示远端已经断开
	Packet Request(const Packet &pkg);

	//回复，异步
	//如果返回-1，表示发送失败
	int Reply(const Packet &pkg);

	//拾取服务端信件
	void PeekPacket(std::vector<Packet> &vtPkgs);

	//拾取信件回复
	//feedback：处理Client数据后的返回数据
	//返回false表示client端已断开
	bool PeekFeedback(std::vector<Packet> &feedbackPkgs);

	//设置通信超时时间，-1表示不限制
	void SetTimeoutSpan(int ms);

	//获取通信超时时间
	int GetTimeoutSpan() const;

	//是否真正处于一次会话过程
	bool IsSessioning() const;

	void SetEventInterface(TcpConnectionEvent *pInterface);

private:
	TcpConnection(const TcpConnection &other) {}
	void operator = (const TcpConnection &other) {}

	virtual void TcpInbox_OnRequestArrived(const Packet &pkg);
	virtual void TcpInbox_OnReplyArrived(const Packet &pkg);
	virtual void TcpInbox_OnRemoteUnknownReasonDisconnected();

	void HandlePacket(const Packet &pkg);

	//发送过程中如果有client请求包，优先处理
	//返回false表示client已经断开
	bool CheckUrgentPackets();

	bool							m_bConnected;
	bool							m_bTimeout;
	Socket							*m_pSocket;

	Sync							m_RequestSync;
	bool							m_bUrgentReplyNeeded;
	bool							m_bRequestWaitAgain;
	bool							m_bNeedUnlock;
	int								m_nWaitTimeout;

	TcpInbox						m_Inbox;
	nb::System::CriticalSection		m_Lock;
	TcpConnectionEvent				*m_pEventInterface;

	std::stack<PacketPair>			m_RequestSession;
	std::stack<PacketPair>			m_PeekSession;
};


class TcpConnectionEvent
{
public:
	virtual void TcpConnection_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbacks) {(void)vtRequestPkg; (void)vtFeedbacks;}
	virtual void TcpConnection_OnDisconnected(TcpConnection *Conn) {(void)Conn;}
};

}}
