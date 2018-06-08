#pragma once
#include "core/Object.h"
#include "system/FarCallConnectObject.h"
#include "system/String.h"

namespace nb{ namespace Network{

class IpcServerEvent;
class IpcServer_Internal;
class NB_EXPORT IpcServer
{
public:
	//获取服务器Ip
	nb::System::String GetIp() const;

	//获取服务器绑定的端口号
	unsigned int GetBindingPort() const;

	//启动服务
	bool Startup();

	//停止服务
	void Shutdown();

	//主动提取客户端的信件数据，如果缓冲区中无数据，该信件将是空的
	void Peek();

	//设置通信超时时间，-1表示不限制
	void SetTimeoutSpan(int ms);

	//获取通信超时时间
	int GetTimeoutSpan() const;

	void SetEventInterface(IpcServerEvent *pInterface);

public:
	IpcServer(const nb::System::String &sIp, unsigned int nPort);
	~IpcServer();
	
private:
	IpcServer(const IpcServer &other) {}
	void operator = (const IpcServer &other) {}

	IpcServer_Internal	*m_pInternal;
};

class IpcServerEvent
{
public:
	//新的连接完成
	virtual void IpcServer_OnNewConnection(const nb::System::String &name, nb::System::FarCallServer *pFarCallServer) {(void)name, (void)pFarCallServer;}

	//连接已断开
	virtual void IpcServer_OnConnectionDisconnected(nb::System::FarCallServer *pFarCallServer) {(void)pFarCallServer;}
};

}}
