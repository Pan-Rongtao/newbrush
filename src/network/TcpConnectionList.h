#pragma once
#include <vector>
#include "TcpConnection.h"
#include "ReceivePacket.h"
#include "core/Object.h"
#include "system/CriticalSection.h"

namespace nb{ namespace Network{

class TcpConnectionListEvent;
class TcpConnectionEvent;
class TcpConnectionList : public TcpConnectionEvent
{
	friend class TcpConnection;
public:
	TcpConnectionList();
	~TcpConnectionList();

	//在列表尾部追加一个Connection
	void Append(Socket *socket);

	//移除一个Connection
	void Remove(TcpConnection *Conn);

	//清除所有Connection
	void Clear();

	//获取连接数量
	int GetCount();

	//获取下标为index的Connection
	TcpConnection *GetAt(int index);

	//向某个Connection发数据
	Packet Send(TcpConnection *Conn, const Packet &pkg);

	//广播
	void Broadcast(const Packet &pkg);

	//从队列中拾取所有Connection的Packet
	void PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs);

	//设置通信超时时间，-1表示不限制
	void SetTimeoutSpan(int ms);

	//获取通信超时时间
	int GetTimeoutSpan() const;

	void SetEventInterface(TcpConnectionListEvent *pInterface);

private:
	virtual void TcpConnection_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkgs, std::vector<Packet> &vtFeedbackPkgs);
	virtual void TcpConnection_OnDisconnected(TcpConnection *Conn);

	int									m_nWaitTimeout;
	std::vector<TcpConnection *>		m_vtConnection;
	nb::System::CriticalSection			m_Lock;
	TcpConnectionListEvent				*m_pEventInterface;
};

class TcpConnectionListEvent
{
public:
	virtual void TcpConnectionList_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbackPkgs) {}
};

}}
