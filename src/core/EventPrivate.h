#pragma once

#include "core/Event.h"

class nbEventPrivate
{
public:
//	typedef void (nbObject::* funAccepterBase)();

	nbEventPrivate(nbEventBase *owner);
	virtual ~nbEventPrivate(void);


	void Add(nbObject *pAccepter, nbEventBase::funAccepterBase pfun);
	void Sub(nbObject *pAccepter, nbEventBase::funAccepterBase pfun);
	void Sub(nbObject *pAccepter);
	bool IsExist(nbObject *pAccepter, nbEventBase::funAccepterBase pfun) const;
	void Dispatch(nbEventParam &param);

	bool HasAccepter() const;

	bool m_isDispatching;
	bool m_bNeedDelete;
protected:
//	virtual void DispatchTrigger(nbObject *pAccepter, funAccepterBase pfun, nbEventParam &param) const {}

private:

	struct ItemInfo
	{
		nbObject *m_pAccepter;
		nbEventBase::funAccepterBase m_pfun;
	};

	ItemInfo *m_pFirstItem;
	NB_LINUX_STD std::list<ItemInfo *> *m_plstItems;

	nbEventBase *m_owner;
};
