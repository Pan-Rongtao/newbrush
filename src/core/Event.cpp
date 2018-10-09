#include "core/Event.h"
#include "core/Exception.h"
#include "EventPrivate.h"

using namespace nb::core;

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
}

void nbEventBase::Add(nbObject *pAccepter, funAccepterBase pfun)
{
	GetPrivate()->Add(pAccepter, pfun);
}

void nbEventBase::Sub(nbObject *pAccepter, funAccepterBase pfun)
{
	GetPrivate()->Sub(pAccepter, pfun);
}

void nbEventBase::Sub(nbObject *pAccepter)
{
	GetPrivate()->Sub(pAccepter);
}


bool nbEventBase::IsExist(nbObject *pAccepter, funAccepterBase pfun) const
{
	return GetPrivate()->IsExist(pAccepter, pfun);
}

void nbEventBase::Dispatch(nbEventParam &param)
{
	GetPrivate()->Dispatch(param);
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
