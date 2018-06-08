#pragma once

#include "core/Object.h"
#include "core/Event.h"
#include "DataSerial.h"
#include "GenericVariant.h"
#include "Array.h"


#include <set>

namespace nb { namespace System {

class FarCallServer;
class FarCallClient;
class FarCallConnectObject;

//远端异常，一般是抛出给另一端捕捉使用。在接收远端数据传递的函数范围内，异常抛出后，远端将会响应异常
class NB_EXPORT FarCallFarPortException : public nb::Core::Exception
{
public:
	FarCallFarPortException(const char *message) : nb::Core::Exception(message) {}
};
typedef nbObjectPtrDerive<FarCallFarPortException, nb::Core::ExceptionPtr> FarCallFarPortExceptionPtr;


class FarCallSerialInternal;
class NB_EXPORT FarCallSerial : public DataSerial
{
	friend class FarCallServer;
public:
	enum Mode
	{
		Mode_Loading,
		Mode_Storing
	};

	FarCallSerial(Mode mode, int beginBufferSize);
	FarCallSerial(Mode mode);
	virtual ~FarCallSerial();

	bool IsLoading() const {return m_mode == Mode_Loading;}

	FarCallConnectObject * GetNewServerObject(void *newClientObject) const;

private:
	void SetNewObjectsMap(void *map); //此函数提供给FarCallServer使用
	Mode m_mode;

	FarCallSerialInternal * m_internal;
};


class NB_EXPORT FarCallConnectObject : public nbObject
{
	friend class FarCallServer;
	friend class FarCallClient;

public:
	class Iterator
	{
	public:
		FarCallConnectObject & operator *() const
		{
			return m_isClient ? *(FarCallConnectObject *)m_client : *(FarCallConnectObject *)m_server;
		}

		FarCallConnectObject * GetConnectObject() const
		{
			return m_isClient ? (FarCallConnectObject *)m_client : (FarCallConnectObject *)m_server;
		}

		Iterator() : m_isClient(true), m_server(NULL), m_client(NULL) {}
		Iterator(bool isClient) : m_isClient(isClient), m_server(NULL), m_client(NULL) {}

		bool operator != (const Iterator &other) const
		{
			return m_server != other.m_server || m_client != other.m_client || m_isClient != other.m_isClient;
		}

		bool operator == (const Iterator &other) const
		{
			return !(operator != (other));
		}

		DataSerial & Serial(DataSerial &serial)
		{
			if(serial.IsStoring())
			{
				serial << !m_isClient << m_server << m_client;
			}
			else
			{
				serial >> m_isClient >> m_server >> m_client;

				if(!m_isClient && m_server == NULL)
				{
					FarCallSerial *fcs = dynamic_cast<FarCallSerial *>(&serial);
					if(fcs != NULL) m_server = fcs->GetNewServerObject(m_client);
				}
			}
			return serial;
		}

	private:
		friend class FarCallConnectObject;
		Iterator(bool isClient, void * server, void * client)
			: m_isClient(isClient), m_server(server), m_client(client) {}

		bool m_isClient;
		void * m_server;
		void * m_client;
	};

public:
	FarCallConnectObject(FarCallClient *client, const char * serverName);
	virtual ~FarCallConnectObject(void);

	inline bool IsClient() const {return m_isClient;}
	inline bool IsServer() const {return !m_isClient;}
	FarCallClient * GetClient() const;
	FarCallServer * GetServer() const;

	Iterator ToIterator() const
	{
	//	if(m_isClient)
	//	{
	//		const_cast<FarCallConnectObject *>(this)->SureFarConnectObject();
	//	}

		return Iterator(m_isClient,
			m_isClient ? m_pFarConnectObject : (void *)this,
			m_isClient ? (void *)this : m_pFarConnectObject);
	}

public: //测试
	class BaseParam
	{
	public:
		virtual ~BaseParam() {}
		virtual void Serial(FarCallSerial &serial) = 0;
		virtual bool HasReturn() const {return true;}
	};
	typedef GenericVariant (FarCallConnectObject:: *funConverNoParam)();

