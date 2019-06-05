#pragma once
#include "../core/Def.h"
#include <map>
#include <string>
#include "Texture2D.h"
#include "../media/FamilyTypeface.h"

namespace nb{ namespace gl{

struct Glyph
{
	int texId;	//字形所在纹理
	int left;	//
	int right;	//
	int top;
	int bottom;

};

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//构建一个字形图集纹理，宽高为width, height，字形的尺寸为glypSize
	TextureGlyphAtlas(uint32_t width, uint32_t height, uint32_t glypSize);

	//追加文本，返回实际追加的长度（超过的长度被忽略）
	uint32_t appendChar(wchar_t unicode);
	uint32_t appendText(const std::wstring &unicodeStr);

	//获取一个字符的信息
	
private:
	uint32_t					m_x;
	uint32_t					m_y;
	uint32_t					m_glypSize;
	std::map<wchar_t, Glyph>	m_glyphs;
	media::FamilyTypeface		m_face;
};

}}