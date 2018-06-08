/*******************************************************
**	TcpClient
**
**	基于Tcp的客户端
**	
**	该类是描述基于Tcp协议的客户端模型的数据结构
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
#include <vector>
#include "Packet.h"

namespace nb{ namespace Network{

class TcpClientEvent;
class TcpClient_Internal;
class NB_EXPORT TcpClient
{
public:
	//登录，该操作将尝试连接服务器，服务器ip为sHostIp，服务器端口号为nPort
	//异常：服务器不可达
	//异常：本地客户端名字在服务器上已存在
	bool Login(const std::string &sHostIp, int nPort);

	//登出，该操作将主动告知服务器自己的离线行为
	void Logout();

	//查询是否处于连接状态
	bool IsConnected() const;

	std::string GetName() const;

	//获取服务器地址
	std::string GetHostIp() const;
	unsigned int GetHostPort() const;

	//向服务器发送一块长度为nLenBytes字节的数据pData
	//如果pData为NULL，将不做发送动作
	//异常：nLenBytes < 0
	Packet SendData(const char *pData, int nLenBytes);

	//主动提取服务端的信件数据，如果缓冲区中无数据，该信件将是空的
	void PeekPacket(std::vector<Packet> &vtPkgs);

	void PeekFeedback(std::vector<Packet> &feedbackPkgs);

	void SetTimeoutSpan(int ms);

	int GetTimeoutSpan() const;

	void SetEventInterface(TcpClientEvent *pInterface);


public:
	//构建一个TcpClient对象
	TcpClient();
	TcpClient(const std::string &name);
	~TcpClient();

private:
	TcpClient(const TcpClient &other) {}
	void operator = (const TcpClient &other) {}

	TcpClient_Internal		*m_pInternal;
	unsigned int			m_PacketID;
};

class TcpClientEvent
{
public:
	//紧急包需处理请求
	virtual void TcpClient_OnUrgentPacketHandleNeeded(const std::vector<Packet> &vtRequestPkg, std::vector<Packet> &vtFeedbacks) {(void)vtRequestPkg; (void)vtFeedbacks;}
};

}}
