#include <stdlib.h>
#include <map>
#include "core/Object.h"
#include "core/Type.h"
#include "core/Event.h"
#include "core/TypesPropertyValuesStore.h"
#include "core/ObjectAttachmentSymbol.h"
#include "InternalCore.h"
#include "PropertyValuesMgr.h"

using namespace nb::core;

void * nbObject::s_pMallocingObject = NULL;

namespace nb { namespace core { 
class ObjectAttachmentsMgr
{
public:
	std::map<ObjectAttachmentSymbolPtr, RefObjectWeatPtr> m_weakRefAttachments;
	std::map<ObjectAttachmentSymbolPtr, RefObjectPtr> m_strongRefAttachments;

	void RemoveWeakRefAttachment(ObjectAttachmentSymbol *symbol)
	{
		std::map<ObjectAttachmentSymbolPtr, RefObjectWeatPtr>::iterator itorWeak = m_weakRefAttachments.find(symbol);
		if(itorWeak != m_weakRefAttachments.end())
		{
			m_weakRefAttachments.erase(itorWeak);
		}
	}

	void RemoveStrongRefAttachment(ObjectAttachmentSymbol *symbol)
	{
		std::map<ObjectAttachmentSymbolPtr, RefObjectPtr>::iterator itorStrong = m_strongRefAttachments.find(symbol);
		if(itorStrong != m_strongRefAttachments.end())
		{
			m_strongRefAttachments.erase(itorStrong);
		}
	}

	void SetAttachment(ObjectAttachmentSymbol *symbol, RefObject *value, bool isWeakRef)
	{
		if(value == NULL)
		{
			RemoveWeakRefAttachment(symbol);
			RemoveStrongRefAttachment(symbol);
		}
		else
		{
			if(isWeakRef)
			{
				RemoveStrongRefAttachment(symbol);
				m_weakRefAttachments[symbol] = value;
			}
			else
			{
				RemoveWeakRefAttachment(symbol);
				m_strongRefAttachments[symbol] = value;
			}
		}
	}

	RefObject * GetAttachment(ObjectAttachmentSymbol *symbol) const
	{
		std::map<ObjectAttachmentSymbolPtr, RefObjectWeatPtr>::const_iterator itorWeak = m_weakRefAttachments.find(symbol);
		if(itorWeak != m_weakRefAttachments.end())
		{
			RefObject *v = itorWeak->second;

			if(v == NULL)
			{
				const_cast<ObjectAttachmentsMgr *>(this)->RemoveWeakRefAttachment(symbol);
			}

			return v;
		}

		std::map<ObjectAttachmentSymbolPtr, RefObjectPtr>::const_iterator itorStrong = m_strongRefAttachments.find(symbol);
		if(itorStrong != m_strongRefAttachments.end())
		{
			return itorStrong->second;
		}

		return NULL;
	}
};

class ObjectKeyTagsMgr
{
public:
	std::map<RefObjectPtr, RefObjectWeatPtr> m_tags;
};

class ObjectPVsMgr
{
public:
	ObjectPVsMgr(PVBaseBase *pv) : m_first(pv), m_pvs(NULL) {}

	// 不派生使用，不使用虚的析构函数
	~ObjectPVsMgr() {delete m_pvs;}

	void Add(PVBaseBase *pv)
	{
		if(m_first == NULL)
		{
			if(m_pvs == NULL)
			{
				m_first = pv;
				return;
			}
			else
			{
				m_first = *m_pvs->begin();
				m_pvs->erase(m_pvs->begin());
				m_pvs->push_back(pv);
			}
		}
		else
		{
			if(m_pvs == NULL) m_pvs = new std::vector<PVBaseBase *>();
			m_pvs->push_back(pv);
		}
	}

	void Sub(PVBaseBase *pv)
	{
		if(m_first == pv)
		{
			//这里仅仅只是将m_first置为空，不将m_pvs里面的内容拉过来，等下次添加的时候再拉过来
			m_first = NULL;
		}
		else
		{
			if(m_pvs != NULL)
			{
				std::vector<PVBaseBase *>::iterator itor = m_pvs->begin();
				for(; itor != m_pvs->end(); itor++)
				{
					if(*itor == pv)
					{
						m_pvs->erase(itor);
						break;
					}
				}
			}
		}
	}


	inline void Notify(nbObject *object)
	{
		if(m_first != NULL) NotifyPV(object, m_first);

		if(m_pvs != NULL)
		{
			std::vector<PVBaseBase *>::iterator itor = m_pvs->begin();
			for(; itor != m_pvs->end(); itor++)
			{
				NotifyPV(object, *itor);
			}
		}

	}

