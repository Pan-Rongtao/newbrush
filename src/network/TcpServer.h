/*******************************************************
**	TcpServer
**
**	基于Tcp的服务端
**	
**	该类是描述基于Tcp协议的服务端模型的数据结构
**	
**	它提供的所有操作都是同步的
**
**		
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include <string>
#include "ReceivePacket.h"
#include "TcpConnection.h"

namespace nb{ namespace Network{

class TcpServerEvent;
class TcpServer_Internal;
class NB_EXPORT TcpServer
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

	//查询服务器状态是否为已启动
	bool IsStartupped() const;

	//向客户端Conn发送数据，如果pData为NULL，将忽略此次操作
	//异常：nLenBytes < 0
	Packet SendData(TcpConnection *Conn, const char *pData, int nLenBytes);

	//主动提取客户端的信件数据，如果缓冲区中无数据，该信件将是空的
	void PeekClientPackets(std::vector<ReceivePacket> &vtRpkgs);

	//设置通信超时时间，-1表示不限制
	void SetTimeoutSpan(int ms);

	//获取通信超时时间
	int GetTimeoutSpan() const;

	void SetEventInterface(TcpServerEvent *pEventInterface);

	void RemoveConnection(TcpConnection *Conn);

public:
	TcpServer(const std::string &sIp, unsigned int nPort);
	~TcpServer();

private:
	TcpServer(const TcpServer &other) {}
	void operator = (const TcpServer &other) {}

	TcpServer_Internal	*m_pInternal;
};

class TcpServerEvent
{
public:
	virtual void TcpServer_OnUrgentPacketHandleNeeded(TcpConnection *Conn, const std::vector<Packet> &vtRequestPkgs, std::vector<Packet> &vtFeedbackPkgs) {(void)vtRequestPkgs; (void)vtFeedbackPkgs;}
};

}}