#pragma once
#include <vector>
#include "TcpServer.h"
#include "FarCallConnectionList.h"
#include "system/FarCallConnectObject.h"

namespace nb{ namespace Network{

class IpcServerEvent;
class FarCallConnectionListEvent;
class IpcServer_Internal : public TcpServerEvent
{
public:
	//获取服务器Ip
	std::string GetIp() const;

	//获取服务器绑定的端口号
	unsigned int GetBindingPort() const;

	//启动服务
	bool Startup();

	//停止服务
	void Shutdown();

	//发送数据
	//nb::System::FarCallSerial Send(const std::string &sClientName, nb::System::FarCallSerial &serial);

	//提取收件箱信件，如果缓冲区中无数据，该数据流将是空的
	void Peek();

	//设置通信超时时间，-1表示不限制
	void SetTimeoutSpan(int ms);

	//获取通信超时时间
	int GetTimeoutSpan() const;

	void SetEventInterface(IpcServerEvent *pInterface);

public:
	IpcServer_Internal(const std::string &sIp, unsigned int nPort);
	~IpcServer_Internal();

private:
	virtual void TcpServer_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequests, std::vector<Packet> &vtFeedbacks);

	//处理一个pkg，返回值表示是否是退出pkg
	bool HandlePeekedPackage(TcpConnection *Conn, const Packet &pkg, Packet &feedback);

private:
	TcpServer						m_TcpServer;
	FarCallConnectionList			m_FarCallConnections;
	IpcServerEvent					*m_pEventInterface;
};

}}
