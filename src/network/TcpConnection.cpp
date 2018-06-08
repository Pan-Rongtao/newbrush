#include "TcpConnection.h"
#include <assert.h>
#include "core/Exception.h"

using nb::Network::TcpConnection;
using nb::Network::Socket;
using nb::Network::Packet;
using nb::Network::TcpConnectionEvent;

TcpConnection::TcpConnection(Socket *socket)
: m_pSocket(socket)
, m_bConnected(false)
, m_bTimeout(false)
, m_bUrgentReplyNeeded(false)
, m_bRequestWaitAgain(false)
, m_bNeedUnlock(true)
, m_nWaitTimeout(-1)
, m_pEventInterface(NULL)
{
	m_Inbox.SetSocket(m_pSocket);
	m_Inbox.SetEventInterface(this);
}

TcpConnection::~TcpConnection()
{
	//这里删除socket不是很规范，因为new socket是在listen那里的，但这算是比较好的地方了
	m_Lock.Lock();
	delete m_pSocket;
	m_pSocket = NULL;
	m_bConnected = false;
	m_Lock.Unlock();
}

bool TcpConnection::IsConnected() const
{
	return m_bConnected;
}

void TcpConnection::Work()
{
	m_bConnected = true;
	m_Inbox.Work();
}

void TcpConnection::UnWork()
{
	m_bConnected = false;
	m_Inbox.UnWork();
}

