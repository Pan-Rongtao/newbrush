#include "core/DependencyProperty.h"
#include "InternalCore.h"
#include "PropertyInternal.h"

using namespace nb::core;

NB_OBJECT_TYPE_IMPLEMENT(DependencyProperty, RefObject, NULL, NULL);

DependencyProperty::DependencyProperty(void)
	: m_pType(NULL)
	, m_pElementType(NULL)
	, m_isImmobile(false)
	, m_funPropertyChanged_Old(NULL)
	, m_funPropertyValueChanged(NULL)
{
}

DependencyProperty::~DependencyProperty(void)
{
}

DependencyProperty * DependencyProperty::PrepareProperty(const std::string &key, const std::type_info &type, const std::type_info &propertyType, funPropertyValueChanged fun)
{
	DependencyProperty *p = nbInternalCore::GetDependencyPropertyInteranl()->PrepareProperty(key, type, propertyType, false, false);
	p->m_funPropertyValueChanged = fun;
	return p;
}

DependencyProperty * DependencyProperty::PrepareProperty(const char *pkey, const std::type_info &type, const std::type_info &propertyType, funPropertyValueChanged fun)
{
	DependencyProperty *p = nbInternalCore::GetDependencyPropertyInteranl()->PrepareProperty(pkey, type, propertyType, false, false);
	p->m_funPropertyValueChanged = fun;
	return p;
}

DependencyProperty * DependencyProperty::PrepareExternalProperty(const char *pkey, const std::type_info &type, const std::type_info &propertyType, funPropertyValueChanged fun)
{
	DependencyProperty *p = nbInternalCore::GetDependencyPropertyInteranl()->PrepareProperty(pkey, type, propertyType, true, false);
	p->m_funPropertyValueChanged = fun;
	return p;
}

Type * DependencyProperty::GetElementType() const
{
	return m_pElementType;
}

DependencyProperty * DependencyProperty::PrepareProperty(int offset, const char *pkey, const std::type_info &type, const std::type_info &propertyType, bool isImmobile, funPropertyValueChanged fun)
{
	DependencyProperty *p = nbInternalCore::GetDependencyPropertyInteranl()->PrepareProperty(offset, pkey, type, propertyType, false, isImmobile);
	p->m_funPropertyValueChanged = fun;
	return p;
}

size_t DependencyProperty::GetPreparePropertyCount(const std::string & typeName)
{
	return nbInternalCore::GetDependencyPropertyInteranl()->GetPreparePropertyCount(typeName);
}
