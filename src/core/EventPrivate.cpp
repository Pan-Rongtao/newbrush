#include "EventPrivate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

nbEventPrivate::nbEventPrivate(nbEventBase *owner)
	: m_isDispatching(false)
	, m_bNeedDelete(false)
	, m_pFirstItem(NULL)
	, m_plstItems(NULL)
	, m_owner(owner)
{
}

nbEventPrivate::~nbEventPrivate(void)
{
	if(m_pFirstItem != NULL)
	{
		m_pFirstItem->m_pAccepter->EventRefRelease(m_owner);
		delete m_pFirstItem;
	}

	if(m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end(); itor++)
		{
			ItemInfo *pItem = *itor;

			pItem->m_pAccepter->EventRefRelease(m_owner);
			delete pItem;
		}

		delete m_plstItems;
	}
}

void nbEventPrivate::Add(nbObject *pAccepter, nbEventBase::funAccepterBase pfun)
{
//	if(pAccepter == NULL || pfun == NULL) return;
	if(pAccepter == NULL) NB_THROW_EXCEPTION("事件接收对象不能为空。");
	if(pfun == NULL) NB_THROW_EXCEPTION("事件接收函数不能为空。");
	if(IsExist(pAccepter, pfun)) NB_THROW_EXCEPTION("事件响应函数已存在。");

	pAccepter->EventRefAdd(m_owner);

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

void nbEventPrivate::Sub(nbObject *pAccepter, nbEventBase::funAccepterBase pfun)
{
	if(m_pFirstItem != NULL)
	{
		if(m_pFirstItem->m_pAccepter == pAccepter && m_pFirstItem->m_pfun == pfun)
		{
			delete m_pFirstItem;

			if(m_plstItems != NULL && !m_plstItems->empty())
			{
				pAccepter->EventRefRelease(m_owner);
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
				pAccepter->EventRefRelease(m_owner);
				delete pItem;
				m_plstItems->erase(itor);

//暂时屏蔽				if(m_pCallBack) m_pCallBack->On_EventHandleBase_Subed(this);
				break;
			}
		}
	}
}

void nbEventPrivate::Sub(nbObject *pAccepter)
{
	if(m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end();)
		{
			ItemInfo *pItem = *itor;
			if(pItem->m_pAccepter == pAccepter)
			{
				pAccepter->EventRefRelease(m_owner);

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
			pAccepter->EventRefRelease(m_owner);

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


bool nbEventPrivate::IsExist(nbObject *pAccepter, nbEventBase::funAccepterBase pfun) const
{
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

void nbEventPrivate::Dispatch(nbEventParam &param)
{
	m_isDispatching = true;

	if(m_pFirstItem != NULL)
	{
//		(m_pFirstItem->m_pAccepter->*(m_pFirstItem->m_pfun))(pSender, param);

	//	nbObject::ptr x = m_pFirstItem->m_pAccepter; // 增加计数，防止消息处理中被释放掉
		m_owner->DispatchTrigger(m_pFirstItem->m_pAccepter, m_pFirstItem->m_pfun, param);

		if(m_bNeedDelete)
		{
			delete this;
			return;
		}
	}

	if(!param.m_bHandled &&  m_plstItems != NULL)
	{
		NB_LINUX_STD std::list<ItemInfo *>::const_iterator itor = m_plstItems->begin();
		for(; itor != m_plstItems->end(); itor++)
		{
			ItemInfo *pInfo = *itor;
	//		(pInfo->m_pAccepter->*(pInfo->m_pfun))(pSender, param);

		//	nbObject::ptr x = m_pFirstItem->m_pAccepter; // 增加计数，防止消息处理中被释放掉
			m_owner->DispatchTrigger(pInfo->m_pAccepter, pInfo->m_pfun, param);

			if(m_bNeedDelete)
			{
				delete this;
				return;
			}

			if(param.m_bHandled) break;
		}
	}

	m_isDispatching = false;
}

bool nbEventPrivate::HasAccepter() const
{
	return m_pFirstItem != NULL;
}