	inline void NotifyPV(nbObject *object, PVBaseBase *pv)
	{
		nbObject *belongToObject = pv->GetBelongToObject();
		if(belongToObject == NULL) return;

		DependencyProperty::funPropertyValueChanged fun = pv->GetProperty()->GetValueChangedFun();
		if(fun == NULL) return;

		PropertyValueChangedEventArgs args;
		args.m_property = pv->GetProperty();
		args.m_isContentChange = true;
		args.m_newObject = object;
		args.m_oldObject = object;
		(belongToObject->*(fun))(args);
	}

	PVBaseBase *m_first;
	std::vector<PVBaseBase *> * m_pvs;
};



void RefPVBase::AddToObject(RefObject *object)
{
	nbObject *o = dynamic_cast<nbObject *>(object);
	if(o != NULL) o->AddPV(this);
}

void RefPVBase::SubFromObject(RefObject *object)
{
	nbObject *o = dynamic_cast<nbObject *>(object);
	if(o != NULL) o->SubPV(this);
}

}}


//void *nbObject::s_pPrepareType = nbObject::PrepargeType<nbObject, nbObject>();
NB_OBJECT_TYPE_IMPLEMENT(nbObject, RefObject, NULL, NULL);


nbObject::nbObject(void)
	: m_psetEvent(NULL)
	, m_pPropertyValuesMgr(NULL)
	, m_pTypesPropertyValuesStore(NULL)
	, m_pObjectAttachmentsMgr(NULL)
	, m_pvs(NULL)
{
}

nbObject::~nbObject(void)
{
	if(m_psetEvent != NULL)
	{
		std::map<nbEventBase *, int> *pset = m_psetEvent;

		m_psetEvent = NULL;

		std::map<nbEventBase *, int>::iterator itor = pset->begin();
		for(; itor != pset->end(); itor++)
		{
			nbEventBase *pEvent = itor->first;
			pEvent->Sub(this);
		}

		delete pset;
	}

	delete m_pPropertyValuesMgr;
	delete m_pTypesPropertyValuesStore;

	delete m_pObjectAttachmentsMgr;
//待实现	delete m_pObjectKeyTags;

	delete m_pvs;
}

Type *nbObject::GetType(const std::type_info &info)
{
	return Type::GetType(info);
}

void nbObject::EventRefAdd(nbEventBase *pEvent)
{
	if(m_psetEvent == NULL)
	{
		m_psetEvent = new std::map<nbEventBase *, int>();
		(*m_psetEvent)[pEvent] = 1;
	}
	else
	{
		std::map<nbEventBase *, int>::iterator itor = m_psetEvent->find(pEvent);
		if(itor == m_psetEvent->end()) (*m_psetEvent)[pEvent] = 1;
		else itor->second++;
	}
}

void nbObject::EventRefRelease(nbEventBase *pEvent)
{
	if(m_psetEvent == NULL) return;
	
	std::map<nbEventBase *, int>::iterator itor = m_psetEvent->find(pEvent);
	if(itor != m_psetEvent->end())
	{
		itor->second--;
		if(itor->second <= 0) m_psetEvent->erase(itor);
	}
}

void nbObject::SetRefValue(DependencyProperty *pProp, RefObject *pv)
{
	if(pProp->m_offset > 0)
	{
		if(pProp->IsImmobile())
		{
			if(GetRefValue(pProp) != NULL)
			{
				char c[1024] = {0};
				sprintf(c, "属性 %s 具有Immobile标志，只能设置一次属性值。", pProp->GetName().data());
				NB_THROW_EXCEPTION(c);
			}
		}

		const std::type_info &type = typeid(*this);
		Type *pty = Type::GetType(type);
		if(pty && pty->ContainProperty(pProp))
		{
			RefPVBase *x = (RefPVBase *)(((long long)this) + pProp->m_offset);
			//(*x) = pv;
			x->Set(pv, pProp, this);
			return;
		}
	}

	PropertyValuesMgr *pMgr = TakePropertyValuesMgr();
	pMgr->SaveRefValue(pProp, pv, this);
}

RefObject * nbObject::GetRefValue(DependencyProperty *pProp) const
{
	if(pProp->m_offset > 0)
	{
		const std::type_info &type = typeid(*this);
		Type *pty = Type::GetType(type);
		if(pty && pty->ContainProperty(pProp))
		{
			RefPVBase *x = (RefPVBase *)(((long long)this) + pProp->m_offset);
			return x->Get();
		}
	}

	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr == NULL) return NULL;
	return pMgr->GetRefValue(pProp);
}

