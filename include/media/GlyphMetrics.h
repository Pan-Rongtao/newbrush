#pragma once
#include "../core/Size.h"

namespace nb{ namespace media {

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

enum class TextWrapping
{
	NoWrap,	//不换行
	Wrap,	//换行
};

class Font;
class NB_API GlyphMetrics
{
public:
	//测量一个unicode字符
	static GlyphInfo measureGlyp(std::shared_ptr<Font> font, wchar_t ch);

	//测量一个字符集，返回占用的像素尺寸
	static core::Size measureGlyphAltas(std::shared_ptr<Font> font, const std::string &text, float charSpacing, float lineHeight, TextWrapping tw, float widthMax);

};

} }