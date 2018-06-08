#pragma once

#include "OriginObject.h"
#include <list>

#include "Exception.h"

struct nbEventParam //: public nbObject
{
public:
	nbEventParam() : m_bHandled(false) {}
	virtual ~nbEventParam() {}

	bool m_bHandled;
};

template<class T>
struct nbEventParamT :public nbEventParam
{
public:
	T * m_sender;
};

class nbEventPrivate;

class NB_CORE_DECLSPEC_X_INTERFACE nbEventException : public nb::Core::Exception
{
public:
	typedef nbObjectPtrDerive<nbEventException, nb::Core::ExceptionPtr> Ptr;

	nbEventException(){}
	nbEventException(char *pMessage) : nb::Core::Exception(pMessage){}
};

class NB_CORE_DECLSPEC_X_INTERFACE nbEventBase : public nb::Core::RefObject
{
public:
	friend class nbEventPrivate;

	typedef void (nbObject::* funAccepterBase)();

	nbEventBase(void);
	virtual ~nbEventBase(void);


	void Add(nbObject *pAccepter, funAccepterBase pfun);
	void Sub(nbObject *pAccepter, funAccepterBase pfun);
	void Sub(nbObject *pAccepter);
	bool IsExist(nbObject *pAccepter, funAccepterBase pfun) const;
	void Dispatch(nbEventParam &param);

	bool HasAccepter() const;

	nbEventPrivate * GetPrivate() const;

protected:
	virtual void DispatchTrigger(nbObject *pAccepter, funAccepterBase pfun, nbEventParam &param) const {}

private:

	struct ItemInfo
	{
		nbObject *m_pAccepter;
		funAccepterBase m_pfun;
	};

	ItemInfo *m_pFirstItem;
	NB_LINUX_STD std::list<ItemInfo *> *m_plstItems;

	nbEventPrivate *m_private;
};

//template<class ParamType>
//class NB_EXPORT_NO nbTestEvent : public nbEventBase
//{
//public:
//};

template<class ParamType>
class NB_EXPORT_NO nbEvent : public nbEventBase
{
public:
	typedef void (nbObject::* funAccepterConvert)(ParamType &param);

	template<class funType>
	void Add(nbObject *pAccepter, funType fun)
	{
		funAccepterConvert pfunConvert = static_cast<funAccepterConvert>(fun);
		funAccepterBase funBase = (funAccepterBase )pfunConvert;
		nbEventBase::Add(pAccepter, funBase);
	}

	template<class funType>
	void Sub(nbObject *pAccepter, funType fun)
	{
		funAccepterConvert pfunConvert = static_cast<funAccepterConvert>(fun);
		funAccepterBase funBase = (funAccepterBase )pfunConvert;
		nbEventBase::Sub(pAccepter, funBase);
	}

	void Sub(nbObject *pAccepter)
	{
		nbEventBase::Sub(pAccepter);
	}

	void DispatchTrigger(nbObject *pAccepter, funAccepterBase pfun, nbEventParam &param) const
	{
		ParamType *paramT = dynamic_cast<ParamType *>(&param);
		if(paramT == NULL) NB_THROW_EXCEPTION("无效的参数类型。");

		funAccepterConvert pfunT = (funAccepterConvert)pfun;

		(pAccepter->*(pfunT))(*paramT);
	}
};


///////////////////////////////////////////////////////////////////////////////
//
// 包含如下额外功能的事件：
//
//     监测Accepter改变，并通过虚函数接口通知外部
//

class IWatchAccepterEventWatcher
{
public:
	virtual void OnEventAccepterChanged(nbEventBase *eventObject) = 0;
};


template<class ParamType>
class NB_EXPORT_NO nbWatchAccepterEvent : public nbEvent<ParamType>
{
public:

	nbWatchAccepterEvent() : m_watch(NULL) {}

	void SetWatch(IWatchAccepterEventWatcher *watch)
	{
		m_watch = watch;
	}

	template<class funType>
	void Add(nbObject *pAccepter, funType fun)
	{
		nbEvent<ParamType>::Add(pAccepter, fun);
		if(m_watch != NULL) m_watch->OnEventAccepterChanged(this);
	}

	template<class funType>
	void Sub(nbObject *pAccepter, funType fun)
	{
		nbEvent<ParamType>::Sub(pAccepter, fun);
		if(m_watch != NULL) m_watch->OnEventAccepterChanged(this);
	}

	void Sub(nbObject *pAccepter)
	{
		nbEvent<ParamType>::Sub(pAccepter);
		if(m_watch != NULL) m_watch->OnEventAccepterChanged(this);
	}

private:
	IWatchAccepterEventWatcher * m_watch;
};

class NB_CORE_DECLSPEC_X_INTERFACE nbEventBaseTest  
{
public:
	nbEventBaseTest();
	virtual ~nbEventBaseTest();
};

template<class ParamType>
class NB_CORE_DECLSPEC_X_INTERFACE nbEventTest : public nbEventBaseTest
{
public:
	nbEventTest(){}
	void aa(){}
};
