#include "gui/ResourceDictionary.h"

using namespace nb;
using namespace nb::gui;

void ResourceDictionary::remove(const std::string & key)
{
	m_resmap.erase(key);
}

void ResourceDictionary::clear()
{
	m_resmap.clear();
}

Any & ResourceDictionary::find(const std::string & key)
{
	static Any s_a;
	auto iter = m_resmap.find(key);
	return iter == m_resmap.end() ? s_a : iter->second;
}

const Any & ResourceDictionary::find(const std::string & key) const
{
	return const_cast<ResourceDictionary *>(this)->find(key);
}
