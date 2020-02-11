#pragma once
#include "newbrush/media/GlyphMetrics.h"
#include "glm/glm.hpp"

namespace nb{

struct Glyph
{
	int			texureId;	//������������
	glm::vec2	uv[4];		//��������
	GlyphInfo	info;		//������Ϣ
};

class NB_API GlyphFactory
{
public:
	static std::shared_ptr<Glyph> getGlyph(std::shared_ptr<Font> font, wchar_t ch);

};

}