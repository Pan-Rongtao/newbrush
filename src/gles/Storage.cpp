#include "gles/Storage.h"

using namespace nb::core;
using namespace nb::gl;

Storage::Storage()
{
}

Storage::~Storage()
{
}

void Storage::insert(const std::string &name, const Any &v)
{
	m_uniforms.insert(std::make_pair(name, v));
}

std::map<const std::string, Any>::iterator nb::gl::Storage::beg()
{
	return m_uniforms.begin();
}

std::map<const std::string, Any>::iterator nb::gl::Storage::end()
{
	return m_uniforms.end();
}

Any Storage::find(const std::string &name)
{
	auto iter = m_uniforms.find(name);
	return iter == m_uniforms.end() ? Any() : &iter->second;
}

void Storage::clear()
{
	m_uniforms.clear();
}
