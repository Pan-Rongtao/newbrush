#pragma once
#include "../media/Font.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

struct Glyph
{
	int					texureId;	//字形所在纹理
	glm::vec2			uv[4];		//纹理坐标
	media::GlyphInfo	info;		//字形信息
};

class NB_API GlyphFactory
{
public:
	static std::shared_ptr<Glyph> getGlyph(std::shared_ptr<media::Font> font, wchar_t ch);

};

}}