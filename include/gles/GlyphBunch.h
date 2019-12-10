#pragma once
#include "Model.h"
#include <string>
#include "media/GlyphMetrics.h"

namespace nb{

class NB_API GlyphBunch : public Model
{
public:
	GlyphBunch();

	void arrage(std::shared_ptr<Font> font, float xStart, float yStart, const std::string &text, float charSpacing, float lineHeight, TextWrappingE tw, float widthMax);

	float getWidth() const;
	float getHeight() const;

private:
	float			m_x;
	float			m_y;
	float			m_width;
	float			m_height;
};

}