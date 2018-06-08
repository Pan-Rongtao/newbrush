#include "TypesPropertyValuesStorePrivate.h"
#include "core/Exception.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

TypesPropertyValuesStorePrivate::TypesPropertyValuesStorePrivate(void)
{
}

TypesPropertyValuesStorePrivate::~TypesPropertyValuesStorePrivate(void)
{
	std::map<const Type *, PropertyValuesMgr *>::iterator itor = m_typesStore.begin();
	for(; itor != m_typesStore.end(); itor++)
	{
		PropertyValuesMgr *store = itor->second;
		delete store;
	}
}

PropertyValuesMgr * TypesPropertyValuesStorePrivate::GetStore(const Type *type) const
{
	std::map<const Type *, PropertyValuesMgr *>::const_iterator itor = m_typesStore.find(type);
	if(itor == m_typesStore.end())
	{
		return NULL;
	}
	else
	{
		return itor->second;
	}
}

PropertyValuesMgr * TypesPropertyValuesStorePrivate::TakeStore(const Type *type)
{
	std::map<const Type *, PropertyValuesMgr *>::iterator itor = m_typesStore.find(type);
	if(itor == m_typesStore.end())
	{
		PropertyValuesMgr *store = new PropertyValuesMgr();
		m_typesStore[type] = store;
		return store;
	}
	else
	{
		return itor->second;
	}
}

RefObject * TypesPropertyValuesStorePrivate::GetRefValue(const Type *type, DependencyProperty *prop) const
{
	PropertyValuesMgr *store = GetStore(type);
	if(store == NULL) return NULL;
	return store->GetRefValue(prop);
}

const ValueObject &TypesPropertyValuesStorePrivate::GetValueValue(const Type *type, DependencyProperty *prop) const
{
	PropertyValuesMgr *store = GetStore(type);
	if(store == NULL)
	{
		NB_THROW_EXCEPTION("指定的属性尚未存储有值对象。");
	}

	return store->GetValueValue(prop);
}

bool TypesPropertyValuesStorePrivate::IsSavedValue(const Type *type, DependencyProperty *prop) const
{
	PropertyValuesMgr *store = GetStore(type);
	if(store == NULL)
	{
		return false;
	}

	return store->IsSavedPropertyValue(prop);
}
