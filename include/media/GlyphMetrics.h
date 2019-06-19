#pragma once
#include "../core/Size.h"

namespace nb{ namespace media {

enum class TextWrapping
{
	NoWrap,	//²»»»ÐÐ
	Wrap,	//»»ÐÐ
};

class Font;
class NB_API GlyphMetrics
{
public:
	static core::Size measureGlyphAltas(std::shared_ptr<Font> font, const std::string &text, float charSpacing, float lineHeight, TextWrapping tw, float widthMax);

};

} }