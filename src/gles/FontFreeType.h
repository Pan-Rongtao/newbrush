#pragma once
#include "core/Object.h"
#include <utility>
#include <ft2build.h>
#include FT_GLYPH_H
#include FT_TRUETYPE_TABLES_H
#include FT_BITMAP_H
#include FT_WINFONTS_H

namespace nb{ namespace gl{ namespace Gles{

class FontAtlas;
class FontFreeType;

typedef nbObjectPtrDerive<FontFreeType, nbObjectPtr> FontFreeTypePtr;
class FontFreeType: public nbObject
{
public:
	friend class FontAtlas;
	static FontFreeTypePtr Create(const std::string &fontName,float fontSize);

	void RenderCharAt();

	const FT_BitmapGlyph GetGlyphBimap(wchar_t theChar);

protected:
	FontFreeType();

	~FontFreeType(void);

private:
	struct Data
	{
		unsigned char * m_bytes;
		unsigned long   m_size;
		Data():m_bytes(NULL),m_size(0){}
		~Data()
		{
			if (m_bytes != NULL)
			{
				delete[] m_bytes;
				m_bytes = NULL;
				m_size = 0;
			}
		}
		bool IsNull()
		{
			if(m_bytes == NULL || m_size == 0)
			{
				return true;
			}
			return false;
		}
	};
	struct DataRef
	{
		Data m_data;
		unsigned int m_referenceCount;
	};

	bool CreateFontObject(const std::string &fontName, float fontSize);
	std::pair<unsigned char *,unsigned long> ReadFile(const std::string & fileName);
	bool InitFreeType();
	FT_Library GetFTLibrary();

	static std::map<std::string, DataRef> m_fontDataMap;
	std::string m_fontName;
	FT_Face m_fontFace;
	float m_fontsize;
	static FT_Library m_ftLibrary;
    static bool m_bftInitialized;
};


}}}
