#include "TcpClient_Internal.h"
#include "TcpClient.h"
#include "core/Exception.h"
#include <assert.h>

using nb::Network::TcpClient_Internal;
using nb::Network::Packet;
using nb::Network::TcpClientEvent;

TcpClient_Internal::TcpClient_Internal()
: m_bConnected(false)
, m_pSocket(NULL)
, m_pEventInterface(NULL)
, m_bUrgentReplyNeeded(false)
, m_bRequestWaitAgain(false)
, m_nWaitTimeout(-1)
{
	m_Inbox.SetEventInterface(this);
}

TcpClient_Internal::TcpClient_Internal(const std::string &name)
: m_bConnected(false)
, m_pSocket(NULL)
, m_Name(name)
, m_pEventInterface(NULL)
, m_bUrgentReplyNeeded(false)
, m_bRequestWaitAgain(false)
, m_nWaitTimeout(-1)
{
	m_Inbox.SetEventInterface(this);
}

TcpClient_Internal::~TcpClient_Internal()
{
	Logout();
}

bool TcpClient_Internal::Login(const std::string &sHostIp, int nPort)
{
	if(IsConnected())
		return true;

	if(m_pSocket == NULL)
	{
		m_pSocket = new ClientSocket(sHostIp, nPort);
		m_Inbox.SetSocket(m_pSocket);
	}

	m_bConnected = m_pSocket->Connect();
	if(!m_bConnected)
		return false;

	//先开启线程接收再发送数据才能保证server的ack
	m_Inbox.Work();
	Packet ret = Request(SignalLogin(0, Header::Priority_Urgent, m_Name));
	if(ret.GetHeader().GetMessageType() == Header::Property_Unknow)
	{
		m_Inbox.UnWork();
		return false;
	}

	return true;
}

void TcpClient_Internal::Logout()
{
	if(!IsConnected())
		return;

	Packet ret = Request(SignalLogout(-1, Header::Priority_Urgent));
	m_bConnected = false;
	m_Inbox.UnWork();

	delete m_pSocket;
	m_pSocket = NULL;
}

bool TcpClient_Internal::IsConnected() const
{
	return m_bConnected;
}

std::string TcpClient_Internal::GetName() const
{
	return m_Name;
}

std::string TcpClient_Internal::GetHostIp() const
{
	return m_pSocket->GetIp();
}

unsigned int TcpClient_Internal::GetHostPort() const
{
	return m_pSocket->GetPort();
}

Packet TcpClient_Internal::Request(const Packet &pkg)
{
	assert(IsConnected());

	m_Lock.Lock();
	m_RequestSession.push(PacketPair((Packet *)(&pkg), NULL));
	int nSend = m_pSocket->SendData(pkg.GetData(), pkg.GetSize());
	for(int i = 0; i != m_RequestSession.size(); ++i)	//注意解锁次数，Request可能有嵌套（此处与server端不同，解嵌套锁不需要而外的判断）
		m_Lock.Unlock();

loop:
	bool b = m_RequestSync.Wait(m_nWaitTimeout);
	if(b)
	{
		printf("[%d]TcpClient_Internal::Request---wait timeout!!! m_RequestSession.size[%d], id[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), m_RequestSession.size(), m_RequestSession.top().Request->GetHeader().GetID());
		//assert(!b);
		NB_THROW_EXCEPTION("client request timeout!!!");
	}

	//如果有紧急包要处理，则处理，再wait
	m_Lock.Lock();
	if(m_bUrgentReplyNeeded)	CheckUrgentPackets();
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

void TcpClient_Internal::Reply(const Packet &pkg)
{
	assert(IsConnected());
m_Lock.Lock();
	int nSend = m_pSocket->SendData(pkg.GetData(), pkg.GetSize());
m_Lock.Unlock();
}

void TcpClient_Internal::PeekPacket(std::vector<Packet> &vtPkgs)
{
	m_Lock.Lock();
	m_Inbox.PopPackets(vtPkgs);
	m_Lock.Unlock();
}

void TcpClient_Internal::PeekFeedback(std::vector<Packet> &feedbackPkgs)
{
	m_Lock.Lock();
	for(int i = 0; i != feedbackPkgs.size(); ++i)
	{
		Reply(feedbackPkgs[i]);
		m_bRequestWaitAgain = m_RequestSession.size() >= 1;
	}
	m_Lock.Unlock();
}

void TcpClient_Internal::SetTimeoutSpan(int ms)
{
	m_nWaitTimeout = ms;
}

int TcpClient_Internal::GetTimeoutSpan() const
{
	return m_nWaitTimeout;
}

void TcpClient_Internal::SetEventInterface(TcpClientEvent *pEvent)
{
	m_pEventInterface = pEvent;
}

//如果是紧急包，需要先处理掉（发紧急包的条件请看TcpConnectionList）
void TcpClient_Internal::TcpInbox_OnRequestArrived(const Packet &pkg)
{
	m_Lock.Lock();
	if(pkg.GetHeader().GetPriority() == Header::Priority_Urgent)
	{
		m_UrgentPackets.push_back(pkg);
		m_bUrgentReplyNeeded = true;
		m_bRequestWaitAgain = true;
		m_RequestSync.Release();
	}
	else
	{
		m_Inbox.PushPacket(pkg);
	}
	m_Lock.Unlock();
}

void TcpClient_Internal::TcpInbox_OnReplyArrived(const Packet &pkg)
{
	m_Lock.Lock();
	if(pkg.GetHeader().GetID() != m_RequestSession.top().Request->GetHeader().GetID())
	{
		printf("[%d]m_RequestSession.top().Request.id[%d], pkg.id[%d]\r\n", nb::System::Platform::GetCurrentProcessId(), m_RequestSession.top().Request->GetHeader().GetID(), pkg.GetHeader().GetID());
		assert(0);
	}

	while(m_RequestSync.IsWaiting() == false)
		;

	m_RequestSession.top().Ack = new Packet(pkg);
	m_bUrgentReplyNeeded = false;
	m_bRequestWaitAgain = false;
	m_RequestSync.Release();

	m_Lock.Unlock();
}

void TcpClient_Internal::CheckUrgentPackets()
{
	std::vector<Packet> vtRequests = m_UrgentPackets;
	m_UrgentPackets.clear();
	if(!vtRequests.empty())
	{
		std::vector<Packet> vtFeedbacks;
		m_pEventInterface->TcpClient_OnUrgentPacketHandleNeeded(vtRequests, vtFeedbacks);
		m_bUrgentReplyNeeded = false;
	}
}

void TcpClient_Internal::TcpInbox_OnRemoteUnknownReasonDisconnected()
{
	NB_THROW_EXCEPTION("server is disconnected for unknow reason");
}
