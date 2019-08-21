#include "gles/GlyphBunch.h"
#include <codecvt>
#include "gles/GlyphFactory.h"

using namespace nb;
using namespace nb::gl;

GlyphBunch::GlyphBunch()
	: m_width(0.0f)
	, m_height(0.0f)
{
}

void GlyphBunch::arrage(std::shared_ptr<Font> font, float xStart, float yStart, const std::string & text, float charSpacing, float lineHeight, TextWrappingE tw, float widthMax)
{
	auto handleOne = [](std::vector<Vertex> &vertexs, std::vector<uint16_t> &indices, int i, float x, float yy, std::shared_ptr<Glyph> glyph)
	{
		vertexs[i * 4 + 0] = { glm::vec3(x, yy + glyph->info.bm_height, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(glyph->uv[0]) };
		vertexs[i * 4 + 1] = { glm::vec3(x + glyph->info.bm_width, yy + glyph->info.bm_height, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(glyph->uv[1]) };
		vertexs[i * 4 + 2] = { glm::vec3(x + glyph->info.bm_width, yy, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(glyph->uv[2]) };
		vertexs[i * 4 + 3] = { glm::vec3(x, yy, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(glyph->uv[3]) };
		indices[i * 6 + 0] = i * 4;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 3;
	};

	meshes().clear();
	float x = xStart;
	float y = yStart;
	m_width = 0.0f;
	m_height = 0.0f;
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	vertexs.resize(text.size() * 4);
	indices.resize(text.size() * 6);
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	std::wstring unicodeStr = cvt.from_bytes(text);
	switch (tw)
	{
	case TextWrappingE::NoWrap:
	{
		for (int i = 0; i != unicodeStr.size(); ++i)
		{
			auto glyph = GlyphFactory::getGlyph(font, unicodeStr[i]);
			float yy = y + lineHeight - glyph->info.top;
			handleOne(vertexs, indices, i, x, yy, glyph);
			x += glyph->info.bm_width + charSpacing;
		}
		m_width = text.empty() ? 0.0f : x - charSpacing;
		m_height = text.empty() ? 0.0f : lineHeight;
	}
	break;
	case TextWrappingE::Wrap:
	{
		for (int i = 0; i != unicodeStr.size(); ++i)
		{
			auto glyph = GlyphFactory::getGlyph(font, unicodeStr[i]);
			float yy = y + (lineHeight - glyph->info.top);
			if (x + glyph->info.bm_width + charSpacing <= xStart + widthMax)
			{
				handleOne(vertexs, indices, i, x, yy, glyph);
				x += glyph->info.bm_width + charSpacing;
			}
			else
			{
				x = xStart;
				y += lineHeight;
				float yy = y + (lineHeight - glyph->info.top);
				handleOne(vertexs, indices, i, x, yy, glyph);
				x += glyph->info.bm_width + charSpacing;
			}
		}
		m_width = text.empty() ? 0.0f : widthMax;
		m_height = text.empty() ? 0.0f : y + lineHeight;
	}
		break;
	default:
		break;
	}
	meshes().push_back(Mesh(vertexs, indices));
}

float GlyphBunch::getWidth() const
{
	return m_width;
}

float GlyphBunch::getHeight() const
{
	return m_height;
}
