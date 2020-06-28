#pragma once
#include "newbrush/core/Size.h"

namespace nb{

enum class TextWrappingE
{
	NoWrap,				//不换行
	Wrap,				//换行
	WrapWithOverflow,
};

struct GlyphInfo
{
	int				left;
	int				top;
	int				advancex;
	int				advancey;
	unsigned int    bm_width;
	unsigned int    bm_height;
	int             bm_pitch;
	unsigned char*  bm_buffer;
};

class Font;
using FontPtr = std::shared_ptr<Font>;
class NB_API GlyphMetrics
{
public:
	//测量一个unicode字符
	static GlyphInfo measureGlyp(FontPtr font, wchar_t ch);

	//测量一个字符集，返回占用的像素尺寸
	static Size measureGlyphAltas(FontPtr font, const std::string &text, float charSpacing, float lineHeight, TextWrappingE tw, float widthMax);

};

}