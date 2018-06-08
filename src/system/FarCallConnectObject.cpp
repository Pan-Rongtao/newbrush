#include "system/FarCallConnectObject.h"
#include "system/Platform.h"
#include "system/String.h"

using namespace nb::System;
using namespace nb::Core;


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
enum FarCallCommand : short
{
	FarCallCommand_CreateFarObject,
	FarCallCommand_CreateFarObject_Asyn,
	FarCallCommand_DestroyFarObject,
	FarCallCommand_DestroyFarObject_Asyn,
	FarCallCommand_CallFun,
	FarCallCommand_CallFun_NoReturn,
	FarCallCommand_Event,

	FarCallCommand_FarPortException,


	FarCallCommand_ReturnIllCmd,

};


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace nb { namespace System {

class FarCallSerialInternal
{
public:
	FarCallSerialInternal() : m_newObjects(NULL) {}

	std::map<void *, FarCallConnectObject *> *m_newObjects;
};

}}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

FarCallSerial::FarCallSerial(Mode mode)
	: m_mode(mode)
{
	m_internal = new FarCallSerialInternal();
}

FarCallSerial::FarCallSerial(Mode mode, int beginBufferSize)
	: DataSerial(beginBufferSize)
	, m_mode(mode)
{
	m_internal = new FarCallSerialInternal();
}

FarCallSerial::~FarCallSerial()
{
	delete m_internal;
}

void FarCallSerial::SetNewObjectsMap(void *map)
{
	m_internal->m_newObjects = (std::map<void *, FarCallConnectObject *> *)map;
}

