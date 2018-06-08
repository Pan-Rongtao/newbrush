#include "core/PropertyValueToucher.h"
#include "core/Type.h"
#include "core/Exception.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

bool PropertyValueToucherBase::IsRefTypeOfProperty() const
{
	return m_pProperty->GetElementType()->IsRefType();
}


void PropertyValueToucherBase::ThrowException(const char *pMessage) const
{
	throw ExceptionPtr::GetPtrInstance(pMessage);
}

void PropertyValueToucherBase::SetRefValue(DependencyProperty *pProp, RefObject *pv)
{
	m_pObject->SetRefValue(pProp, pv);
}

void PropertyValueToucherBase::SetValueValue(DependencyProperty *pProp, const ValueObject &v)
{
	m_pObject->SetValueValue(pProp, v);
}

void PropertyValueToucherBase::SetEnumValue(DependencyProperty *pProp, int v)
{
	m_pObject->SetEnumValue(pProp, v);
}

RefObject * PropertyValueToucherBase::GetRefValue(DependencyProperty *pProp) const
{
	return m_pObject->GetRefValue(pProp);
}

const ValueObject &PropertyValueToucherBase::GetValueValue(DependencyProperty *pProp) const
{
	return m_pObject->GetValueValue(pProp);
}

int PropertyValueToucherBase::GetEnumValue(DependencyProperty *pProp) const
{
	return m_pObject->GetEnumValue(pProp);
}

bool PropertyValueToucherBase::IsNull() const
{
	return !m_pObject->IsSavedPropertyValue(m_pProperty);
}

PropertyLock * PropertyValueToucherBase::Lock()
{
	return m_pObject->LockPropertyValue(m_pProperty);
}
