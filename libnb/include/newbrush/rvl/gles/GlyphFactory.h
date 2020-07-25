#pragma once
#include "newbrush/core/media/GlyphMetrics.h"
#include "glm/glm.hpp"

namespace nb{

struct Glyph
{
	int			texureId;	//字形所在纹理
	glm::vec2	uv[4];		//纹理坐标
	GlyphInfo	info;		//字形信息
};

using GlyphPtr = std::shared_ptr<Glyph>;

class NB_API GlyphFactory
{
public:
	static GlyphPtr getGlyph(FontPtr font, wchar_t ch);

};

}