FarCallConnectObject * FarCallSerial::GetNewServerObject(void *newClientObject) const
{
	if(m_internal->m_newObjects == NULL) return NULL;

	std::map<void *, FarCallConnectObject *>::const_iterator itor = m_internal->m_newObjects->find(newClientObject);
	if(itor != m_internal->m_newObjects->end()) return itor->second;
	else return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void FarCallConnectObject::BaseEventInfo::Send(BaseEventParam &param)
{
	long long offset = GetOffset();
	FarCallConnectObject *pConnect = (FarCallConnectObject *)(((long long)this) - offset);
	if(pConnect->m_isClient) return;

	if(pConnect->m_server == NULL)
	{
		FarCallDataSendExceptionPtr ex = new FarCallDataSendException("没有接上远程连接");
		throw ex;
	}

	nb::System::FarCallSerial resultSerial(nb::System::FarCallSerial::Mode_Storing);
	pConnect->m_server->SendEvent(pConnect, offset, param, resultSerial);

	nb::System::FarCallSerial rs(nb::System::FarCallSerial::Mode_Loading);
	rs.UseExternData((unsigned char *)resultSerial.GetBuffer(), resultSerial.GetDataSize());

	short cmdShort;
	rs >> cmdShort;
	FarCallCommand cmd = (FarCallCommand)cmdShort;
	switch(cmd)
	{
	case FarCallCommand_Event:
		param.SerialReturn(rs);
		break;
	case FarCallCommand_FarPortException:
		{
			nb::System::String msg;
			rs >> msg;
			FarCallFarPortExceptionPtr ex = new FarCallFarPortException(msg.ToUtf8().GetData());
			throw ex;
		}
		break;
	default:
		NB_THROW_EXCEPTION("error cmd.");
		break;
	}
}

void FarCallConnectObject::BaseEventInfo::Dispatch(nbEventParam &param)
{
	GetEventObject()->Dispatch(param);
}


FarCallConnectObject::FarCallConnectObject(FarCallClient *client, const char * serverName)
	: m_client(client)
	, m_isClient(true)
{
//	m_serverName = serverName;
/*	void *serverConnectObject = m_client->CreateFarObject(this, serverName);// m_client->m_server->OnAcceptCreateObjectEvent(serverName, this);
	m_pFarConnectObject = serverConnectObject;

	if(m_pFarConnectObject == NULL)
	{
		NB_THROW_EXCEPTION("FarCallConnectObject::FarCallConnectObject  远程服务器未提供相应的服务 ");
	}*/


	// 异步方式
	m_pFarConnectObject = NULL;
	m_client->CreateFarObjectAsyn(this, serverName);
}

FarCallConnectObject::FarCallConnectObject(void)
	: m_isClient(false)
{
}

FarCallConnectObject::~FarCallConnectObject(void)
{
	//m_client->m_server->OnAcceptDestroyObjectEvent(m_pFarConnectObject);

	if(m_isClient)
	{
		//假如FarConnectObjects，在删除所在的异步指令包中，可能包含有该Object的Create指令，而Create指令的返回值会操作改Object，将导致操作非法内存
		//所以，必须先调用SureFarConnectObject()，确保Create指令先执?
		SureFarConnectObject(); 

		m_client->DestroyFarObjectAsyn(this);
	}
}

void FarCallConnectObject::ClientSetFarConnectObject(FarCallConnectObject *farConn)
{
	m_pFarConnectObject = farConn;

	if(m_pFarConnectObject == NULL)
	{
		NB_THROW_EXCEPTION("FarCallConnectObject::ClientSetFarConnectObject 远程服务器未提供相应的服务 ");
	}
}

void FarCallConnectObject::CallFun(BaseFunInfo *fun, BaseParam &param, FarCallSerial &resultSerial)
{
//	SureFarConnectObject();

	long long offset = fun->GetOffset();
	//FarCallSerial serial(FarCallSerial::Mode_Storing);
	//param.Serial(serial);
	//serial.Data

//	m_client->CallFun(this, offset, serial.GetBuffer(), serial.GetDataSize(), resultSerial);

	m_client->CallFun(this, offset, param, resultSerial);
}

void FarCallConnectObject::CallFun(BaseFunInfo *fun, BaseParam &param)
{
//	SureFarConnectObject();

	long long offset = fun->GetOffset();
	m_client->CallFun(this, offset, param);
}

void FarCallConnectObject::OnCallFun(long long funOffset, FarCallSerial &paramSerial, FarCallSerial &resultParamSerial)
{
	long long funObjectInt = ((long long)this) + funOffset;

	FarCallConnectObject::BaseFunInfo *fun = (FarCallConnectObject::BaseFunInfo *)funObjectInt;
	FarCallConnectObject::BaseParam *receiveParam = fun->CreateReceiveParam();

	if(receiveParam != NULL)
	{
		receiveParam->Serial(paramSerial);

		GenericVariant result = (this->*(fun->GetFun()))(*receiveParam);

		result.StoreData(resultParamSerial);

		//delete receiveParam;
		fun->FreeReceiveParam(receiveParam);
	}
	else
	{
		GenericVariant result = (this->*((funConverNoParam)fun->GetFun()))();
		result.StoreData(resultParamSerial);
	}
}

void FarCallConnectObject::OnCallFun(long long funOffset, FarCallSerial &paramSerial)
{
	long long funObjectInt = ((long long)this) + funOffset;

	FarCallConnectObject::BaseFunInfo *fun = (FarCallConnectObject::BaseFunInfo *)funObjectInt;
	FarCallConnectObject::BaseParam *receiveParam = fun->CreateReceiveParam();

	if(receiveParam != NULL)
	{
		receiveParam->Serial(paramSerial);

		(this->*(fun->GetFunNoReturn()))(*receiveParam);

		//delete receiveParam;
		fun->FreeReceiveParam(receiveParam);
	}
	else
	{
		(this->*((funConverNoParam)fun->GetFunNoReturn()))();
	}
}

void FarCallConnectObject::OnEvent(long long eventObjectOffset, FarCallSerial &paramSerial, FarCallSerial &resultParamSerial)
{
	long long eventObjectInt = ((long long)this) + eventObjectOffset;
	FarCallConnectObject::BaseEventInfo *eventObject = (FarCallConnectObject::BaseEventInfo *)eventObjectInt;
	
	BaseEventParam *param = eventObject->CreateReceiveParam();
	param->SerialParam(paramSerial);

	eventObject->Dispatch(*param);

	param->SerialReturn(resultParamSerial);
	
	eventObject->FreeReceiveParam(param);
}


FarCallClient * FarCallConnectObject::GetClient() const
{
	return IsClient() ? m_client : NULL;
}

FarCallServer * FarCallConnectObject::GetServer() const
{
	return IsClient() ? NULL : m_server;
}

void FarCallConnectObject::SureFarConnectObject()
{
	if(m_pFarConnectObject != NULL) return;

	if(IsClient())
	{
		m_client->Flush();

		if(m_pFarConnectObject == NULL)
		{
			NB_THROW_EXCEPTION("FarCallConnectObject::SureFarConnectObject 没有连接到远程对象 ");
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace nb { namespace System {
class FarCallClientInternal
{
public:
	FarCallClientInternal() {}
	~FarCallClientInternal()
	{
//		std::list<AsynCmd *>::iterator itor = m_cmds.begin();
//		for(; itor != m_cmds.end(); itor++)
//		{
//			AsynCmd * cmd = *itor;
//			delete cmd;
//		}
	}

//	class AsynCmd
//	{
//	};

//	class CallFunAsynCmd : public AsynCmd
//	{
//	};

//	class CreateConnectObjectAsynCmd : public AsynCmd
//	{
//	};

//	std::list<AsynCmd *> m_cmds;
};
}}

FarCallClient::FarCallClient()
	: m_threadId(0)
	, m_isLimitThreadId(false)
{
	m_cmdBuffer = new nb::System::FarCallSerial(nb::System::FarCallSerial::Mode_Storing);
	m_internal = new FarCallClientInternal();
}

FarCallClient::~FarCallClient()
{
	delete m_cmdBuffer;
	delete m_internal;
}

void FarCallClient::CallFun(FarCallConnectObject *conn, long long funOffset, FarCallConnectObject::BaseParam &param, FarCallSerial &resultSerial)
{
	TestTreadId();

//	FarCallSerial serial(FarCallSerial::Mode_Storing);
//	serial << (short)FarCallCommand_CallFun << conn->m_pFarConnectObject << funOffset;
//	param.Serial(serial);

//	SendDataOverride(serial, resultSerial);

	*m_cmdBuffer << (short)FarCallCommand_CallFun << conn->m_pFarConnectObject << conn << funOffset;
	param.Serial(*m_cmdBuffer);
	Flush(resultSerial);
}

void FarCallClient::CallFun(FarCallConnectObject *conn, long long funOffset, FarCallConnectObject::BaseParam &param)
{
	TestTreadId();

	*m_cmdBuffer << (short)FarCallCommand_CallFun_NoReturn << conn->m_pFarConnectObject << conn << funOffset;
	param.Serial(*m_cmdBuffer);

//	FarCallSerial serial(FarCallSerial::Mode_Storing);
//	serial << (short)FarCallCommand_CallFun_NoReturn << conn->m_pFarConnectObject << funOffset;
//	param.Serial(serial);

//	FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
//	SendDataOverride(serial, resultSerial);
}

void FarCallClient::Flush()
{
	TestTreadId();

	if(!m_cmdBuffer->IsPosEnd())
	{
		FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
		Flush(resultSerial);
	}
}

void FarCallClient::Flush(FarCallSerial &resultSerial)
{
	TestTreadId();

	if(!m_cmdBuffer->IsPosEnd())
	{
//		FarCallSerial resultSerial(FarCallSerial::Mode_Storing);

		nb::System::FarCallSerial * buffer = m_cmdBuffer;
//		int k = m_cmdBuffer->GetDataSize();
//		nb::System::FarCallSerial * buffer = new nb::System::FarCallSerial(nb::System::FarCallSerial::Mode_Storing, k);
//		buffer->Write(m_cmdBuffer->GetBuffer(), k);

		m_cmdBuffer = new nb::System::FarCallSerial(nb::System::FarCallSerial::Mode_Storing);

		SendDataOverride(*buffer, resultSerial);
		delete buffer;  //没有使用智能指针，如果中途抛出异常，将无法执行到delete

		bool isInvalidate;
		resultSerial >> isInvalidate;
		if(!isInvalidate)
		{
			NB_THROW_EXCEPTION("远端服务已关闭 ");
		}


		while(!resultSerial.IsPosEnd())
		{
			short cmdShort;
			resultSerial >> cmdShort;

			FarCallCommand cmd = (FarCallCommand)cmdShort;
			switch(cmd)
			{
			case FarCallCommand_CreateFarObject_Asyn:
				{
					void * farConn;
					void * conn;
					resultSerial >> farConn >> conn;
					((FarCallConnectObject *)conn)->ClientSetFarConnectObject((FarCallConnectObject *)farConn);
				}
				break;
			case FarCallCommand_DestroyFarObject_Asyn:
				break;
			case FarCallCommand_CallFun_NoReturn:
				break;
			default: // 同步指令
				return;

			case FarCallCommand_ReturnIllCmd:
				NB_THROW_EXCEPTION("远端服务拒绝非法的指令 ");
			}
		}

		OnceFlashedEventParam param;
		OnceFlashedEvent.Dispatch(param);
	}
}

void * FarCallClient::CreateFarObject(FarCallConnectObject *conn, const char *serverName)
{
	TestTreadId();

/*	FarCallSerial serial(FarCallSerial::Mode_Storing);
	serial << (short)FarCallCommand_CreateFarObject << serverName << conn;

	FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
	SendDataOverride(serial, resultSerial);

	FarCallSerial rs(FarCallSerial::Mode_Loading);
	rs.UseExternData(const_cast<unsigned char *>(resultSerial.GetBuffer()), resultSerial.GetDataSize());

	bool isInvalidate;
	rs >> isInvalidate;
	if(!isInvalidate)
	{
		NB_THROW_EXCEPTION("远端服务已关闭 ");
	}

	void * farConn;
	rs >> farConn;
	return farConn;*/

	*m_cmdBuffer << (short)FarCallCommand_CreateFarObject << (void *)NULL << conn << serverName;
	FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
	Flush(resultSerial);

	void * farConn;
	resultSerial >> farConn;
	return farConn;
}

void FarCallClient::CreateFarObjectAsyn(FarCallConnectObject *conn, const char *serverName)
{
	TestTreadId();

	*m_cmdBuffer << (short)FarCallCommand_CreateFarObject_Asyn << (void *)NULL << conn << serverName;
}

void FarCallClient::DestroyFarObject(FarCallConnectObject *conn)
{
	TestTreadId();

/*	FarCallSerial serial(FarCallSerial::Mode_Storing);
	serial << (short)FarCallCommand_DestroyFarObject << conn->m_pFarConnectObject;

	FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
	SendDataOverride(serial, resultSerial);*/

	*m_cmdBuffer << (short)FarCallCommand_DestroyFarObject << conn->m_pFarConnectObject << conn;
	FarCallSerial resultSerial(FarCallSerial::Mode_Storing);
	Flush(resultSerial);
}

void FarCallClient::DestroyFarObjectAsyn(FarCallConnectObject *conn)
{
	TestTreadId();

	*m_cmdBuffer << (short)FarCallCommand_DestroyFarObject_Asyn << conn->m_pFarConnectObject << conn;
}

void FarCallClient::AcceptData(const unsigned char *data, int len, FarCallSerial &resultSerial)
{
	FarCallSerial dataSerial(FarCallSerial::Mode_Loading);
	dataSerial.UseExternData(const_cast<unsigned char *>(data), len);

//	FarCallSerial resultSerial(FarCallSerial::Mode_Storing);

	short cmdShort;
	dataSerial >> cmdShort;
	FarCallCommand cmd = (FarCallCommand)cmdShort;

	try{
		switch(cmd)
		{
		case FarCallCommand_Event:
			{
				void * connID;
				long long funOffset;

				dataSerial  >> connID >> funOffset;

				FarCallConnectObject *conn = (FarCallConnectObject *)connID;

				resultSerial << (short)cmd;

				conn->OnEvent(funOffset, dataSerial, resultSerial);
			}
			break;
		}
	}
	catch(FarCallFarPortExceptionPtr &ex)
	{
		resultSerial.ClearData();

		nb::System::String msg = ex->GetErrorMessageData();
		resultSerial << (short)FarCallCommand_FarPortException << msg;
	}
}

void FarCallClient::LimitThreadId(int threadId)
{
	m_isLimitThreadId = true;
	m_threadId = threadId;
}

inline void FarCallClient::TestTreadId()
{
	if(m_isLimitThreadId)
	{
		if(m_threadId != nb::System::Platform::GetCurrentThreadId())
		{
			char c[1024];
			sprintf(c, "FarCallClient is not called in the limited thread. LimitedThreadId=[%u] CurrentThreadId=[%u]",
				m_threadId, nb::System::Platform::GetCurrentThreadId());

			NB_THROW_EXCEPTION(c);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace nb { namespace System {
class FarCallServerInternal
{
public:
	class AsynNewObjectMap : public nbObject
	{
	public:
		std::map<void *, FarCallConnectObject *> m_map;
	};
	typedef nbObjectPtrDerive<AsynNewObjectMap, nbObjectPtr> AsynNewObjectMapPtr;

public:
	FarCallServerInternal() : m_isClosed(false) {}
	~FarCallServerInternal() {Close();}
	inline bool IsClosed() const {return m_isClosed;}
	inline void Close()
	{
		if(m_isClosed) return;
		m_isClosed = true;

		std::set<FarCallConnectObjectPtr>::iterator itor = m_setConnects.begin();
		for(; itor != m_setConnects.end(); itor++)
		{
			FarCallConnectObject *conn = *itor;
			FarCallServer::DisConnectObject(conn);
	//		delete conn;
		}
		m_setConnects.clear();
	}

	
	void GetAllFarConnection(ObjectArray<FarCallConnectObject> &conns) const
	{
		std::set<FarCallConnectObjectPtr>::const_iterator itor = m_setConnects.begin();
		for(; itor != m_setConnects.end(); itor++)
		{
			conns.Add(*itor);
		}
	}


	std::map<std::string, FarCallServer::CX> m_map;
	std::set<FarCallConnectObjectPtr> m_setConnects;
	bool m_isClosed;

	//用于保存AcceptData时，异步传递的New Object（这时候ServID=NULL）
	AsynNewObjectMapPtr m_asynNewObjects;
};

}}


FarCallDataSendException::FarCallDataSendException(const char *err)
	: Exception(err)
{
}

FarCallServer::FarCallServer()
{
	m_internal = new FarCallServerInternal();
}

FarCallServer::~FarCallServer()
{
	delete m_internal;
}

void FarCallServer::Close()
{
	m_internal->Close();
}

bool FarCallServer::IsClosed()
{
	return m_internal->IsClosed();
}

void FarCallServer::_RegServer(const char * name, CX cx)
{
	m_internal->m_map[name] = cx;
}

int FarCallServer::GetFarConnectionCount() const
{
	return m_internal->m_setConnects.size();
}

void FarCallServer::GetAllFarConnection(ObjectArray<FarCallConnectObject> &conns) const
{
	m_internal->GetAllFarConnection(conns);
}


FarCallConnectObject * FarCallServer::OnAcceptCreateObjectEvent(const char *name, void * clientConnectObject)
{
	std::map<std::string, FarCallServer::CX>::const_iterator itor = m_internal->m_map.find(name);
	if(itor != m_internal->m_map.end())
	{
		CX x = itor->second;
		FarCallConnectObject *conn = (this->*(x))(clientConnectObject);

		m_internal->m_setConnects.insert(conn);
		return conn;
	}
	else
	{
		return NULL;
	}
}

//#include "System/Platform.h"
void FarCallServer::AcceptData(const unsigned char *data, int len, FarCallSerial &resultSerial)
{
//	int kk = nb::System::Platform::GetTickCount();
//	printf("hbs is SSS %d\r\n", kk);

////	int k = nb::System::Platform::GetTickCount();
	int CreateFarObjectTotal = 0;
	int FunCallTotal = 0;

	if(IsClosed())
	{
		resultSerial << false;
		return;
	}
	else
	{
		resultSerial << true;
	}

	FarCallSerial dataSerial(FarCallSerial::Mode_Loading);
	dataSerial.UseExternData(const_cast<unsigned char *>(data), len);


//	std::map<void *, FarCallConnectObject *> asynNewObjects;

	bool isCreateAsynNewObjects = false;
	if(m_internal->m_asynNewObjects == NULL)
	{
		m_internal->m_asynNewObjects = new FarCallServerInternal::AsynNewObjectMap();
		isCreateAsynNewObjects = true;
	}

int cmdCount = 0;

	dataSerial.SetNewObjectsMap(&m_internal->m_asynNewObjects->m_map);

	while(!dataSerial.IsPosEnd())
	{
		short cmdShort;
		dataSerial >> cmdShort;
		FarCallCommand cmd = (FarCallCommand)cmdShort;


		void *connCliID;
		void *connSevID;
		dataSerial >> connSevID >> connCliID;

		if(connSevID == NULL && cmd == FarCallCommand_DestroyFarObject_Asyn)
		{
			resultSerial << (short)FarCallCommand_ReturnIllCmd;
			goto loop_End;
		}

		if(connSevID == NULL && cmd != FarCallCommand_CreateFarObject && cmd != FarCallCommand_CreateFarObject_Asyn)
		{
			std::map<void *, FarCallConnectObject *>::iterator itor = m_internal->m_asynNewObjects->m_map.find(connCliID);
			if(itor == m_internal->m_asynNewObjects->m_map.end())
			{
				resultSerial << (short)FarCallCommand_ReturnIllCmd;
				goto loop_End;
			}

			connSevID = itor->second;
		}

		resultSerial << cmdShort;

		switch(cmd)
		{
		case FarCallCommand_CreateFarObject:
			{
				std::string name;
				dataSerial >> name;
				FarCallConnectObject *conn = OnAcceptCreateObjectEvent(name.data(), connCliID);
				resultSerial << conn;

				ConnectObjectCreatedEventParam param;
				param.m_obj = conn;
				ConnectObjectCreatedEvent.Dispatch(param);

			}
			break;
		case FarCallCommand_CreateFarObject_Asyn:
			{
				int bb = nb::System::Platform::GetTickCount();
				std::string name;
				dataSerial >> name;
				FarCallConnectObject *conn = OnAcceptCreateObjectEvent(name.data(), connCliID);
				resultSerial << conn << connCliID;

				CreateFarObjectTotal += nb::System::Platform::GetTickCount() - bb; 
				m_internal->m_asynNewObjects->m_map[connCliID] = conn;

				ConnectObjectCreatedEventParam param;
				param.m_obj = conn;
				ConnectObjectCreatedEvent.Dispatch(param);
			}
			break;
		case FarCallCommand_DestroyFarObject:
			{
				FarCallConnectObjectPtr connSev = (FarCallConnectObject *)connSevID;

				ConnectObjectDestroyingEventParam param;
				param.m_obj = connSev;
				ConnectObjectDestroyingEvent.Dispatch(param);

				OnAcceptDestroyObjectEvent(connSev);
			}
			break;
		case FarCallCommand_DestroyFarObject_Asyn:
			{
				FarCallConnectObjectPtr connSev = (FarCallConnectObject *)connSevID;

				ConnectObjectDestroyingEventParam param;
				param.m_obj = connSev;
				ConnectObjectDestroyingEvent.Dispatch(param);

				OnAcceptDestroyObjectEvent(connSev);

			////	asynNewObjects.erase(connCliID);
			}
			break;
		case FarCallCommand_CallFun:
			{
				long long funOffset;
				dataSerial  >> funOffset;

				FarCallConnectObjectPtr connSev = (FarCallConnectObject *)connSevID;

				connSev->OnCallFun(funOffset, dataSerial, resultSerial);
			}
			break;
		case FarCallCommand_CallFun_NoReturn:
			{
				int bb = nb::System::Platform::GetTickCount();

				long long funOffset;
				dataSerial  >> funOffset;

				FarCallConnectObjectPtr connSev = (FarCallConnectObject *)connSevID;

				connSev->OnCallFun(funOffset, dataSerial);

				FunCallTotal += nb::System::Platform::GetTickCount() - bb;
			}
			break;
		}
cmdCount++;
	}

loop_End:
	if(isCreateAsynNewObjects)
	{
		m_internal->m_asynNewObjects = NULL;
	}

//	int xxxx = nb::System::Platform::GetTickCount() - k;
//printf("FarCallServer::AcceptData---xxxx[%d], cmdCount[%d]\r\n", xxxx, cmdCount);

//	SendReturnResultOverride(resultSerial);
}

void FarCallServer::OnAcceptDestroyObjectEvent(void * conn)
{
	FarCallConnectObject *c = (FarCallConnectObject *)conn;
	std::set<FarCallConnectObjectPtr>::iterator itor = m_internal->m_setConnects.find(c);
	if(itor != m_internal->m_setConnects.end())
	{
	//	FarCallConnectObject *conn = *itor;
	//	delete c;

		m_internal->m_setConnects.erase(itor);
	}
}

/*
void FarCallServer::OnCallFun(FarCallClient *client, void *conn, long long funOffset, const unsigned char *paramData, int paramLen, FarCallSerial &resultSerial)
{
//	ConnectObject *c = (ConnectObject *)conn;
//	c->OnCallFun(funOffset, paramData, paramLen, resultSerial);

//	long long funObjectInt = ((long long)conn) + funOffset;

//	ConnectObject::BaseFunInfo *fun = (ConnectObject::BaseFunInfo *)funObjectInt;
//	ConnectObject::BaseParam *receiveParam = fun->CreateReceiveParam();
//	(c->*(fun->GetFun()))(*receiveParam);

//	delete receiveParam;
//	BaseFun
}
*/

void FarCallServer::SendEvent(FarCallConnectObject *conn, long long funOffset, FarCallConnectObject::BaseEventParam &param, FarCallSerial &resultSerial)
{
	if(IsClosed())
	{
		FarCallDataSendExceptionPtr ex = new FarCallDataSendException("服务已停止，可能是客户端的连接已断开 ");
		throw ex;
	}

	FarCallSerial serial(FarCallSerial::Mode_Storing);
	serial << (short)FarCallCommand_Event << conn->m_pFarConnectObject << funOffset;
	param.SerialParam(serial);

	try{
		SendDataOverride(serial, resultSerial);
	}
	catch(FarCallDataSendExceptionPtr &ex)
	{
		//NB_OUTA(ex->GetErrorMessage().data());
		throw ex;
	}

}

void FarCallServer::DisConnectObject(FarCallConnectObject *connectObject)
{
	connectObject->m_server = NULL;
}
