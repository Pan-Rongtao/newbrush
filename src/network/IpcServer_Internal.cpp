#include "IpcServer_Internal.h"
#include "network/IpcServer.h"
#include "system/FarCallConnectObject.h"

using nb::Network::IpcServer_Internal;
using nb::Network::IpcServerEvent;
using nb::Network::Packet;
using nb::Network::TcpConnection;

IpcServer_Internal::IpcServer_Internal(const std::string &sIp, unsigned int nPort)
: m_TcpServer(sIp, nPort)
, m_pEventInterface(NULL)
{
	m_TcpServer.SetEventInterface(this);
}

IpcServer_Internal::~IpcServer_Internal()
{
}

std::string IpcServer_Internal::GetIp() const
{
	return m_TcpServer.GetIp();
}

unsigned int IpcServer_Internal::GetBindingPort() const
{
	return m_TcpServer.GetBindingPort();
}

bool IpcServer_Internal::Startup()
{
	return m_TcpServer.Startup();
}

void IpcServer_Internal::Shutdown()
{
	return m_TcpServer.Shutdown();
}

void IpcServer_Internal::Peek()
{
	std::vector<ReceivePacket> vtPkgs;
	m_TcpServer.PeekClientPackets(vtPkgs);
	for(int i = 0; i != vtPkgs.size(); ++i)
	{
		std::vector<Packet> vtFeedbackPkgs;
		Packet feedback;
		bool bLogout = HandlePeekedPackage(vtPkgs[i].GetConnection(), vtPkgs[i].GetPacket(), feedback);
		vtFeedbackPkgs.push_back(feedback);
		vtPkgs[i].GetConnection()->PeekFeedback(vtFeedbackPkgs);
		if(bLogout)
			break;
	}
}

void IpcServer_Internal::SetTimeoutSpan(int ms)
{
	m_TcpServer.SetTimeoutSpan(ms);
}

int IpcServer_Internal::GetTimeoutSpan() const
{
	return m_TcpServer.GetTimeoutSpan();
}

void IpcServer_Internal::SetEventInterface(IpcServerEvent *pInterface)
{
	m_pEventInterface = pInterface;
}

void IpcServer_Internal::TcpServer_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequests, std::vector<Packet> &vtFeedbacks)
{
	for(int i = 0; i != vtRequests.size(); ++i)
	{
		Packet feedback;
		bool bLogout = HandlePeekedPackage(Conn, vtRequests[i], feedback);
		vtFeedbacks.push_back(feedback);
		if(bLogout)
			break;
	}
}

bool IpcServer_Internal::HandlePeekedPackage(TcpConnection *Conn, const Packet &pkg, Packet &feedback)
{
	Header::MessageType type = pkg.GetHeader().GetMessageType();
	switch(pkg.GetHeader().GetMessageType())
	{
	case Header::Message_Signal_Account_Login:
		{
			m_FarCallConnections.Push(Conn, &m_TcpServer);
			std::string s(pkg.GetBodyData() ,pkg.GetBodyData() + pkg.GetHeader().GetBodySize());
			if(m_pEventInterface)
				m_pEventInterface->IpcServer_OnNewConnection(nb::System::String(s.data()), m_FarCallConnections.FindFarCall(Conn));

			feedback = AckLogin(pkg.GetHeader().GetID(), pkg.GetHeader().GetPriority());
		}
		break;
	case Header::Message_Signal_Account_Logout:
		{
			if(m_pEventInterface)
				m_pEventInterface->IpcServer_OnConnectionDisconnected(m_FarCallConnections.FindFarCall(Conn));
			m_FarCallConnections.Remove(Conn);

			feedback = AckLogout(pkg.GetHeader().GetID(), pkg.GetHeader().GetPriority());
		}
		break;
	case Header::Message_Binary_Stream:
		{
			feedback = m_FarCallConnections.DecodePacket(Conn, pkg);
		}
		break;
	default:
		break;
	}
	return type == Header::Message_Signal_Account_Logout;
}
