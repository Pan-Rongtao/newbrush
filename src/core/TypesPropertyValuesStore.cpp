#include "core/TypesPropertyValuesStore.h"
#include "PropertyValuesMgr.h"
#include "TypesPropertyValuesStorePrivate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

TypesPropertyValuesStore::TypesPropertyValuesStore(void)
	: m_pPrivate(NULL)
{
	m_pPrivate = new TypesPropertyValuesStorePrivate();
}

TypesPropertyValuesStore::~TypesPropertyValuesStore(void)
{
	delete m_pPrivate;
}

void TypesPropertyValuesStore::SaveRefValue(const Type *type, DependencyProperty *prop, RefObject *pv)
{
	m_pPrivate->SaveRefValue(type, prop, pv);
}

void TypesPropertyValuesStore::SaveValueValue(const Type *type, DependencyProperty *prop, const ValueObject &v)
{
	m_pPrivate->SaveValueValue(type, prop, v);
}

RefObject * TypesPropertyValuesStore::GetRefValue(const Type *type, DependencyProperty *prop) const
{
	return m_pPrivate->GetRefValue(type, prop);
}

const ValueObject &TypesPropertyValuesStore::GetValueValue(const Type *type, DependencyProperty *prop) const
{
	return m_pPrivate->GetValueValue(type, prop);
}

bool TypesPropertyValuesStore::IsSavedValue(const Type *type, DependencyProperty *prop) const
{
	return m_pPrivate->IsSavedValue(type, prop);
}
