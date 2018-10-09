#include "PropertyInternal.h"
#include "core/Exception.h"
#include "InternalCore.h"
#include "TypePrivate.h"

using namespace nb::core;

DependencyProperty * DependencyPropertyInternal::TypePropertys::NewProperty(int offset, const char *pkey, const std::type_info &type, bool isExternal, bool isImmobile)
{
	Info *pinfo = new Info();
	pinfo->m_key = pkey;
	pinfo->m_sElementType = type.name();
	pinfo->m_pProperty = new DependencyProperty();
	pinfo->m_isExternal = isExternal;
	pinfo->m_offset = offset;
	pinfo->m_pProperty->m_isImmobile = isImmobile;
	pinfo->m_pProperty->m_name = pkey;

	m_lst.push_back(pinfo);

	return pinfo->m_pProperty;
}

DependencyProperty * DependencyPropertyInternal::TypePropertys::NewProperty(int offset, const std::string &key, const std::type_info &type, bool isExternal, bool isImmobile)
{
	return NewProperty(offset, key.data(), type, isExternal, isImmobile);
}

DependencyPropertyInternal::TypePropertys::~TypePropertys()
{
	std::list<Info *>::iterator itor = m_lst.begin();
	for(; itor != m_lst.end(); itor++)
	{
		Info * pinfo = *itor;
		delete pinfo;
	}
}

DependencyPropertyInternal::DependencyPropertyInternal(void)
{
}

DependencyPropertyInternal::~DependencyPropertyInternal(void)
{
	//不做释放，AppPreparePropertys时已经全部释放了
}

DependencyProperty * DependencyPropertyInternal::PrepareProperty(const std::string &key, const std::type_info &type, const std::type_info &propertyType, bool isExternal, bool isImmobile)
{
	std::map<std::string, TypePropertys *>::iterator itor = m_mapPrepare.find(type.name());
	TypePropertys *pTypeProperty;
	if(itor == m_mapPrepare.end())
	{
		pTypeProperty = new TypePropertys;
		m_mapPrepare[type.name()] = pTypeProperty;
	}
	else
	{
		pTypeProperty = itor->second;
	}

	return pTypeProperty->NewProperty(0, key, propertyType, isExternal, isImmobile);
}

DependencyProperty * DependencyPropertyInternal::PrepareProperty(const char *pkey, const std::type_info &type, const std::type_info &propertyType, bool isExternal, bool isImmobile)
{
	std::map<std::string, TypePropertys *>::iterator itor = m_mapPrepare.find(type.name());
	TypePropertys *pTypeProperty;
	if(itor == m_mapPrepare.end())
	{
		pTypeProperty = new TypePropertys;
		m_mapPrepare[type.name()] = pTypeProperty;
	}
	else
	{
		pTypeProperty = itor->second;
	}

	return pTypeProperty->NewProperty(0, pkey, propertyType, isExternal, isImmobile);
}

DependencyProperty * DependencyPropertyInternal::PrepareProperty(int offset, const char *pkey, const std::type_info &type, const std::type_info &propertyType, bool isExternal, bool isImmobile)
{
	std::map<std::string, TypePropertys *>::iterator itor = m_mapPrepare.find(type.name());
	TypePropertys *pTypeProperty;
	if(itor == m_mapPrepare.end())
	{
		pTypeProperty = new TypePropertys;
		m_mapPrepare[type.name()] = pTypeProperty;
	}
	else
	{
		pTypeProperty = itor->second;
	}

	return pTypeProperty->NewProperty(offset, pkey, propertyType, isExternal, isImmobile);
}


void DependencyPropertyInternal::AppPreparePropertys()
{
	TypeInternal *pTypeInternal = nbInternalCore::GetTypeInternal();

	std::map<std::string, TypePropertys *>::iterator itor = m_mapPrepare.begin();
	for(; itor != m_mapPrepare.end(); itor++)
	{
		Type *pType = pTypeInternal->GetType(itor->first);

		if(pType == NULL)
		{
			char pc[1024] = { 0 };
			NB_SPRINTF(pc, sizeof(pc) - 1, "使用未注册的类型：%s", itor->first.data());
			NB_THROW_EXCEPTION(pc);
		}
		
		TypePropertys_ApplyPropertys(itor->second, pType);

		delete itor->second;
	}
	m_mapPrepare.clear();
}

void DependencyPropertyInternal::TypePropertys_ApplyPropertys(TypePropertys *pTP, Type *pType)
{
	TypeInternal *pTypeInternal = nbInternalCore::GetTypeInternal();

	std::list<TypePropertys::Info *>::iterator itor =pTP->m_lst.begin();
	for(; itor != pTP->m_lst.end(); itor++)
	{
		TypePropertys::Info * pinfo = *itor;
		Type *pElementType = pTypeInternal->GetType(pinfo->m_sElementType);

		if(pElementType == NULL)
		{
			char pc[1024] = { 0 };
			NB_SPRINTF(pc, sizeof(pc) - 1, "使用未注册的类型： %s", pinfo->m_sElementType.data());
			NB_THROW_EXCEPTION(pc);
		}

		pinfo->m_pProperty->m_pElementType = pElementType;
	//	DependencyPropertyInternal::SetPropertyElementType(pinfo->m_pProperty, pElementType);
	//	pinfo->m_pProperty->m_pType = pType;

		if(pinfo->m_isExternal)
		{
			pType->AttachExternalPropertyPrivate(pinfo->m_key, pinfo->m_pProperty);
		}
		else
		{
			pType->AttachPropertyPrivate(pinfo->m_key, pinfo->m_pProperty);
			pinfo->m_pProperty->m_offset = pinfo->m_offset;
		}

		delete pinfo;
	}
	pTP->m_lst.clear();
}

size_t DependencyPropertyInternal::GetPreparePropertyCount(const std::string & typeName) const
{
	std::map<std::string, TypePropertys *>::const_iterator itor = m_mapPrepare.find(typeName);
	if(itor == m_mapPrepare.end()) return 0;

	return itor->second->m_lst.size();
}
