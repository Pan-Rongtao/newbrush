#include "Renderer2D.h"
#include <array>
#include "newbrush/Helper.h"
#include "clipper/clipper.hpp"
#include "mapbox/earcut.hpp"

using namespace nb;
using namespace ClipperLib;

static const unsigned MaxQuadCount = 2000;
static const unsigned MaxVertexCount = MaxQuadCount * 4;
static const unsigned MaxIndexCount = MaxQuadCount * 6;
static const unsigned MaxTextureCount = 16;	//必须跟2d.fs的纹理个数对应上

struct VertexData
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float texIndex;
	float opacity;
};

struct RendererData
{
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	GLuint whiteTexture = 0;
	unsigned whiteTextureSlot = 0;
	unsigned usedIndexCount = 0;
	unsigned usedTextureCount = 1;
	std::array<unsigned, MaxTextureCount> textureIDs{{ 0 }};
	VertexData *quadBuffer = nullptr;
	VertexData *quadBufferPtr = nullptr;
	Renderer2D::Stats RenderStats;
};
static RendererData g_data;
static ref<Shader> g_renderer2dShader;

void Renderer2D::init()
{
	//如果已经初始化过，则跳出
	if (g_data.quadBuffer)
		return;

	g_data.quadBuffer = new VertexData[MaxVertexCount];

	//初始化vao, vbo, ebo
	glGenVertexArrays(1, &g_data.vao);
	glBindVertexArray(g_data.vao);

	glGenBuffers(1, &g_data.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_data.vbo);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, uv));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, texIndex));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(9, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, opacity));

	unsigned indices[MaxIndexCount];
	unsigned offset = 0;
	for (int i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 0 + offset;
		indices[i + 4] = 2 + offset;
		indices[i + 5] = 3 + offset;
		offset += 4;
	}

	glGenBuffers(1, &g_data.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_data.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 1x1白色纹理
	glGenTextures(1, &g_data.whiteTexture);
	glBindTexture(GL_TEXTURE_2D, g_data.whiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	unsigned color = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

	g_data.textureIDs[0] = g_data.whiteTexture;

	//初始化采样器数组uniform
	g_renderer2dShader = ShaderLibrary::get("shader_2d");
	g_renderer2dShader->use();

	int samplers[MaxTextureCount];
	for (int i = 0; i < MaxTextureCount; ++i) samplers[i] = i;
	g_renderer2dShader->setIntArray("u_samplers", samplers, MaxTextureCount);

	g_renderer2dShader->disuse();
}

void Renderer2D::_beginBatch(bool resetStats)
{
	if (resetStats)
		memset(&g_data.RenderStats, 0, sizeof(Stats));
	g_data.quadBufferPtr = g_data.quadBuffer;
	g_data.usedIndexCount = 0;
	g_data.usedTextureCount = 1;
}

void Renderer2D::shutdown()
{
	glDeleteVertexArrays(1, &g_data.vao);
	glDeleteBuffers(1, &g_data.vbo);
	glDeleteBuffers(1, &g_data.ebo);
	glDeleteTextures(1, &g_data.whiteTexture);

	delete[] g_data.quadBuffer;
	g_data.quadBuffer = nullptr;
}

void Renderer2D::beginBatch()
{
	init();
	_beginBatch(true);
}

void Renderer2D::endBatch()
{
	GLsizeiptr size = (uint8_t *)g_data.quadBufferPtr - (uint8_t *)g_data.quadBuffer;
	glBindBuffer(GL_ARRAY_BUFFER, g_data.vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, g_data.quadBuffer);

	//激活使用的所有采样单元
	for (auto i = 0u; i < g_data.usedTextureCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, g_data.textureIDs[i]);
	}
	
	g_renderer2dShader->use();

	auto const &matVP = nb::sharedCamera2D()->getViewProjectionMatrix();
	g_renderer2dShader->setMat4("u_viewProjectionMatrix", matVP);

	glBindVertexArray(g_data.vao);
	glDrawElements(GL_TRIANGLES, g_data.usedIndexCount, GL_UNSIGNED_INT, nullptr);
	
	g_renderer2dShader->disuse();

	g_data.RenderStats.drawCount++;
}

