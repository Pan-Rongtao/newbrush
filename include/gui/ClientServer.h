#pragma once

//#if (!defined _CLIENTSERVER_SERVER_H_) || (!defined _CLIENTSERVER_CLIENT_H_)
//#ifdef NB_TEST_SERVER
//	#define _CLIENTSERVER_SERVER_H_
//#else
//	#define _CLIENTSERVER_CLIENT_H_
//#endif

///#if (_CLIENTSERVER_SERVER_H_ = 1)



#include "core/Object.h"
#include <map>
#include <set>
#include "system/GenericVariant.h"
#include "system/FarCallConnectObject.h"

class xxxxBase;



class xxxxBase
{
public:
	xxxxBase()
	{
	}

	virtual ~xxxxBase() {}

#ifdef NB_TEST_SERVER
	virtual xxxxBase * CreateServerObject() = 0;
#endif
};

#ifdef NB_TEST_SERVER
class xxbb
{
};
#endif

#ifdef NB_TEST_SERVER
class xxxxServer : public xxxxBase
#else
class xxxx : public xxxxBase
#endif
{
public:
	struct SetParam;

#ifdef NB_TEST_SERVER
	typedef void (xxxxServer:: *funSet)(SetParam *p);
#else
	typedef void (xxxx:: *funSet)(SetParam *p);
#endif

	struct SetParam
	{
#ifdef NB_TEST_SERVER
		SetParam() : x(&xxxxServer::Set) {}
#else
		SetParam() : x(&xxxx::Set) {}
#endif
		funSet x;
	};
	class bbbb
	{
		virtual SetParam * CreateParamObject() {return new SetParam();}
	};

#ifdef NB_TEST_SERVER
	virtual void Set(SetParam *p) = 0;
#else
	void Set(SetParam *p) {}
#endif

#ifdef NB_TEST_SERVER
	xxxxServer * m_pServer;
#else
#endif

};

class NB_EXPORT ServerConnect
{
	template<class T>
	xxxxBase * CreateXxxx()
	{
		return new T();
	}

//	typedef xxxxBase * (* fun)();
	typedef xxxxBase * (ServerConnect:: *CX)();

public:
	template<class T>
	void RegServer(std::string name)
	{
		_RegServer(name, &ServerConnect::CreateXxxx<T>);
	}

	void _RegServer(std::string name, CX cx) {m_map[name] = cx;}

private:
	std::map<std::string, CX> m_map;
};


class ClientConnect
{
public:
	template<class T>
	xxxxBase * CreateXxxx()
	{
		return new T();
	}

	typedef xxxxBase * (ClientConnect:: *CX)();

public:
	template<class T>
	void RegServer(std::string name)
	{
		_RegServer(name, &ClientConnect::CreateXxxx<T>);
	}

	void _RegServer(std::string name, CX cx) {m_map[name] = cx;}

private:
	std::map<std::string, CX> m_map;
};

/*
class ServerObjectBase
{
};

template<class T>
class ServerObject : public ServerObjectBase, public T
{
};

class ClientObjectBase
{
};

template<class T>
class ClientObject : public ClientObjectBase
{
};

class abcdInter
{
public:
};

class abcdServerObject : public ServerObject<abcdInter>
{
};*/

class ClientObject;
class ClientServer
{
public:
	ClientServer(void);
	virtual ~ClientServer(void);
};






//#endif
