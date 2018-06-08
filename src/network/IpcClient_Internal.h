#pragma once
#include "TcpClient.h"
#include "system/FarCallConnectObject.h"

namespace nb{ namespace Network{

class IpcClient_Internal : public nb::System::FarCallClient, public TcpClientEvent
{
public:
	bool Login(const char *pHostIp, int nHostPort);

	void Logout();

	std::string GetName() const;
	std::string GetHostIp() const;
	unsigned int GetHostPort() const;

	nb::System::FarCallSerial Send(nb::System::FarCallSerial &serial);

	nb::System::FarCallClient *GetFarCallClient();

	void Peek();

	void SetTimeoutSpan(int ms);

	int GetTimeoutSpan() const;

public:
	IpcClient_Internal();
	IpcClient_Internal(const char *name);
	~IpcClient_Internal();

private:
	virtual void SendDataOverride(nb::System::FarCallSerial &dataSerial, nb::System::FarCallSerial &resultSerial);
	virtual void TcpClient_OnUrgentPacketHandleNeeded(const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbacks);

	TcpClient	m_TcpClient;
};

}}