void Renderer2D::drawRect(const Rect &rc, const glm::mat4 &transform, const glm::vec4 & color, float opacity, const Rect & rcClip)
{
	if (rcClip.width() > 0 && rcClip.height() > 0)
	{
		auto material = createRef<FlatMaterial>(Color::fromRgbaF(color.x, color.y, color.z, color.w));
		drawEffect(rc, transform, material, {}, rcClip);
	}
	else
	{
		if (g_data.usedIndexCount >= MaxIndexCount)
		{
			endBatch();
			_beginBatch(false);
		}

		const glm::vec4 &_color = color;
		const float &_textureIndex = 0.0f;
		static const TextureFrame texFrame;
		_drawQuad(rc, transform, _color, _textureIndex, texFrame, opacity);
	}
}

void Renderer2D::drawImage(const Rect &rc, const glm::mat4 &transform, const TextureFrame &texFrame, float opacity, const Rect &rcClip)
{
	if (rcClip.width() > 0 && rcClip.height() > 0)
	{
		auto material = createRef<TextureMaterial>(texFrame);
		drawEffect(rc, transform, material, {}, rcClip);
	}
	else
	{
		static const glm::vec4 &color = { 1.0f, 1.0f, 1.0f, 1.0f };
		_drawImage(rc, transform, texFrame, opacity, color);
	}
}

const Renderer2D::Stats & Renderer2D::getStats()
{
	return g_data.RenderStats;
}

/**************************************
*	rc是需要整个矩形的区域
*	而p0,p1,p2,p3是实际渲染区域，
*	如果渲染的纹理四周为空，则p0,p1,p2,p3的区域小于rc
***************************************/
void Renderer2D::_drawQuad(const Rect &rc, const glm::mat4 &transform, const glm::vec4 & color, float textureIndex, const TextureFrame &texFrame, float opacity)
{
	auto const &tex = texFrame.texture;
	auto rotated = texFrame.rotated;
	glm::vec4 position = { (int)rc.x(), (int)rc.y(), 0.0f, 1.0f };		//一定要取整，否则两个紧挨的节点会出现缝隙，暂未找到原因
	glm::vec4 p0 = { texFrame.pinch.x, texFrame.pinch.y, 0.0f, 1.0f };
	glm::vec4 p1 = { rc.width() - (texFrame.sourceSize.x - texFrame.frame.z - texFrame.pinch.x), texFrame.pinch.y, 0.0f, 1.0f };
	glm::vec4 p2 = { rc.width() - (texFrame.sourceSize.x - texFrame.frame.z - texFrame.pinch.x), rc.height() - (texFrame.sourceSize.y - texFrame.frame.w - texFrame.pinch.y), 0.0f, 1.0f };
	glm::vec4 p3 = { texFrame.pinch.x, rc.height() - (texFrame.sourceSize.y - texFrame.frame.w - texFrame.pinch.y), 0.0f, 1.0f };
	glm::vec2 texSourceSize = tex ? glm::vec2(tex->width(), tex->height()) : glm::vec2(0.0f);
	glm::vec2 texTargetOffset = { texFrame.frame.x, texFrame.frame.y };
	glm::vec2 texTargetSize = rotated ? glm::vec2(texFrame.frame.w, texFrame.frame.z) : glm::vec2(texFrame.frame.z, texFrame.frame.w);
	glm::vec2 uv0 = { texTargetOffset / texSourceSize };
	glm::vec2 uv1 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, texTargetOffset.y / texSourceSize.y };
	glm::vec2 uv2 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };
	glm::vec2 uv3 = { texTargetOffset.x / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };

	g_data.quadBufferPtr->position = transform * p0 + position;
	g_data.quadBufferPtr->color = color;
	g_data.quadBufferPtr->uv = rotated ? uv1 : uv0;// { 0.0f, 0.0f };
	g_data.quadBufferPtr->texIndex = textureIndex;
	g_data.quadBufferPtr->opacity = opacity;
	g_data.quadBufferPtr++;

	g_data.quadBufferPtr->position = transform * p1 + position;
	g_data.quadBufferPtr->color = color;
	g_data.quadBufferPtr->uv = rotated ? uv2 : uv1;// { 1.0f, 0.0f };
	g_data.quadBufferPtr->texIndex = textureIndex;
	g_data.quadBufferPtr->opacity = opacity;
	g_data.quadBufferPtr++;

	g_data.quadBufferPtr->position = transform * p2 + position;
	g_data.quadBufferPtr->color = color;
	g_data.quadBufferPtr->uv = rotated ? uv3 : uv2;// { 1.0f, 1.0f };
	g_data.quadBufferPtr->texIndex = textureIndex;
	g_data.quadBufferPtr->opacity = opacity;
	g_data.quadBufferPtr++;

	g_data.quadBufferPtr->position = transform * p3 + position;
	g_data.quadBufferPtr->color = color;
	g_data.quadBufferPtr->uv = rotated ? uv0 : uv3;// { 0.0f, 1.0f };
	g_data.quadBufferPtr->texIndex = textureIndex;
	g_data.quadBufferPtr->opacity = opacity;
	g_data.quadBufferPtr++;

	g_data.usedIndexCount += 6;
	g_data.RenderStats.quadCount++;
}