	typedef GenericVariant (FarCallConnectObject:: *funConver)(BaseParam &param);
	typedef void (FarCallConnectObject:: *funConverNoReturn)(BaseParam &param);

	class BaseFunInfo
	{
	public:
		//获取有返回值类型的功能函数的地址（服务端使用）
		virtual funConver GetFun() const {return NULL;}

		//获取没有返回值类型的功能函数的地址（服务端使用）
		virtual funConverNoReturn GetFunNoReturn() const {return NULL;}

		//获取函数对象相对于类头的偏移地址（客户端和服务端均需要使用）
		virtual long long GetOffset() const = 0;

		//创建返回参数对象（服务端使用）
		virtual BaseParam * CreateReceiveParam() const = 0;

		//释放放回参数对象（服务端使用）
		virtual void FreeReceiveParam(BaseParam *param) const = 0;
	};

	class NoContentParam : public BaseParam
	{
	public:
		virtual void Serial(FarCallSerial &serial) {}
	};

	class BaseEventParam : public nbEventParam
	{
	public:
		virtual void SerialParam(FarCallSerial &serial){}
		virtual void SerialReturn(FarCallSerial &serial){}
	};

	class NB_EXPORT BaseEventInfo
	{
	public:
		//服务端的函数
		void Send(BaseEventParam &param);

		//客户端的函数
		void Dispatch(nbEventParam &param);

		virtual nbEventBase * GetEventObject() = 0;
	//	virtual funConver GetFun() const = 0;
		virtual long long GetOffset() const = 0;
		virtual BaseEventParam * CreateReceiveParam() const = 0;
		virtual void FreeReceiveParam(BaseEventParam *param) const = 0;
	};

	template<class ParamT>
	class EventInfoT : public BaseEventInfo
	{
	public:
		template<class funType>
		void Add(nbObject *pAccepter, funType fun)
		{
			m_event.Add(pAccepter, fun);
		}

		template<class funType>
		void Sub(nbObject *pAccepter, funType fun)
		{
			m_event.Sub(pAccepter, fun);
		}

		void Sub(nbObject *pAccepter)
		{
			m_event.Sub(pAccepter);
		}

		nbEventBase * GetEventObject() {return &m_event;}
		virtual BaseEventParam * CreateReceiveParam() const
		{
			return new ParamT;
		}

		virtual void FreeReceiveParam(BaseEventParam *param) const
		{
			delete param;
		}

	private:
		nbEvent<ParamT> m_event;
	};

protected:
	FarCallConnectObject(void);

	void CallFun(BaseFunInfo *fun, BaseParam &param, FarCallSerial &resultSerial);
	void CallFun(BaseFunInfo *fun, BaseParam &param);

	template<class ResultT>
	void CallFunT(BaseFunInfo *fun, BaseParam &param, ResultT &result)
	{
		nb::System::FarCallSerial resultSerial(nb::System::FarCallSerial::Mode_Storing);
		CallFun(fun, param, resultSerial);

	// 这里不做转换了
	//	nb::System::FarCallSerial rs(nb::System::FarCallSerial::Mode_Loading);
	//	rs.UseExternData((unsigned char *)resultSerial.GetBuffer(), resultSerial.GetDataSize());

	//	bool isInvalidate;
	//	rs >> isInvalidate;
	//	if(!isInvalidate)
	//	{
	//		NB_THROW_EXCEPTION("远端服务已关闭");
	//	}

		resultSerial >> result;
	}

private:

	void OnCallFun(long long funOffset, FarCallSerial &paramSerial, FarCallSerial &resultParamSerial);
	void OnCallFun(long long funOffset, FarCallSerial &paramSerial);
	void OnEvent(long long eventObjectOffset, FarCallSerial &paramSerial, FarCallSerial &resultParamSerial);

	void ClientSetFarConnectObject(FarCallConnectObject *farConn);

	void SureFarConnectObject();

	union
	{
		FarCallServer *m_server;
		FarCallClient *m_client;
	};

