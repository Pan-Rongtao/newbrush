#include "gui/TextBlock.h"
#include <codecvt>
#include "media/Font.h"
#include "gles/Quadrangle.h"
#include "gles/GlyphFactory.h"
#include "gles/Context.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Texture2D.h"

using namespace nb::core;
using namespace nb::media;
using namespace nb::gl;
using namespace nb::gui;

TextBlock::TextBlock()
	: TextBlock("")
{
}

TextBlock::TextBlock(const std::string & content)
	: m_x(0.0)
	, m_y(0.0)
{
	auto onTextChanged = [&](const std::string &_old, const std::string &_new)
	{
		m_charRenderers.clear();
		std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
		std::wstring unicodeStr = cvt.from_bytes(_new);
		for (auto const &ch : unicodeStr)
		{
			auto quad = std::make_shared<Quadrangle>();
			auto renderObj = std::make_shared<RenderObject>(quad, std::make_shared<Material>(Programs::glpy()));
			m_charRenderers.push_back(std::make_pair(renderObj, GlyphFactory::getGlyph(ch)));
		}
	};

	Text.notify(onTextChanged);
}

nb::core::Size TextBlock::measureOverride(const nb::core::Size & availableSize)
{
	return Size(availableSize.width() - Padding().left() - Padding().right(), availableSize.height() - Padding().top() - Padding().bottom());
}

nb::core::Size TextBlock::arrangeOverride(const nb::core::Size & finalSize)
{
	switch (TextWrapping)
	{
	case nb::gui::NoWrap:	return finalSize;
	case nb::gui::Wrap:
		break;
	case nb::gui::WrapWithOverflow:
		break;
	default:
		break;
	}
}

void TextBlock::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	m_x = Padding().left();
	m_y = Padding().top();
	for (auto const &one : m_charRenderers)
	{
		auto renderObject = one.first;
		auto glyph = one.second;
		float lineHeigt = 24;
		int offset = (lineHeigt - glyph->info.top);
		float y = m_y + offset;
		Rect rc(m_x, y, glyph->info.bm_width, glyph->info.bm_height);
		renderObject->model()->meshes()[0].vertexs()[0].position = { rc.left(), rc.bottom(), 0.0f };
		renderObject->model()->meshes()[0].vertexs()[1].position = { rc.right(), rc.bottom(), 0.0f };
		renderObject->model()->meshes()[0].vertexs()[2].position = { rc.right(), rc.top(), 0.0f };
		renderObject->model()->meshes()[0].vertexs()[3].position = { rc.left(), rc.top(), 0.0f };
		renderObject->model()->meshes()[0].vertexs()[0].texCoord = glyph->uv[0];
		renderObject->model()->meshes()[0].vertexs()[1].texCoord = glyph->uv[1];
		renderObject->model()->meshes()[0].vertexs()[2].texCoord = glyph->uv[2];
		renderObject->model()->meshes()[0].vertexs()[3].texCoord = glyph->uv[3];
		renderObject->material()->textures().push_back(std::make_shared<Texture2D>(glyph->texureId));
		drawContext->queue(renderObject);
		m_x += glyph->info.bm_width;
	//	m_y += glyph->info.bm_height;
	}
}