void Renderer2D::_drawImage(const Rect & rc, const glm::mat4 & transform, const TextureFrame & texFrame, float opacity, const glm::vec4& color)
{
	auto const &tex = texFrame.texture;
	if (!tex)
		return;

	if (g_data.usedIndexCount >= MaxIndexCount || g_data.usedTextureCount > MaxTextureCount - 1)
	{
		endBatch();
		_beginBatch(false);
	}

	float textureIndex = 0.0f;
	for (auto i = 1u; i < g_data.usedTextureCount; ++i)
	{
		if (g_data.textureIDs[i] == tex->id())
		{
			textureIndex = (float)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		textureIndex = (float)g_data.usedTextureCount;
		g_data.textureIDs[g_data.usedTextureCount] = tex->id();
		g_data.usedTextureCount++;
	}

	_drawQuad(rc, transform, color, textureIndex, texFrame, opacity);
}

void Renderer2D::drawEffect(const Rect& rc, const glm::mat4 & transform, ref<Material> material, const std::vector<ref<Light>> &lights, const Rect &rcClip)
{
	endBatch();

	if (rcClip.width() > 0 && rcClip.height() > 0)
	{
		float vpX, vpY, vpW, vpH;
		GLUtils::getViewport(vpX, vpY, vpW, vpH);
		glEnable(GL_SCISSOR_TEST);
		glScissor((int)rcClip.x(), (int)(vpH - rcClip.bottom()), (int)rcClip.width(), (int)rcClip.height());
	}

	std::vector<Vertex> vertexs(4);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };
	if (nb::is<TextureMaterial>(material))
	{
		auto texFrame = nb::as<TextureMaterial>(material)->texFrame;
		auto const &tex = texFrame.texture;
		auto rotated = texFrame.rotated;
		glm::vec4 position = { (int)rc.x(), (int)rc.y(), 0.0f, 1.0f };		//一定要取整，否则两个紧挨的节点会出现缝隙，暂未找到原因
		glm::vec4 p0 = { texFrame.pinch.x, texFrame.pinch.y, 0.0f, 1.0f };
		glm::vec4 p1 = { rc.width() - (texFrame.sourceSize.x - texFrame.frame.z - texFrame.pinch.x), texFrame.pinch.y, 0.0f, 1.0f };
		glm::vec4 p2 = { rc.width() - (texFrame.sourceSize.x - texFrame.frame.z - texFrame.pinch.x), rc.height() - (texFrame.sourceSize.y - texFrame.frame.w - texFrame.pinch.y), 0.0f, 1.0f };
		glm::vec4 p3 = { texFrame.pinch.x, rc.height() - (texFrame.sourceSize.y - texFrame.frame.w - texFrame.pinch.y), 0.0f, 1.0f };
		glm::vec2 texSourceSize = tex ? glm::vec2(tex->width(), tex->height()) : glm::vec2(0.0f);
		glm::vec2 texTargetOffset = { texFrame.frame.x, texFrame.frame.y };
		glm::vec2 texTargetSize = rotated ? glm::vec2(texFrame.frame.w, texFrame.frame.z) : glm::vec2(texFrame.frame.z, texFrame.frame.w);
		glm::vec2 uv0 = { texTargetOffset / texSourceSize };
		glm::vec2 uv1 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, texTargetOffset.y / texSourceSize.y };
		glm::vec2 uv2 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };
		glm::vec2 uv3 = { texTargetOffset.x / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };
	
		vertexs[0].position = transform * p0 + position;
		vertexs[1].position = transform * p1 + position;
		vertexs[2].position = transform * p2 + position;
		vertexs[3].position = transform * p3 + position;
		vertexs[0].uv = rotated ? uv1 : uv0;
		vertexs[1].uv = rotated ? uv2 : uv1;
		vertexs[2].uv = rotated ? uv3 : uv2;
		vertexs[3].uv = rotated ? uv0 : uv3;;
	}
	else
	{
		glm::vec4 position = { rc.x(), rc.y(), 0.0f, 1.0f };
		glm::vec4 p0 = { 0.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 p1 = { rc.width(), 0.0f, 0.0f, 1.0f };
		glm::vec4 p2 = { rc.width(), rc.height(), 0.0f, 1.0f };
		glm::vec4 p3 = { 0.0f, rc.height(), 0.0f, 1.0f };

		vertexs[0].position = transform * p0 + position;
		vertexs[1].position = transform * p1 + position;
		vertexs[2].position = transform * p2 + position;
		vertexs[3].position = transform * p3 + position;
		vertexs[0].uv = glm::vec2(0.0, 0.0);
		vertexs[1].uv = glm::vec2(1.0, 0.0);
		vertexs[2].uv = glm::vec2(1.0, 1.0);
		vertexs[3].uv = glm::vec2(0.0, 1.0);
	}

	auto mesh = createRef<Mesh>(vertexs, indices, material);
	mesh->draw(Transform::identityMatrix4(), sharedCamera2D(), lights);

	glDisable(GL_SCISSOR_TEST);
	_beginBatch(false);
}

