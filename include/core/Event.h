#pragma once
#include <list>
#include "Object.h"
#include "OriginObject.h"
#include "Exception.h"

struct nbEventParam
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

class NB_API nbEventBase : public nb::core::RefObject
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
	std::list<ItemInfo *> *m_plstItems;

	nbEventPrivate *m_private;
};

template<class ParamType>
class nbEvent : public nbEventBase
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
class nbWatchAccepterEvent : public nbEvent<ParamType>
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

#include <vector>
#include <functional>
namespace nb{ namespace core{

template<class ArgsT>
class Event
{
public:
	void addHandler(std::function<void(const ArgsT &args)> handler)
	{
		m_handlers.push_back(handler);
	}

	void removeHandler(std::function<void(const ArgsT &args)> handler)
	{
		for (auto iter = m_handlers.begin(); iter != m_handlers.end();)
		{
			if (iter->target_type() == handler.target_type())
			{
				iter = m_handlers.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void dispatch(const ArgsT &args)
	{
		for (int i = 0; i != m_handlers.size(); ++i)
			if (m_handlers[i])
				m_handlers[i](args);
	}

	void operator += (std::function<void(const ArgsT &args)> handler)
	{
		addHandler(handler);
	}

	void operator -=(std::function<void(const ArgsT &args)> handler)
	{
		remove(handler);
	}

private:
	std::vector<std::function<void(const ArgsT &)>>	m_handlers;
};

}}