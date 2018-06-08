#pragma once

#include <map>
#include <list>
#include <typeinfo>
#include "core/Type.h"

class Assembly;

namespace nb { namespace Core {

class TypeInternal
{
public:
	TypeInternal(void);
	virtual ~TypeInternal(void);

	Type * RegisterType(const std::type_info &type, Type *pParentType, Assembly *pAssembly, Type::IsEqualObjectFun funIsEqual, Type::CopyObjectFun funCopy, int selfPropertyCount);
	Type * GetType(const std::type_info &type) const;
	Type * GetType(const char *psTypeName) const;
	Type * GetType(const std::string &sTypeName) const;

	void PrepargeType(const std::type_info &type, const std::type_info &parentType, Assembly *pAssembly, Type::IsEqualObjectFun funIsEqual, Type::CopyObjectFun funCopy);

	void AppPrepareTypes();
private:

	struct PrepareTypeInfo
	{
		Assembly * m_pAssembly;
		const std::type_info * m_pParent;
		Type::IsEqualObjectFun m_funIsEqual;
		Type::CopyObjectFun m_funCopy;
	};

private:
	Type * AppPrepareType(const std::map<const std::string, PrepareTypeInfo>::iterator &itor);
	Type * RegisterType(const std::string &typeName, Type *pParentType, Assembly *pAssembly, Type::IsEqualObjectFun funIsEqual, Type::CopyObjectFun funCopy, int selfPropertyCount);

private:
	std::map<const std::string, TypePtr> m_mapTypex;

	std::map<const std::string, PrepareTypeInfo> m_mapPrepareType;
	std::list<DependencyPropertyPtr> m_lstPrepareProperty;

};

}}