	bool m_isClient;

//	std::string m_serverName;
	void *m_pFarConnectObject;
};
typedef nbObjectPtrDerive<FarCallConnectObject, nbObjectPtr> FarCallConnectObjectPtr;


inline DataSerial & operator >> (DataSerial &serial, FarCallConnectObject::Iterator &itor)
{
	return itor.Serial(serial);
}

inline DataSerial & operator << (DataSerial &serial, FarCallConnectObject::Iterator &itor)
{
	return itor.Serial(serial);
}

class NB_EXPORT FarCallDataSendException : public nb::Core::Exception
{
public:
	FarCallDataSendException(const char *err);

};
typedef nbObjectPtrDerive<FarCallDataSendException, nb::Core::ExceptionPtr> FarCallDataSendExceptionPtr;

class FarCallServerInternal;
class NB_EXPORT FarCallServer : public nbObject
{
	friend class FarCallServerInternal;

	template<class T>
	FarCallConnectObject * CreateConnectObject(void * clientConnectObject)
	{
		FarCallConnectObject *conn = new T();
		conn->m_pFarConnectObject = clientConnectObject;
		conn->m_server = this;
		return conn;
	}

	template<class T, class InterT>
	FarCallConnectObject * CreateConnectObject(void * clientConnectObject)
	{
		FarCallConnectObject *conn = (InterT *)(new T());
		conn->m_pFarConnectObject = clientConnectObject;
		conn->m_server = this;
		return conn;
	}

	typedef FarCallConnectObject * (FarCallServer:: *CX)(void * clientConnectObject);

public:
	FarCallServer();
	virtual ~FarCallServer();

	template<class T>
	void RegServer(const char * name)
	{
		_RegServer(name, &FarCallServer::CreateConnectObject<T>);
	}
	template<class T, class InterT>
	void RegServer(const char * name)
	{
		_RegServer(name, &FarCallServer::CreateConnectObject<T, InterT>);
	}
	void _RegServer(const char * name, CX cx);

	FarCallConnectObject * OnAcceptCreateObjectEvent(const char *name, void * clientConnectObject);

	void OnAcceptDestroyObjectEvent(void * conn);

//	void OnCallFun(FarCallClient *client, void *conn, long long funOffset, const unsigned char *paramData, int paramLen, FarCallSerial &resultSerial);

	void AcceptData(const unsigned char *data, int len, FarCallSerial &resultSerial);

	FarCallServerInternal * GetInternal() const {return m_internal;}

	void SendEvent(FarCallConnectObject *conn, long long funOffset, FarCallConnectObject::BaseEventParam &param, FarCallSerial &resultSerial);

	int GetFarConnectionCount() const;

	void GetAllFarConnection(ObjectArray<FarCallConnectObject> &conns) const;

	 //关闭连接，清除数据，不再接受客户端的访问
	void Close();

	bool IsClosed();

public:
	struct ConnectObjectCreatedEventParam : nbEventParam { FarCallConnectObject * m_obj; };
	nbEvent<ConnectObjectCreatedEventParam> ConnectObjectCreatedEvent;

	struct ConnectObjectDestroyingEventParam : nbEventParam { FarCallConnectObject * m_obj; };
	nbEvent<ConnectObjectDestroyingEventParam> ConnectObjectDestroyingEvent;

protected:
//	virtual void SendReturnResultOverride(FarCallSerial &dataSerial) = 0;
	virtual void SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial){}

private:
	static void DisConnectObject(FarCallConnectObject *connectObject);

	FarCallServerInternal *m_internal;
};
typedef nbObjectPtrDerive<FarCallServer, nbObjectPtr> FarCallServerPtr;

class FarCallClientInternal;
class NB_EXPORT FarCallClient : public nbObject
{
//	friend class FarCallConnectObject;
public:
	FarCallClient();
	virtual ~FarCallClient();

