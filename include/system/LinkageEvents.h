/**************************************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved
 
 * 技术中心 → ... → MF组 → UI Framework团队

 * 编 写 者: 何平

 * 编写日期: 2016-06

 * 简要描述: 消息联动类。

			消息联动类是用来联动触发消息的，没一个消息联动类对象都可以与其它的消息联动类对象连接起
			来，多个消息联动类对象可以组成一个联动网，当这个联动网中某一个消息联动对象调用Dispatch
			触发消息的时候，该联动网内的其它所有消息联动对象都将会触发相应的消息事件。

			一个消息联动类可以定义多个消息，使用上，通过派生本类来使用，在派生类上可以定义多个自定
			义的消息。在派生类上，使用宏L_EVENT来定义改派生类的消息。

			例如：

			class TestLinkageEvents : public LinkageEvents
			{
			public:
				class AbcEventParam : public nbEventParam { ... };
				L_EVENT(AbcEvent, AbcEventParam, LinkageEvents);

				class DDDEventParam : public nbEventParam { ... };
				L_EVENT(DDDEvent, DDDEventParam, LinkageEvents);
			};


 * 修改记录:

 **************************************************************************************************/

#pragma once

//链路事件集

#include "../core/Object.h"
#include "../core/Event.h"



namespace nb { namespace System {

#define L_EVENT(name, param, lesClass) \
class event__##name : public LEvent<param> \
{ \
	virtual LinkageEvents * GetLinkageEvents() const \
	{ \
		lesClass *x = NULL;\
		unsigned long offset = (unsigned long)&x->name;\
		LinkageEvents *pL = (lesClass *)(((unsigned long)this) - offset);\
		return pL; \
	} \
}name; \

class LinkageEventsInternal;
class NB_API LinkageEvents : public nbObject
{
public:

	///////////////////////////////////////////////////////////////////////////
	//链路事件集中的某一个事件
	//
	class NB_API LEventBase
	{
		friend class LinkageEventsInternal;
	public:

		// param 传递的事件参数
		// isOwnerRespond true 表明发送者本身也会响应消息；false 表明发送者本身不会响应消息
		void Dispatch(nbEventParam &param, bool isOwnerRespond);

	protected:
		virtual nbEventBase * GetTriggerEvent() = 0;
		virtual LinkageEvents * GetLinkageEvents() const = 0;
	};
	friend class LEventBase;

	///////////////////////////////////////////////////////////////////////////

	template<class ParamT>
	class LEvent : public LEventBase
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


	protected:
		virtual nbEventBase * GetTriggerEvent()
		{
			return &m_event;
		}

	private:
		nbEvent<ParamT> m_event;
	};

	class AbcEventParam : public nbEventParam
	{
	};
	L_EVENT(AbcEvent, AbcEventParam, LinkageEvents);

	class DddEventParam : public nbEventParam
	{
	};

public:
	LinkageEvents(void);
	virtual ~LinkageEvents(void);

	void ContentTo(LinkageEvents * le);

private:
	LinkageEventsInternal *m_internal;
};

typedef nbObjectPtrDerive<LinkageEvents, nbObjectPtr> LinkageEventsPtr;

}}

