#include "FontAtlasCache.h"
#include "FontAtlas.h"
#include <sstream>
#include <iostream>

using namespace nb::gl::Gles;
using namespace nb::Core;

FontAtlasCache::FontAtlasCache(void)
{
}

FontAtlasCache::~FontAtlasCache(void)
{
}

FontAtlasPtr FontAtlasCache::GetFontAtlasTTF(const TTFConfig* config)
{
	std::string atlasName = GenerateFontName(config->m_fontFilePath,config->m_fontSize);
	std::map<std::string, RefObjectWeatPtrT<FontAtlas> >::iterator itor = m_atlasMap.find(atlasName);
	if(itor == m_atlasMap.end())
	{
		FontAtlas * fontatlas = new FontAtlas(config);
		m_atlasMap[atlasName] = fontatlas;
		return fontatlas;
	}
	else
	{
		RefObjectWeatPtrT<FontAtlas> weakFontAtlas = itor->second;
		if(weakFontAtlas.operator ->() == NULL)
		{
			FontAtlas *  fontatlas = new FontAtlas(config);
			m_atlasMap[atlasName] = fontatlas;
			return fontatlas;
		}
		return (FontAtlas*)(itor->second);
	}
	return NULL;
}

std::string FontAtlasCache::GenerateFontName(const std::string & fontName,float fontSize)
{
	std::string tmpName(fontName);
	std::stringstream ss;
    ss.precision(2);
    ss << std::fixed << fontSize;
	return tmpName.append(ss.str());
}
