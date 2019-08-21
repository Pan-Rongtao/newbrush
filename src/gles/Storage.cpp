#include "gles/Storage.h"

using namespace nb;
using namespace nb::gl;

const std::map<std::string, Any>& Storage::uniforms() const
{
	return m_uniforms;
}

void Storage::clear()
{
	m_uniforms.clear();
}
