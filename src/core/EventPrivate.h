#pragma once
#include "core/Event.h"

class nbEventPrivate
{
public:
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

private:

	struct ItemInfo
	{
		nbObject *m_pAccepter;
		nbEventBase::funAccepterBase m_pfun;
	};

	ItemInfo *m_pFirstItem;
	std::list<ItemInfo *> *m_plstItems;

	nbEventBase *m_owner;
};