	void CallFun(FarCallConnectObject *conn, long long funOffset, FarCallConnectObject::BaseParam &param, FarCallSerial &resultSerial);
	void CallFun(FarCallConnectObject *conn, long long funOffset, FarCallConnectObject::BaseParam &param);
	void * CreateFarObject(FarCallConnectObject *conn, const char * serverName);
	void CreateFarObjectAsyn(FarCallConnectObject *conn, const char *serverName);
	void DestroyFarObject(FarCallConnectObject *conn);
	void DestroyFarObjectAsyn(FarCallConnectObject *conn);

	void AcceptData(const unsigned char *data, int len, FarCallSerial &resultSerial);

	void LimitThreadId(int threadID);

	// 将缓存中的指令立即发送出去
	void Flush();
	void Flush(FarCallSerial &resultSerial);

	virtual void SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial) = 0;

	FarCallServer *m_server;

	// 完成了一次Flash动作
	class OnceFlashedEventParam : public nbEventParam{ };
	nbEvent<OnceFlashedEventParam> OnceFlashedEvent;

private:
	inline void TestTreadId();

	nb::System::FarCallSerial * m_cmdBuffer;
	FarCallClientInternal * m_internal;

	bool m_isLimitThreadId;
	int m_threadId;

};
typedef nbObjectPtrDerive<FarCallClient, nbObjectPtr> FarCallClientPtr;

}}



