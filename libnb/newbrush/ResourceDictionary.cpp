#include "newbrush/ResourceDictionary.h"

using namespace nb;

void ResourceDictionary::add(const std::string & key, const var & v)
{
	nbThrowExceptionIf(!m_resmap.insert({ key, v }).second, std::logic_error, "[%s] already exists.", key.data());
}

void ResourceDictionary::remove(const std::string & key)
{
	m_resmap.erase(key);
}

void ResourceDictionary::clear()
{
	m_resmap.clear();
}

var & ResourceDictionary::find(const std::string & key)
{
	static var s_a;
	auto iter = m_resmap.find(key);
	return iter == m_resmap.end() ? s_a : iter->second;
}

const var & ResourceDictionary::find(const std::string & key) const
{
	return const_cast<ResourceDictionary *>(this)->find(key);
}

int ResourceDictionary::count() const
{
	return m_resmap.size();
}

ref<ResourceDictionary> nb::globalResources()
{
	static auto g_res = createRef<ResourceDictionary>();
	return g_res;
}
