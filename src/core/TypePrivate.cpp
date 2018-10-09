#include "TypePrivate.h"
#include "core/Type.h"
#include "core/Exception.h"

using namespace nb::core;

TypeInternal::TypeInternal(void)
{
}

TypeInternal::~TypeInternal(void)
{
}

Type * TypeInternal::RegisterType(const std::type_info &type, Type *pParentType, Assembly *pAssembly, Type::IsEqualObjectFun funIsEqual, Type::CopyObjectFun funCopy, int propertyCount)
{
	return RegisterType(type.name(), pParentType, pAssembly, funIsEqual, funCopy, propertyCount);
}

Type * TypeInternal::RegisterType(const std::string &typeName, Type *pParentType, Assembly *pAssembly, Type::IsEqualObjectFun funIsEqual, Type::CopyObjectFun funCopy, int propertyCount)
{
	if(m_mapTypex.find(typeName) != m_mapTypex.end()) return NULL;

	Type *pType = new Type(typeName, pParentType, pAssembly, funIsEqual, funCopy, propertyCount);
	m_mapTypex[typeName] = pType;

	return pType;
}

Type * TypeInternal::GetType(const std::type_info &type) const
{
	std::map<const std::string, TypePtr>::const_iterator itor = m_mapTypex.find(type.name());
	if(itor == m_mapTypex.end()) return NULL;

	const TypePtr &t = static_cast<TypePtr>(itor->second);
	return t;
}

Type * TypeInternal::GetType(const char *psTypeName) const
{
	std::map<const std::string, TypePtr>::const_iterator itor = m_mapTypex.find(psTypeName);
	if(itor == m_mapTypex.end()) return NULL;

	const TypePtr &t = static_cast<TypePtr>(itor->second);
	return t;
}

Type * TypeInternal::GetType(const std::string &sTypeName) const
{
	std::map<const std::string, TypePtr>::const_iterator itor = m_mapTypex.find(sTypeName);
	if(itor == m_mapTypex.end()) return NULL;

	const TypePtr &t = static_cast<TypePtr>(itor->second);
	return t;
}

void TypeInternal::PrepargeType(const std::type_info &type, const std::type_info &parentType, Assembly *pAssembly, Type::IsEqualObjectFun funIsEqual, Type::CopyObjectFun funCopy)
{
	if(type == parentType)
	{
		if(type != typeid(OriginObject))
		{
			NB_THROW_EXCEPTION("派生类的Type不能与父类的Type相同。");
		}
	}

	PrepareTypeInfo x;
	x.m_pAssembly = pAssembly;
	x.m_pParent = (type == typeid(OriginObject) ? NULL : &parentType);
	x.m_funIsEqual = funIsEqual;
	x.m_funCopy = funCopy;
	m_mapPrepareType[type.name()] = x;
}

void TypeInternal::AppPrepareTypes()
{
	while(!m_mapPrepareType.empty())
	{
		AppPrepareType(m_mapPrepareType.begin());
	}
}

Type * TypeInternal::AppPrepareType(const std::map<const std::string, PrepareTypeInfo>::iterator &itor)
{
	const std::string &typeName = itor->first;
	PrepareTypeInfo &info = itor->second;

	if(info.m_pParent == NULL && typeName == typeid(OriginObject).name())
	{
		Type *pType = RegisterType(typeName, NULL, info.m_pAssembly, info.m_funIsEqual, info.m_funCopy, DependencyProperty::GetPreparePropertyCount(typeName));
		m_mapPrepareType.erase(itor);
		return pType;
	}

	// 获取父类型
	Type *pParent =  GetType(*info.m_pParent);
	if(pParent == NULL)
	{
		const std::type_info *xd = &typeid(OriginObject);
		const std::type_info *xd2 = &typeid(OriginObject);
		std::map<const std::string, PrepareTypeInfo>::iterator itorParent = m_mapPrepareType.find(info.m_pParent->name());
		if(itorParent == m_mapPrepareType.end()) NB_THROW_EXCEPTION("找不到对应的父类型。");
		pParent = AppPrepareType(itorParent);
	}

	// 注册类型
	Type *pType = RegisterType(typeName, pParent, info.m_pAssembly, info.m_funIsEqual, info.m_funCopy, DependencyProperty::GetPreparePropertyCount(typeName));
	m_mapPrepareType.erase(itor);
	return pType;
}
