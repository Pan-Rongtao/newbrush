/*******************************************************
**	IpcClient
**
**	进程间通信Client端
**	
**	该类是描述Ipc客户端的数据结构
**	它将用于定制数据流的传输
**
**		
**		
**		潘荣涛
**	
********************************************************/

#pragma once
#include "system/String.h"

namespace nb{ namespace System{

	class FarCallClient;
}}

namespace nb{ namespace Network{

class IpcClient_Internal;
class NB_EXPORT IpcClient
{
public:
	//登录服务端
	bool Login(const nb::System::String &sHostIp, unsigned int nHostPort);

	//登出
	void Logout();

	//获取名字
	nb::System::String GetName() const;

	//获取服务器ip地址
	nb::System::String GetHostIp() const;

	//获取端口
	unsigned int GetHostPort() const;

	//用于FarCallConnection通信会话使用的句柄
	nb::System::FarCallClient *GetFarCallClient() const;

	//收取信件
	void Peek();

	//设置通信超时时间，-1表示不限制
	void SetTimeoutSpan(int ms);

	//获取通信超时时间
	int GetTimeoutSpan() const;

public:
	//构建一个IpcClient对象
	IpcClient();
	IpcClient(const nb::System::String &name);
	~IpcClient();

private:
	IpcClient(const IpcClient &other) {}
	void operator = (const IpcClient &other) {}

	IpcClient_Internal		*m_pInternal;
};

}}
