/*******************************************************
**	Packet
**
**	
**	该类群是描述用于通信的数据包数据结构，Header类描述了
**	数据包头，它的结构为
**
	包头内容： id  +	动作性质 + 命令类型 + 优先级 + 包体长度
	字节占位：  4	    	1	 +	  1		+    1   +	 4
		
**		而Packet的多种派生类描述各类请求包和确认包类型
**
**		
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include <stdio.h>
#include "core/NewBrushDef.h"

namespace nb{ namespace Network {

class NB_EXPORT Header
{
public:
	//动作类型
	enum ActionProperty : char
	{
		Property_Unknow,												//未知
		Property_Request,												//请求
		Property_Reply,													//答复
		Property_Max,
	};

	//包信息类型
	enum MessageType : char
	{
		Message_Unknow,
		Message_Signal_Hello,											//打招呼
		Message_Signal_Account_Login,									//客户端上线
		Message_Signal_Account_Logout,									//客户端离线
		Message_Signal_Server_Shutdown,									//服务器关闭
		Message_Binary_Stream,											//二进制数据
		Message_Signal_Max,												//signal保留
	};

	//包的传输优先级
	enum Priority : char
	{
		Priority_Unknow,
		Priority_Normal,												//普通
		Priority_Urgent,												//紧急
		Priority_Max,
	};

public:
	//获取数据指针
	char *GetData() const;

	//获取ID
	unsigned int GetID() const;

	//获取动作类型
	ActionProperty GetActionProperty() const;

	//获取消息类型
	MessageType GetMessageType() const;

	//获取优先级
	Priority GetPriority() const;

	//获取包体长度
	unsigned int GetBodySize() const;

public:
	//构建一个数据包头，它的动作类型为Property_Request，它的包信息类型是Message_Unknow，优先级为普通，它的包体长度为0，一般拥有这个包头的Packet不具有意义
	Header();

	//构建一个数据包头， ID 为 id，它的动作类型为ap，它的包信息类型是msgType，优先级为priority，它的包体长度为bodySize
	Header(unsigned int id, ActionProperty ap, MessageType msgType, Priority priority, unsigned int bodySize);

	//以其他Header的数据来构建一个Header
	Header(const Header &other);

	~Header();

public:
	void operator = (const Header &other);

public:
	//包头的字节长度，静态不可变，将返回11
	static unsigned int Size();

private:
	char	*m_pData;
};


//封包，一个封包包含包头和包体部分
class NB_EXPORT Packet
{
public:
	//获取报头
	Header GetHeader() const;

	//获取装包数据
	const char *GetData() const;

	//获取Body数据
	const char *GetBodyData() const;

	//填充Body数据，长度为Header::BodySize
	void FillBodyData(const char *pData);

	//获取包总长度
	int GetSize() const;


public:
	void operator = (const Packet &other);

public:
	//构建一个包，只有包头部分，包体长度为0
	Packet();

	//构建一个包，包头为header，包体数据为pBody
	Packet(const Header &header, const char *pBody);

	//从其他Packet构建一个包
	Packet(const Packet &other);

	~Packet();


public:
	//包的最长长度（包含包头的的长度），返回3 * 1024 * 1024字节
	static unsigned int MaxSize();

private:
	Header			m_Header;
	char			*m_pData;
};

//请求包基类
class Request : public Packet
{
public:
	Request(unsigned int id, Header::MessageType reqMsgType, Header::Priority priority, const char *pBodyData, int nBodySize);
};
//请求包派生类
class SignalHello : public Request
{
public:
	SignalHello(unsigned int id, Header::Priority priority);
};
class SignalLogin : public Request
{
public:
	SignalLogin(unsigned int id, Header::Priority priority, const std::string &name);
};
class SignalLogout : public Request
{
public:
	SignalLogout(unsigned int id, Header::Priority priority);
};
class SignalServerShutdown : public Request
{
public:
	SignalServerShutdown(unsigned int id, Header::Priority priority);
};
class SignalBinaryStream : public Request
{
public:
	SignalBinaryStream(unsigned int id, Header::Priority priority, const char *pBodyData, int nBodySize);
};

//////////////////////
//回执包基类
class Ack : public Packet
{
public:
	Ack(unsigned int id, Header::MessageType reqMsgType, Header::Priority priority, const char *pBodyData, int nBodySize);
};
//回执包派生类
class AckHello : public Ack
{
public:
	AckHello(unsigned int id, Header::Priority priority);
};
class AckLogin : public Ack
{
public:
	AckLogin(unsigned int id, Header::Priority priority);
};
class AckLogout : public Ack
{
public:
	AckLogout(unsigned int id, Header::Priority priority);
};
class AckServerShutdown : public Ack
{
public:
	AckServerShutdown(unsigned int id, Header::Priority priority);
};
class AckBinaryStream : public Ack
{
public:
	AckBinaryStream(unsigned int id, Header::Priority priority, const char *pBodyData, int nLenBytes);
};

}}