//在所有wait之外的地方都该加锁，以保证request期间同步
//Request是有可能嵌套的，因此需要一个Stack来保持所有请求
//嵌套的场景为：当一个Connection发出Request后，接收到Client的请求，这时候需要
//优先处理Client的请求，但是在Client请求消息中，Connection又发了一个Request
//注意：如果在Request过程中发现client已经断开，不要马上把Connection删掉，
//而是等到下一个peek收到logout后删除，不然很难处理
Packet TcpConnection::Request(const Packet &pkg)
{
	assert(IsConnected());

	m_Lock.Lock();
	m_bNeedUnlock = true;
	m_RequestSession.push(PacketPair((Packet *)(&pkg), NULL));
	int nSend = m_pSocket->SendData(pkg.GetData(), pkg.GetSize());
	//send出错表示远端已断开，则返回空包
	if(nSend == -1)
	{
		m_Lock.Unlock();
		return Packet();
	}
	//检查紧急包并reply，如果出错表示远端已断开，则返回空包
	if(CheckUrgentPackets() == false)
	{
		m_Lock.Unlock();
		return Packet();
	}
	//注意解锁次数，Request可能有嵌套，需要解锁全部接收线程才能继续执行（如果全部解锁一次即可）
	if(m_bNeedUnlock)
	{
		for(int i = 0; i != m_RequestSession.size(); ++i)	
			m_Lock.Unlock();
		if(m_RequestSession.size() >= 2)
			m_bNeedUnlock = false;
	}


loop:
	bool b = m_RequestSync.Wait(m_nWaitTimeout);
	if(b)
	{
		m_Lock.Lock();
		m_bTimeout = true;
		m_RequestSession.pop();
		m_Lock.Unlock();
		printf("[%d]TcpConnection::Request---wait timeout!!! m_RequestSession.pop->size[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), m_RequestSession.size());
		NB_THROW_EXCEPTION("server request timeout!!!");
	}

	m_Lock.Lock();
	if(m_bUrgentReplyNeeded) CheckUrgentPackets();
	m_Lock.Unlock();

	if(m_bRequestWaitAgain)
		goto loop;

	m_Lock.Lock();
	Packet *p = m_RequestSession.top().Ack;
	Packet ret = p ? *p : Packet();
	delete p;
	m_RequestSession.pop();
	m_Lock.Unlock();

	return ret;
}

int TcpConnection::Reply(const Packet &pkg)
{
	assert(IsConnected());

	m_Lock.Lock();
	int nSend = m_pSocket->SendData(pkg.GetData(), pkg.GetSize());
	m_Lock.Unlock();
	return nSend;
}

void TcpConnection::PeekPacket(std::vector<Packet> &vtPkgs)
{
	m_Lock.Lock();
	m_Inbox.PopPackets(vtPkgs);
	for(int i = 0; i != vtPkgs.size(); ++i)
		m_PeekSession.push(PacketPair(&(vtPkgs[i]), NULL));
	m_Lock.Unlock();
}

bool TcpConnection::PeekFeedback(std::vector<Packet> &feedbackPkgs)
{
	for(int i = 0; i != feedbackPkgs.size(); ++i)
	{
		Packet &pkg = feedbackPkgs[i];
		if(pkg.GetHeader().GetMessageType() == Header::Message_Signal_Account_Logout)
		{
			m_pEventInterface->TcpConnection_OnDisconnected(this);
			return true;
		}
		else
		{
			m_Lock.Lock();
			int nSend = Reply(pkg);
			m_bRequestWaitAgain = (m_RequestSession.size() >= 1) && (nSend != -1);
			if(!m_PeekSession.empty())
				m_PeekSession.pop();
			m_Lock.Unlock();
			return nSend != -1;
		}

	}
	return true;
}

void TcpConnection::SetTimeoutSpan(int ms)
{
	m_nWaitTimeout = ms;
}

int TcpConnection::GetTimeoutSpan() const
{
	return m_nWaitTimeout;
}

bool TcpConnection::IsSessioning() const 
{
	((TcpConnection *)this)->m_Lock.Lock();
	bool b = !m_RequestSession.empty() || !m_PeekSession.empty();
	((TcpConnection *)this)->m_Lock.Unlock();
	return b;
}

void TcpConnection::SetEventInterface(TcpConnectionEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void TcpConnection::TcpInbox_OnRequestArrived(const Packet &pkg)
{
	HandlePacket(pkg);
}

//接收线程加锁
void TcpConnection::TcpInbox_OnReplyArrived(const Packet &pkg)
{
	m_Lock.Lock();
	//如果超时，将忽略此次client端的ack包
	if(m_bTimeout && (m_RequestSession.empty() || pkg.GetHeader().GetID() != m_RequestSession.top().Request->GetHeader().GetID()))
	{
		printf("TcpConnection::TcpInbox_OnReplyArrived timeout reply packet, ignore.");
		m_bTimeout = false;
		m_Lock.Unlock();
		return;
	}
	if(pkg.GetHeader().GetID() != m_RequestSession.top().Request->GetHeader().GetID())
	{
		printf("[%d]m_RequestSession.top().Request.id[%d], reply pkg.id[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), m_RequestSession.top().Request->GetHeader().GetID(), pkg.GetHeader().GetID());
		assert(0);
	}

	while(!m_RequestSync.IsWaiting())	
		;

	m_RequestSession.top().Ack = new Packet(pkg);
	m_bUrgentReplyNeeded = false;
	m_bRequestWaitAgain = false;

	m_RequestSync.Release();

	m_Lock.Unlock();
}

void TcpConnection::TcpInbox_OnRemoteUnknownReasonDisconnected()
{
	HandlePacket(SignalLogout(-1, Header::Priority_Normal));
}

//接收线程加锁
void TcpConnection::HandlePacket(const Packet &pkg)
{
	m_Lock.Lock();
	m_Inbox.PushPacket(pkg);
	//如果正在Request，且还未收到ack，则让Request release，设置标志
	if(!m_RequestSession.empty() && !(m_RequestSession.top().Ack))
	{
		while(!m_RequestSync.IsWaiting())
			;

		bool bLogout = pkg.GetHeader().GetMessageType() == Header::Message_Signal_Account_Logout;
		m_bUrgentReplyNeeded = !bLogout;
		m_bRequestWaitAgain = !bLogout;

		m_RequestSync.Release();
	}
	m_Lock.Unlock();
}

bool TcpConnection::CheckUrgentPackets()
{
	bool bRet = true;
	std::vector<Packet> vtPkgs;
	m_Inbox.PopPackets(vtPkgs);
	if(!vtPkgs.empty())
	{
		std::vector<Packet> vtFeedbackPkgs;
		//此处不做m_pEventInterface判断了，要求一定不为空，提高效率
		m_pEventInterface->TcpConnection_OnUrgentPacketHandleNeeded(this, vtPkgs, vtFeedbackPkgs);
		bRet = PeekFeedback(vtFeedbackPkgs);
	}
	m_bUrgentReplyNeeded = false;
	return bRet;
}
