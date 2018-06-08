#include "core/Event.h"
#include "core/Exception.h"
#include "EventPrivate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

nbEventBase::nbEventBase(void)
	: m_pFirstItem(NULL)
	, m_plstItems(NULL)
	, m_private(NULL)
{
}

nbEventBase::~nbEventBase(void)
{
	if(m_private != NULL)
	{
		if(m_private->m_isDispatching)
		{
			m_private->m_bNeedDelete = true;
		}
		else
		{
			delete m_private;
		}
	}

/*	if(m_pFirstItem != NULL)
	{
		m_pFirstItem->m_pAccepter->EventRefRelease(this);
		delete m_pFirstItem;
	}

	if(m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end(); itor++)
		{
			ItemInfo *pItem = *itor;

			pItem->m_pAccepter->EventRefRelease(this);
			delete pItem;
		}

		delete m_plstItems;
	}*/
}

void nbEventBase::Add(nbObject *pAccepter, funAccepterBase pfun)
{
	GetPrivate()->Add(pAccepter, pfun);
	return;

//	if(pAccepter == NULL || pfun == NULL) return;
	if(pAccepter == NULL) NB_THROW_EXCEPTION("事件接收对象不能为空。");
	if(pfun == NULL) NB_THROW_EXCEPTION("事件接收函数不能为空。");
	if(IsExist(pAccepter, pfun)) NB_THROW_EXCEPTION("事件响应函数已存在。");

	pAccepter->EventRefAdd(this);

	if(m_pFirstItem == NULL)
	{
		m_pFirstItem = new ItemInfo;
		m_pFirstItem->m_pAccepter = pAccepter;
		m_pFirstItem->m_pfun = pfun;

//暂时屏蔽			if(m_pCallBack) m_pCallBack->On_EventHandleBase_Added(this);
		return;
	}

	if(m_plstItems == NULL) m_plstItems = new NB_LINUX_STD std::list<ItemInfo *>();

	ItemInfo *pItem = new ItemInfo();
	pItem->m_pAccepter = pAccepter;
	pItem->m_pfun = pfun;
	m_plstItems->push_back(pItem);

//暂时屏蔽		if(m_pCallBack) m_pCallBack->On_EventHandleBase_Added(this);
}

void nbEventBase::Sub(nbObject *pAccepter, funAccepterBase pfun)
{
	GetPrivate()->Sub(pAccepter, pfun);
	return;

	if(m_pFirstItem != NULL)
	{
		if(m_pFirstItem->m_pAccepter == pAccepter && m_pFirstItem->m_pfun == pfun)
		{
			delete m_pFirstItem;

			if(m_plstItems != NULL && !m_plstItems->empty())
			{
				pAccepter->EventRefRelease(this);
				m_pFirstItem = *m_plstItems->begin();
				m_plstItems->pop_front();
			}
			else
			{
				m_pFirstItem = NULL;
			}

//暂时屏蔽			if(m_pCallBack) m_pCallBack->On_EventHandleBase_Subed(this);
			return;
		}
	}

	if(m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end(); itor++)
		{
			ItemInfo *pItem = *itor;
			if(pItem->m_pAccepter == pAccepter && pItem->m_pfun == pfun)
			{
				pAccepter->EventRefRelease(this);
				delete pItem;
				m_plstItems->erase(itor);

//暂时屏蔽				if(m_pCallBack) m_pCallBack->On_EventHandleBase_Subed(this);
				break;
			}
		}
	}
}

void nbEventBase::Sub(nbObject *pAccepter)
{
	GetPrivate()->Sub(pAccepter);
	return;

	if(m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end();)
		{
			ItemInfo *pItem = *itor;
			if(pItem->m_pAccepter == pAccepter)
			{
				pAccepter->EventRefRelease(this);

				delete pItem;
				NB_LINUX_STD std::list<ItemInfo *>::iterator itorErase = itor;
				itor++;
				m_plstItems->erase(itorErase);

//暂时屏蔽				if(m_pCallBack) m_pCallBack->On_EventHandleBase_Subed(this);
			}
			else
			{
				 itor++;
			}
		}
	}

	if(m_pFirstItem != NULL)
	{
		if(m_pFirstItem->m_pAccepter == pAccepter)
		{
			pAccepter->EventRefRelease(this);

			delete m_pFirstItem;

			if(m_plstItems != NULL && !m_plstItems->empty())
			{
				m_pFirstItem = *m_plstItems->begin();
				m_plstItems->pop_front();
			}
			else
			{
				m_pFirstItem = NULL;
			}

//暂时屏蔽			if(m_pCallBack) m_pCallBack->On_EventHandleBase_Subed(this);
		}
	}
}


bool nbEventBase::IsExist(nbObject *pAccepter, funAccepterBase pfun) const
{
	return GetPrivate()->IsExist(pAccepter, pfun);

	if(m_pFirstItem != NULL)
	{
		if(m_pFirstItem->m_pAccepter == pAccepter && m_pFirstItem->m_pfun == pfun) return true;
	}

	if(m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::const_iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end(); itor++)
		{
			const ItemInfo *pItem = *itor;
			if(pItem->m_pAccepter == pAccepter && pItem->m_pfun == pfun) return true;
		}
	}

	return false;
}

void nbEventBase::Dispatch(nbEventParam &param)
{
	GetPrivate()->Dispatch(param);
	return;

	if(m_pFirstItem != NULL)
	{
//		(m_pFirstItem->m_pAccepter->*(m_pFirstItem->m_pfun))(pSender, param);

	//	nbObject::ptr x = m_pFirstItem->m_pAccepter; // 增加计数，防止消息处理中被释放掉
		DispatchTrigger(m_pFirstItem->m_pAccepter, m_pFirstItem->m_pfun, param);
	}

	if(!param.m_bHandled &&  m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::const_iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end(); itor++)
		{
			ItemInfo *pInfo = *itor;
	//		(pInfo->m_pAccepter->*(pInfo->m_pfun))(pSender, param);

		//	nbObject::ptr x = m_pFirstItem->m_pAccepter; // 增加计数，防止消息处理中被释放掉
			DispatchTrigger(pInfo->m_pAccepter, pInfo->m_pfun, param);
			if(param.m_bHandled) break;
		}
	}
}

bool nbEventBase::HasAccepter() const
{
	return GetPrivate()->HasAccepter();
}

nbEventPrivate * nbEventBase::GetPrivate() const
{
	if(m_private == NULL)
	{
		nbEventBase *pThis = const_cast<nbEventBase *>(this);
		pThis->m_private = new nbEventPrivate(pThis);
	}
	return m_private;
}

nbEventBaseTest::nbEventBaseTest()
{
}

nbEventBaseTest::~nbEventBaseTest()
{
}
