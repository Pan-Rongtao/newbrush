#pragma once
#include "core/Object.h"
#include "gles/TTFConfig.h"

namespace nb{ namespace Media{

class FontPrivate : public Core::RefObject
{
public:
	FontPrivate(void);
	FontPrivate(const nb::gl::Gles::TTFConfig& config);
	~FontPrivate(void);
	const nb::gl::Gles::TTFConfig * GetConfig();

	inline void SetSize(float fontSize)
	{
		m_ttfConfig.m_fontSize = fontSize;
	}
	inline void SetFontName(std::string sFontName)
	{
		m_ttfConfig.m_fontFilePath = sFontName;
	}

private:
	nb::gl::Gles::TTFConfig m_ttfConfig;
};


}}