#include <codecvt>
void Renderer2D::drawText(ref<Font> font, const Point & pt, const std::string & text, const glm::vec4 &color, float opacity)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	std::wstring unicodeStr = cvt.from_bytes(text);
	drawText(font, pt, unicodeStr, color, opacity);
}

void Renderer2D::drawText(ref<Font> font, const Point & pt, const std::wstring & unicodeStr, const glm::vec4 & color, float opacity)
{
	Point offset = pt;
	for (int i = 0; i != unicodeStr.size(); ++i)
	{
		auto glyph = nb::getGlyph(font, unicodeStr[i]);
		Rect drawRC(glyph->rc.x() + offset.x, glyph->rc.y() + offset.y, glyph->rc.size());
		offset += { glyph->advanceX, 0.0f };

		auto tex = glyph->texture;
		Rect texRect = Rect(glyph->uv[3].x * tex->width(), glyph->uv[3].y * tex->height(),
			(glyph->uv[2].x - glyph->uv[3].x) * tex->width(), (glyph->uv[0].y - glyph->uv[3].y) * tex->height());

		_drawImage(drawRC, Transform::identityMatrix4(), TextureFrame(tex, texRect), opacity, color);
	}
}

void Renderer2D::drawBorder(const Rect & rc, const glm::vec4 & color)
{
	endBatch();

	glm::vec4 position = { rc.x(), rc.y(), 0.0f, 1.0f };
	glm::vec4 p0 = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 p1 = { rc.width(), 0.0f, 0.0f, 1.0f };
	glm::vec4 p2 = { rc.width(), rc.height(), 0.0f, 1.0f };
	glm::vec4 p3 = { 0.0f, rc.height(), 0.0f, 1.0f };
	std::vector<Vertex> vertexs(4);
	vertexs[0].position = { rc.x(), rc.y(), 0.0f };
	vertexs[1].position = { rc.right(), rc.y(), 0.0f };
	vertexs[2].position = { rc.right(), rc.bottom(), 0.0f };
	vertexs[3].position = { rc.x(), rc.bottom(), 0.0f };
	std::vector<uint16_t> indices = { 0, 1, 2, 3 };
	auto material = createRef<FlatMaterial>(Color::fromRgbaF(color.x, color.y, color.z, color.w));
	auto mesh = createRef<Mesh>(vertexs, indices, material);
	mesh->draw(Transform::identityMatrix4(), sharedCamera2D(), {}, GL_LINE_LOOP);

	_beginBatch(false);
}
