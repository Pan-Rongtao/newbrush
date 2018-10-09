#include "core/Type.h"
#include "TypePrivate.h"
#include "InternalCore.h"
#include "core/DependencyProperty.h"
#include "core/Exception.h"

using namespace nb::core;

Type::Type(const std::type_info &type, Type *pParent, Assembly *pAssembly, IsEqualObjectFun funIsEqualObject, CopyObjectFun funCopy, int selfPropertyCount)
	: m_sTypeName(type.name())
	, m_pParent(pParent)
	, m_pProperties(NULL)
	, m_pExternalProperties(NULL)
	, m_pAssembly(pAssembly)
	, m_funIsEqualObject(funIsEqualObject)
	, m_funCopyObject(funCopy)
	, m_bIsRefType(type.name() == typeid(RefObject).name() ? true : (pParent == NULL ? false : pParent->IsRefType()))
	, m_nParentPropertyCount(pParent == NULL ? 0 : pParent->GetPropertyCount())
	, m_selfPropertyCount(selfPropertyCount)
{

}

Type::Type(const std::string &typeName, Type *pParent, Assembly *pAssembly, IsEqualObjectFun funIsEqualObject, CopyObjectFun funCopy, int selfPropertyCount)
	: m_sTypeName(typeName)
	, m_pParent(pParent)
	, m_pProperties(NULL)
	, m_pExternalProperties(NULL)
	, m_pAssembly(pAssembly)
	, m_funIsEqualObject(funIsEqualObject)
	, m_funCopyObject(funCopy)
	, m_bIsRefType(typeName == typeid(RefObject).name() ? true : (pParent == NULL ? false : pParent->IsRefType()))
	, m_nParentPropertyCount(pParent == NULL ? 0 : pParent->GetPropertyCount())
	, m_selfPropertyCount(selfPropertyCount)
{
}

Type::~Type(void)
{
	delete m_pProperties;
	delete m_pExternalProperties;
}

Type * Type::GetType(const std::type_info &type)
{
	return nbInternalCore::GetTypeInternal()->GetType(type);
}

Type * Type::GetParent() const
{
	return m_pParent;
}

Assembly * Type::GetAssembly() const
{
	return m_pAssembly;
}

Type::IsEqualObjectFun Type::GetIsEqualObjectFun() const
{
	return m_funIsEqualObject;
}

Type::CopyObjectFun Type::GetCopyObjectFun() const
{
	return m_funCopyObject;
}


void * Type::PrepargeType(const std::type_info &type, const std::type_info &parentType, Assembly *pAssembly, IsEqualObjectFun funIsEqual, CopyObjectFun funCopy)
{
	nbInternalCore::GetTypeInternal()->PrepargeType(type, parentType, pAssembly, funIsEqual, funCopy);
	return NULL;
}

void Type::AttachPropertyPrivate(const std::string &key, DependencyProperty *pProperty)
{
	if(m_pProperties == NULL)
	{
		m_pProperties = new ProperitesInfo();
	}

	if(m_pProperties->m_map.find(key) != m_pProperties->m_map.end())
	{
		char pc[1024] = { 0 };
		NB_SPRINTF(pc, sizeof(pc) - 1, "属性Key值 “%s” 已经被注册了。不能重复注册。", key.data());
		NB_THROW_EXCEPTION(pc);
	}

	pProperty->m_pType = this;
	pProperty->m_index = GetParentPropertyCount() + m_pProperties->m_map.size();
	m_pProperties->m_map[key] = pProperty;
	m_pProperties->m_vec.push_back(pProperty);
}

void Type::AttachExternalPropertyPrivate(const std::string &key, DependencyProperty *pProperty)
{
	if(m_pExternalProperties == NULL)
	{
		m_pExternalProperties = new ProperitesInfo();
	}

	if(m_pExternalProperties->m_map.find(key) != m_pExternalProperties->m_map.end())
	{
		char pc[1024] = { 0 };
		NB_SPRINTF(pc, sizeof(pc) -1, "属性Key值 “%s” 已经被注册了。不能重复注册。", key.data());
		NB_THROW_EXCEPTION(pc);
	}

	pProperty->m_pType = this;
	m_pExternalProperties->m_map[key] = pProperty;
	m_pExternalProperties->m_vec.push_back(pProperty);
}

bool Type::IsRefType() const
{
	return m_bIsRefType;
}

DependencyProperty * Type::GetExternalProperty(const char *pKey) const
{
	if(m_pExternalProperties == NULL) return NULL;
	std::map<std::string, DependencyPropertyPtr>::const_iterator itor = m_pExternalProperties->m_map.find(pKey);
	if(itor == m_pExternalProperties->m_map.end()) return NULL;
	return itor->second;
}

int Type::GetParentPropertyCount() const
{
	return m_nParentPropertyCount;
}

int Type::GetPropertyCount() const
{
	return GetParentPropertyCount() + m_selfPropertyCount;
}

bool Type::ContainProperty(DependencyProperty *prop) const
{
	if(prop->m_index < 0 || prop->m_index >= GetPropertyCount()) return false;
	
	return prop == GetPropertyAt(prop->m_index);
}

DependencyProperty * Type::GetPropertyAt(size_t index) const
{
	if(index < 0) NB_THROW_EXCEPTION("超出范围。");

	size_t parentCount = GetParentPropertyCount();

	if(index < parentCount)
	{
		return m_pParent->GetPropertyAt(index);
	}
	else
	{
		size_t x = index - parentCount;
		if(x >= m_pProperties->m_vec.size())
		{
			NB_THROW_EXCEPTION("超出范围。");
		}

		return m_pProperties->m_vec[x];
	}
}
