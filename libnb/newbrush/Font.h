#pragma once
#include "newbrush/Components.h"

struct stbtt_fontinfo;
namespace nb
{
	
struct Glyph
{
	ref<Texture2D> texture;
	glm::vec2 uv[4];
	Rect rc;
	float advanceX;
};

struct FontBm
{
	Rect rc;		//x:左跨距（bearingX）, y:上跨距（bearingY）, width, height（字形宽高，位图宽高）
	float advanceX;	//字间距
	std::string bm;
};

class NB_API Font
{
public:
	Font(const std::string &path, uint32_t size);
	~Font();

	float getBaseline() const;
	float getLineHeight() const;

	FontBm getBitmap(wchar_t unicode) const;

	/***for test***/
	//path: d:/1.png
	void saveTextBitmap(const std::string &path, const std::string &text);

private:
	float m_size;
	float m_scale;
	int m_ascent;	//基线到顶部的高度
	int m_descent;	//基线到底部的高度，通常为负值
	int m_lineGap;	//字体从基线到顶部的高度
	stbtt_fontinfo *m_ttFontInfo;
};

class NB_API FontLibrary
{
public:
	static ref<Font> addFont(const std::string &path, uint32_t size);
	static ref<Font> getDefaultFont();

};

NB_API ref<Glyph> getGlyph(ref<Font> font, wchar_t unicode);

}