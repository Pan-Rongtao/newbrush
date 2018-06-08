#include "FontPrivate.h"

using namespace nb::Media;

FontPrivate::FontPrivate(void)
{
}

FontPrivate::~FontPrivate(void)
{
}


FontPrivate::FontPrivate(const nb::gl::Gles::TTFConfig& config)
{
	m_ttfConfig =  config;
}

const nb::gl::Gles::TTFConfig * FontPrivate::GetConfig()
{
	return &m_ttfConfig;
}
