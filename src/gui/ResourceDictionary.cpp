#include "newbrush/gui/ResourceDictionary.h"

using namespace nb;
using namespace nb::gui;

void ResourceDictionary::add(const std::string & key, const Var & v)
{
	if (m_resmap.find(key) == m_resmap.end())
		nbThrowException(std::logic_error, "[%s] already exists.", key.data());
	else
		m_resmap[key] = v;
}

void ResourceDictionary::remove(const std::string & key)
{
	m_resmap.erase(key);
}

void ResourceDictionary::clear()
{
	m_resmap.clear();
}

Var & ResourceDictionary::find(const std::string & key)
{
	static Var s_a;
	auto iter = m_resmap.find(key);
	return iter == m_resmap.end() ? s_a : iter->second;
}

const Var & ResourceDictionary::find(const std::string & key) const
{
	return const_cast<ResourceDictionary *>(this)->find(key);
}

int ResourceDictionary::count() const
{
	return m_resmap.size();
}
