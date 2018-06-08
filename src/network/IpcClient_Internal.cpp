#include "IpcClient_Internal.h"

using nb::Network::IpcClient_Internal;
using nb::Network::Packet;

IpcClient_Internal::IpcClient_Internal()
{
	m_TcpClient.SetEventInterface(this);
}

IpcClient_Internal::IpcClient_Internal(const char *name)
: m_TcpClient(name)
{
	m_TcpClient.SetEventInterface(this);
}

IpcClient_Internal::~IpcClient_Internal()
{
}

bool IpcClient_Internal::Login(const char *pHostIp, int nHostPort)
{
	return m_TcpClient.Login(pHostIp, nHostPort);
}

void IpcClient_Internal::Logout()
{
	m_TcpClient.Logout();
}

std::string IpcClient_Internal::GetName() const
{
	return m_TcpClient.GetName();
}

std::string IpcClient_Internal::GetHostIp() const
{
	return m_TcpClient.GetHostIp();
}

unsigned int IpcClient_Internal::GetHostPort() const
{
	return m_TcpClient.GetHostPort();
}

nb::System::FarCallSerial IpcClient_Internal::Send(nb::System::FarCallSerial &serial)
{
	nb::System::FarCallSerial ret(nb::System::FarCallSerial::Mode_Storing);
	SendDataOverride(serial, ret);
	return ret;
}

void IpcClient_Internal::SendDataOverride(nb::System::FarCallSerial &dataSerial, nb::System::FarCallSerial &resultSerial)
{
	Packet pkg = m_TcpClient.SendData((const char *)dataSerial.GetBuffer(), dataSerial.GetDataSize());

	if(pkg.GetHeader().GetMessageType() == Header::Message_Unknow)
	{

	}

	//写入的是bodydata，不是整个pkg的data
	resultSerial.Write((const unsigned char *)pkg.GetBodyData(), pkg.GetHeader().GetBodySize());
}

nb::System::FarCallClient *IpcClient_Internal::GetFarCallClient()
{
	return this;
}

void IpcClient_Internal::Peek()
{
	std::vector<Packet> vtFeedbackPkgs;
	std::vector<Packet> vtPkgs;

	m_TcpClient.PeekPacket(vtPkgs);
	for(int i = 0; i != vtPkgs.size(); ++i)
	{
		const Packet &pkg = vtPkgs[i];
		nb::System::FarCallSerial ret(nb::System::FarCallSerial::Mode_Storing);
		//解析的是bodydata，不是整个pkg的data
		AcceptData((const unsigned char *)pkg.GetBodyData(), pkg.GetHeader().GetBodySize(), ret);

		vtFeedbackPkgs.push_back(AckBinaryStream(pkg.GetHeader().GetID(), pkg.GetHeader().GetPriority(), (const char *)ret.GetBuffer(), ret.GetDataSize()));
	}

	m_TcpClient.PeekFeedback(vtFeedbackPkgs);
}

void IpcClient_Internal::TcpClient_OnUrgentPacketHandleNeeded(const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbacks)
{
	for(int i = 0; i != vtRequestPkg.size(); ++i)
	{
		const Packet &pkg = vtRequestPkg[i];
		nb::System::FarCallSerial ret(nb::System::FarCallSerial::Mode_Storing);
		//解析的是bodydata，不是整个pkg的data
		AcceptData((const unsigned char *)pkg.GetBodyData(), pkg.GetHeader().GetBodySize(), ret);

		vtFeedbacks.push_back(AckBinaryStream(pkg.GetHeader().GetID(), pkg.GetHeader().GetPriority(), (const char *)ret.GetBuffer(), ret.GetDataSize()));
	}

	m_TcpClient.PeekFeedback(vtFeedbacks);
}

void IpcClient_Internal::SetTimeoutSpan(int ms)
{
	return m_TcpClient.SetTimeoutSpan(ms);
}

int IpcClient_Internal::GetTimeoutSpan() const
{
	return m_TcpClient.GetTimeoutSpan();
}