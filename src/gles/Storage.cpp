#include "gles/Storage.h"

using namespace nb::core;
using namespace nb::gl;

const std::map<std::string, nb::core::Any>& nb::gl::Storage::uniforms() const
{
	return m_uniforms;
}

void Storage::clear()
{
	m_uniforms.clear();
}