#define NB_FAR_CALL_FUN(className, funName, paramName, returnType) \
class funName##Info : public BaseFunInfo \
{ \
public: \
	virtual funConver GetFun() const \
	{ \
		return (funConver)&className::funName##Sv; \
	} \
	virtual long long GetOffset() const \
	{ \
		className *pNull = NULL; \
		return (long long)(void *)&pNull->m_##funName##Info; \
	} \
	virtual BaseParam * CreateReceiveParam() const \
	{ \
		return new paramName(); \
	} \
	virtual void FreeReceiveParam(BaseParam *param) const {delete param;} \
} m_##funName##Info; \
virtual returnType funName(paramName &param) \
{ \
	returnType k; \
	CallFunT(&m_##funName##Info, param, k); \
	return k; \
} \
virtual GenericVariant funName##Sv(paramName &param) \
{ \
	return GenericVariant(); \
}


#define NB_FAR_CALL_FUN_NORETURN(className, funName, paramName) \
class funName##Info : public BaseFunInfo \
{ \
public: \
	virtual funConverNoReturn GetFunNoReturn() const \
	{ \
		return (funConverNoReturn)&className::funName##Sv; \
	} \
	virtual long long GetOffset() const \
	{ \
		className *pNull = NULL; \
		return (long long)(void *)&pNull->m_##funName##Info; \
	} \
	virtual BaseParam * CreateReceiveParam() const \
	{ \
		return new paramName(); \
	} \
	virtual void FreeReceiveParam(BaseParam *param) const {delete param;} \
} m_##funName##Info; \
virtual void funName(paramName &param) \
{ \
	CallFun(&m_##funName##Info, param); \
} \
virtual void funName##Sv(paramName &param) \
{ \
}


#define NB_FAR_CALL_FUN_NOARGS(className, funName, returnType) \
class funName##Info : public BaseFunInfo \
{ \
public: \
	virtual funConver GetFun() const \
	{ \
	return (funConver)&className::funName##Sv; \
	} \
	virtual long long GetOffset() const \
	{ \
		className *pNull = NULL; \
		return (long long)(void *)&pNull->m_##funName##Info; \
	} \
	virtual BaseParam * CreateReceiveParam() const \
	{ \
		return NULL; \
	} \
	virtual void FreeReceiveParam(BaseParam *param) const {} \
} m_##funName##Info; \
virtual returnType funName() \
{ \
	NoContentParam param;\
	returnType k; \
	CallFunT(&m_##funName##Info, param, k); \
	return k; \
} \
virtual GenericVariant funName##Sv() \
{ \
	return GenericVariant(); \
}


#define NB_FAR_CALL_EVENT(className, eventName, paramName) \
class eventName##Info : public EventInfoT<paramName> \
{ \
public: \
	virtual long long GetOffset() const \
	{ \
		className *pNull = NULL; \
		return (long long)(void *)&pNull->eventName; \
	} \
} \
eventName; \


namespace nb { namespace System {

class AbcConnectObject : public FarCallConnectObject
{
public:
	AbcConnectObject() {}
	AbcConnectObject(FarCallClient *client) : FarCallConnectObject(client, "Abc") {}

	//typedef int (AbcConnectObject:: *funGetValue)(BaseParam &param);

	class TestParam : public BaseParam
	{
	public:
		int a;
		int b;

	private:
		void Serial(FarCallSerial &serial)
		{
			serial - a - b;
		}
	};
	NB_FAR_CALL_FUN(AbcConnectObject, Test, TestParam, int);

	class AddChildParam : public BaseParam
	{
	public:
		FarCallConnectObject::Iterator m_child;

	private:
		void Serial(FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_child;
			else serial >> m_child;
		}
	};
	NB_FAR_CALL_FUN(AbcConnectObject, AddChild, AddChildParam, int);


	NB_FAR_CALL_FUN_NOARGS(AbcConnectObject, GetChild, FarCallConnectObject::Iterator);





	class GetValueParam : public BaseParam
	{
	public:
		int t;
		int m_width;
		float m_abc;
	private:
		void Serial(FarCallSerial &serial)
		{
			serial - t - m_abc - m_width;
		}
	};
	class GetValueInfo : public BaseFunInfo
	{
	public:
		virtual funConver GetFun() const
		{
			return (funConver)&AbcConnectObject::GetValueSv;
		}
		virtual long long GetOffset() const
		{
			AbcConnectObject *pNull = NULL;
			return (long long)(void *)&pNull->m_GetValueInfo;
		}
		virtual BaseParam * CreateReceiveParam() const
		{
			return new GetValueParam();
		}
		virtual void FreeReceiveParam(BaseParam *param) const {delete param;}
	} m_GetValueInfo;
	virtual int GetValue(GetValueParam &param)
	{
		FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
		CallFun(&m_GetValueInfo, param, resultSerial);

		//这里转换为Loading风格，是否能做到自动转换？？直接使用resultSerial？？
		FarCallSerial rs(FarCallSerial::Mode_Loading);
		rs.UseExternData((unsigned char *)resultSerial.GetBuffer(), resultSerial.GetDataSize());

		int k;
		rs >> k;
		return k;
	}

	virtual GenericVariant GetValueSv(GetValueParam &param)
	{
		return GenericVariant(20);
	}



	class TestEventParam : public BaseEventParam
	{
	public:
		int m_a;
		float m_b;
		virtual void SerialParam(FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_a << m_b;
			else serial >> m_a >> m_b;
		}

		int m_r1;
		float m_r2;
		virtual void SerialReturn(FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_r1 << m_r2;
			else serial >> m_r1 >> m_r2;
		}
	};


	class TestEventInfo : public EventInfoT<TestEventParam>
	{
	public:
		virtual long long GetOffset() const
		{
			AbcConnectObject *pNull = NULL;
			return (long long)(void *)&pNull->TestEvent;
		}
	}
	TestEvent;

	NB_FAR_CALL_EVENT(AbcConnectObject, TestEvet2, TestEventParam);
};

}}

/* 文档Demo

class MyClass : public FarCallConnectObject
{
	class SetValueParam : public BaseParam
	{
	public:
		int m_nNewValue;
	private:
		void Serial(nb::System::FarCallSerial &serial)
		{
			if(serial.IsStoring()) serial << m_nNewValue;
			else serial >> m_nNewValue;
		}
	};

	class SetValueFun : public BaseFunInfo
	{
		//实现BaseFunInfo的虚函数

		virtual long long GetOffset() const
		{
			MyClass *pNull = NULL;
			return (long long)(void *)&pNull->m_SetValue;
		}
	};
	SetValueFun m_SetValue;
	void SetValue(SetValueParam &param) { CallFun(&m_SetValue, param); }
};

//*/