void nbObject::SetValueValue(DependencyProperty *pProp, const ValueObject &v, PropertyLock *lock)
{
	PropertyValuesMgr *pMgr = TakePropertyValuesMgr();
	pMgr->SaveValueValue(pProp, v, this, lock);
}

void nbObject::SetEnumValue(DependencyProperty *pProp, int v)
{
	PropertyValuesMgr *pMgr = TakePropertyValuesMgr();
	pMgr->SaveEnumValue(pProp, v);
}

const ValueObject &nbObject::GetValueValue(DependencyProperty *pProp) const
{
	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr == NULL)
	{
		ThrowException("指定的属性尚未存储有值对象。");
	}

	return pMgr->GetValueValue(pProp);
}

int nbObject::GetEnumValue(DependencyProperty *pProp) const
{
	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr == NULL)
	{
		ThrowException("指定的属性尚未存储枚举对象。");
	}

	return pMgr->GetEnumValue(pProp);
}

void nbObject::SetBaseValue(DependencyProperty *pProp, PropertyValueBase *pv)
{
	PropertyValuesMgr *pMgr = TakePropertyValuesMgr();
	pMgr->SaveValue(pProp, pv, this);
}

PropertyValueBase * nbObject::GetBaseValue(DependencyProperty *pProp) const
{
	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr == NULL) return NULL;
	return pMgr->GetValue(pProp);
}

PropertyValuesMgr *nbObject::TakePropertyValuesMgr()
{
	if(m_pPropertyValuesMgr == NULL)
	{
		m_pPropertyValuesMgr = new PropertyValuesMgr();
	}

	return m_pPropertyValuesMgr;
}

PropertyValuesMgr *nbObject::GetPropertyValuesMgr() const
{
	return m_pPropertyValuesMgr;
}

bool nbObject::IsSavedPropertyValue(DependencyProperty *pProp) const
{
	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr == NULL) return NULL;
	return pMgr->IsSavedPropertyValue(pProp);
}

nb::core::TypesPropertyValuesStore *nbObject::GetTypesPropertyValuesStore() const
{
	if(m_pTypesPropertyValuesStore == NULL)
	{
		nbObject *pThis = const_cast<nbObject *>(this);
		pThis->m_pTypesPropertyValuesStore = new nb::core::TypesPropertyValuesStore();
	}

	return m_pTypesPropertyValuesStore;
}

PropertyLock * nbObject::LockPropertyValue(DependencyProperty *pProp)
{
	PropertyValuesMgr *pMgr = TakePropertyValuesMgr();
	return pMgr->LockProperty(pProp);	
}

void nbObject::GetAllRefProperties(std::list<DependencyPropertyPtr> &lst) const
{
	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr != NULL) pMgr->GetAllRefProperties(lst);
}

void nbObject::GetAllValueProperties(std::list<DependencyPropertyPtr> &lst) const
{
	PropertyValuesMgr *pMgr = GetPropertyValuesMgr();
	if(pMgr != NULL) pMgr->GetAllValueProperties(lst);
}

void nbObject::SetAttachment(ObjectAttachmentSymbol *symbol, RefObject *value, bool isWeakRef)
{
	TakeObjectAttachmentsMgr()->SetAttachment(symbol, value, isWeakRef);
}

RefObject * nbObject::GetAttachment(ObjectAttachmentSymbol *symbol) const
{
	if(m_pObjectAttachmentsMgr == NULL) return NULL;
	return m_pObjectAttachmentsMgr->GetAttachment(symbol);
}

nb::core::ObjectAttachmentsMgr * nbObject::TakeObjectAttachmentsMgr()
{
	if(m_pObjectAttachmentsMgr == NULL)
		m_pObjectAttachmentsMgr = new nb::core::ObjectAttachmentsMgr;

	return m_pObjectAttachmentsMgr;
}

void nbObject::NotifyContentChanged()
{
	if(m_pvs != NULL) m_pvs->Notify(this);
}

void nbObject::AddPV(nb::core::PVBaseBase *pv)
{
	if(m_pvs == NULL)
	{
		m_pvs = new nb::core::ObjectPVsMgr(pv);
	}
	else
	{
		m_pvs->Add(pv);
	}
}

void nbObject::SubPV(nb::core::PVBaseBase *pv)
{
	//调用端保证已经有了m_pvs，这样就不用判断是否为空了
	m_pvs->Sub(pv);
}
