#include <string.h>
#include "Packet.h"

using nb::Network::Header;
using nb::Network::Packet;
using nb::Network::Request;
using nb::Network::SignalHello;
using nb::Network::SignalLogin;
using nb::Network::SignalLogout;
using nb::Network::SignalServerShutdown;
using nb::Network::SignalBinaryStream;
using nb::Network::Ack;
using nb::Network::AckHello;
using nb::Network::AckLogin;
using nb::Network::AckLogout;
using nb::Network::AckServerShutdown;
using nb::Network::AckBinaryStream;

Header::Header()
{
	m_pData = new char[Header::Size()];
	*((unsigned int *)m_pData) = 0;
	m_pData[4] = Property_Request;
	m_pData[5] = Message_Unknow;
	m_pData[6] = Priority_Normal;
	*((unsigned int *)(m_pData + 7)) = 0;
}

Header::Header(unsigned int id, ActionProperty ap, MessageType msgType, Priority priority, unsigned int bodySize)
{
	m_pData = new char[Header::Size()];
	*((unsigned int *)m_pData) = id;
	m_pData[4] = ap;
	m_pData[5] = msgType;
	m_pData[6] = priority;
	*((unsigned int *)(m_pData + 7)) = bodySize;
}

Header::Header(const Header &other)
: m_pData(NULL)
{
	delete [] m_pData;
	m_pData = new char[Header::Size()];
	memcpy(m_pData, other.m_pData, Header::Size());
}

Header::~Header()
{
	delete [] m_pData;
}

void Header::operator = (const Header &other)
{
	delete [] m_pData;
	m_pData = new char[Header::Size()];
	memcpy(m_pData, other.m_pData, Header::Size());
}

char *Header::GetData() const
{
	return m_pData;
}

unsigned int Header::GetID() const
{
	return *((unsigned int *)m_pData);
}

Header::ActionProperty Header::GetActionProperty() const
{
	return (ActionProperty)m_pData[4];
}

Header::MessageType Header::GetMessageType() const
{
	return (MessageType)m_pData[5];
}

Header::Priority Header::GetPriority() const
{
	return (Priority)m_pData[6];
}

unsigned int Header::GetBodySize() const
{
	int xx = *((unsigned int *)(m_pData + 7));
	return xx;
}

unsigned int Header::Size()
{
	return 11;
}

//////////////////////
Packet::Packet()
{
	m_pData = new char[Header::Size() + m_Header.GetBodySize()];
	memcpy(m_pData, m_Header.GetData(), Header::Size());
}

Packet::Packet(const Header &header, const char *pBody)
: m_Header(header)
{
	m_pData = new char[Header::Size() + m_Header.GetBodySize()];
	memcpy(m_pData, header.GetData(), Header::Size());
	if(pBody != NULL && m_Header.GetBodySize() > 0)
		memcpy(m_pData + Header::Size(), pBody, m_Header.GetBodySize());
}

Packet::Packet(const Packet &other)
: m_Header(other.GetHeader())
, m_pData(NULL)
{
	delete [] m_pData;
	m_pData = new char[other.GetSize()];
	memcpy(m_pData, other.GetData(), other.GetSize());
}

void Packet::operator = (const Packet &other)
{
	m_Header = other.GetHeader();
	delete [] m_pData;
	m_pData = new char[other.GetSize()];
	memcpy(m_pData, other.GetData(), other.GetSize());
}

Packet::~Packet()
{
	delete [] m_pData;
}

Header Packet::GetHeader() const
{
	return m_Header;
}

const char *Packet::GetData() const
{
	return m_pData;
}

const char *Packet::GetBodyData() const
{
	return m_pData + Header::Size();
}

void Packet::FillBodyData(const char *pData)
{	
	if(pData != NULL && m_Header.GetBodySize() > 0)
		memcpy(m_pData + Header::Size(), pData, m_Header.GetBodySize());
}

int Packet::GetSize() const
{
	return Header::Size() + m_Header.GetBodySize();
}

unsigned int Packet::MaxSize()
{
	return 3 * 1024 * 1024;
}

Request::Request(unsigned int id, Header::MessageType reqMsgType, Header::Priority priority, const char *pBodyData, int nBodySize)
: Packet(Header(id, Header::Property_Request, reqMsgType, priority, nBodySize), pBodyData)
{
}
SignalHello::SignalHello(unsigned int id, Header::Priority priority)
: Request(id, Header::Message_Signal_Hello, priority, NULL, 0)
{
}
SignalLogin::SignalLogin(unsigned int id, Header::Priority priority, const std::string &name)
: Request(id, Header::Message_Signal_Account_Login, priority, name.data(), name.size())
{
}
SignalLogout::SignalLogout(unsigned int id, Header::Priority priority)
: Request(id, Header::Message_Signal_Account_Logout, priority, NULL, 0)
{
}
SignalServerShutdown::SignalServerShutdown(unsigned int id, Header::Priority priority)
: Request(id, Header::Message_Signal_Server_Shutdown, priority, NULL, 0)
{
}
SignalBinaryStream::SignalBinaryStream(unsigned int id, Header::Priority priority, const char *pBodyData, int nBodySize)
: Request(id, Header::Message_Binary_Stream, priority, pBodyData, nBodySize)
{
}
///////////
Ack::Ack(unsigned int id, Header::MessageType reqMsgType, Header::Priority priority, const char *pBodyData, int nBodySize)
: Packet(Header(id, Header::Property_Reply, reqMsgType, priority, nBodySize), pBodyData)
{
}
AckHello::AckHello(unsigned int id, Header::Priority priority)
: Ack(id, Header::Message_Signal_Hello, priority, NULL, 0)
{
}
AckLogin::AckLogin(unsigned int id, Header::Priority priority)
: Ack(id, Header::Message_Signal_Account_Login, priority, NULL, 0)
{
}
AckLogout::AckLogout(unsigned int id, Header::Priority priority)
: Ack(id, Header::Message_Signal_Account_Logout, priority, NULL, 0)
{
}
AckServerShutdown::AckServerShutdown(unsigned int id, Header::Priority priority)
: Ack(id, Header::Message_Signal_Server_Shutdown, priority, NULL, 0)
{
}
AckBinaryStream::AckBinaryStream(unsigned int id, Header::Priority priority, const char *pBodyData, int nLenBytes)
: Ack(id, Header::Message_Binary_Stream, priority, pBodyData, nLenBytes)
{
}