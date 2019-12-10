#pragma once
#include "../media/GlyphMetrics.h"
#include "glm/glm.hpp"

namespace nb{

struct Glyph
{
	int			texureId;	//字形所在纹理
	glm::vec2	uv[4];		//纹理坐标
	GlyphInfo	info;		//字形信息
};

class NB_API GlyphFactory
{
public:
	static std::shared_ptr<Glyph> getGlyph(std::shared_ptr<Font> font, wchar_t ch);

};

}