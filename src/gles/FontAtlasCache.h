#pragma once
#include "core/Object.h"
#include "FontAtlas.h"

namespace nb{ namespace gl{ namespace Gles{

struct TTFConfig;
class FontAtlasCache : public nbObject
{
public:
	FontAtlasCache(void);

	~FontAtlasCache(void);

	FontAtlasPtr GetFontAtlasTTF(const TTFConfig* config);

private:
	std::string GenerateFontName(const std::string & fontName,float fontSize);

	std::map<std::string, Core::RefObjectWeatPtrT<FontAtlas> > m_atlasMap;
};

}}}
