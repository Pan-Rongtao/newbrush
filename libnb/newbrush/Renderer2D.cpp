#include "Renderer2D.h"
#include <array>
#include "newbrush/Mesh.h"
#include "clipper/clipper.hpp"
#include "mapbox/earcut.hpp"

using namespace nb;
using namespace ClipperLib;

static const unsigned MaxQuadCount = 2000;
static const unsigned MaxVertexCount = MaxQuadCount * 4;
static const unsigned MaxIndexCount = MaxQuadCount * 6;
static const unsigned MaxTextureCount = 32;

struct VertexData
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
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
	std::array<unsigned, MaxTextureCount> textureIDs = { 0 };
	VertexData *quadBuffer = nullptr;
	VertexData *quadBufferPtr = nullptr;
	Renderer2D::Stats RenderStats;
};
static RendererData s_Data;
static ref<Shader> s_renderer2dShader;

void Renderer2D::init()
{
	//如果已经初始化过，则跳出
	if (s_Data.quadBuffer)
		return;

	s_Data.quadBuffer = new VertexData[MaxVertexCount];

	//初始化vao, vbo, ebo
	glGenVertexArrays(1, &s_Data.vao);
	glBindVertexArray(s_Data.vao);

	glGenBuffers(1, &s_Data.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, texCoord));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, texIndex));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData, opacity));

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

	glGenBuffers(1, &s_Data.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 1x1白色纹理
	glGenTextures(1, &s_Data.whiteTexture);
	glBindTexture(GL_TEXTURE_2D, s_Data.whiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	unsigned color = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

	s_Data.textureIDs[0] = s_Data.whiteTexture;

	//初始化采样器数组uniform
	s_renderer2dShader = ShaderLibrary::get("system_2d");
	s_renderer2dShader->use();

	int samplers[MaxTextureCount];
	for (int i = 0; i < MaxTextureCount; ++i) samplers[i] = i;
	s_renderer2dShader->setIntArray("samplers", samplers, MaxTextureCount);

	s_renderer2dShader->disuse();
}

void Renderer2D::_beginBatch(bool resetStats)
{
	if (resetStats)
		memset(&s_Data.RenderStats, 0, sizeof(Stats));
	s_Data.quadBufferPtr = s_Data.quadBuffer;
	s_Data.usedIndexCount = 0;
	s_Data.usedTextureCount = 1;
}

void Renderer2D::shutdown()
{
	glDeleteVertexArrays(1, &s_Data.vao);
	glDeleteBuffers(1, &s_Data.vbo);
	glDeleteBuffers(1, &s_Data.ebo);
	glDeleteTextures(1, &s_Data.whiteTexture);

	delete[] s_Data.quadBuffer;
	s_Data.quadBuffer = nullptr;
}

void Renderer2D::beginBatch()
{
	init();
	_beginBatch(true);
}

void Renderer2D::drawPolyline(ref<Brush> brush, const std::vector<glm::vec2>& points, float size, const glm::vec2 &offset)
{
	Path path;
	for (auto const &p : points)
	{
		path.push_back(IntPoint((cInt)(p.x), (cInt)(p.y)));
	}
	ClipperOffset co;
	co.AddPath(path, jtRound, etOpenButt);
	Paths solution;
	co.Execute(solution, size / 2.0);

	std::vector<glm::vec2> pointsX(solution[0].size());
	for (auto i = 0u; i < pointsX.size(); ++i)
	{
		pointsX[i] = { solution[0][i].X, solution[0][i].Y };
	}

	drawPolygon(brush, pointsX, offset);
}

void Renderer2D::drawPolygon(ref<Brush> brush, const std::vector<glm::vec2> &points, const glm::vec2 & offset)
{
	std::vector<Vertex> vertexs(points.size());
	for (auto i = 0u; i < vertexs.size(); ++i)
	{
		auto p0 = points[i] + offset;
		vertexs[i].position = glm::vec3(p0, 0.0f);
	}

	using Point = std::array<float, 2>;
	std::vector<std::vector<Point>> polygon;
	std::vector<Point> pointsxx;
	for (auto i = 0u; i < vertexs.size(); ++i)
	{
		Point p = { vertexs[i].position.x, vertexs[i].position.y };
		pointsxx.push_back(p);
	}
	polygon.push_back(pointsxx);
	std::vector<uint16_t> indices = mapbox::earcut<uint16_t>(polygon);

	endBatch();

	ref<Material> material;
	if (is<SolidColorBrush>(brush))
	{
		auto _brush = as<SolidColorBrush>(brush);
		material = createRef<SolidColorMaterial>(_brush->color);
	}
	else if (is<LinearGradientBrush>(brush))
	{
		auto _brush = as<LinearGradientBrush>(brush);
		std::vector<GradientStop> stops;
		for (auto pair : _brush->stops)
		{
			stops.push_back({ pair.first, pair.second });
		}
		auto linearMaterial = createRef<LinearGrandientMaterial>(_brush->lenght, stops);
		linearMaterial->vertical = _brush->vertical;
		material = linearMaterial;
	}
	else if (is<ImageBrush>(brush))
	{
		auto _brush = as<ImageBrush>(brush);
	}
	else if (is<EffectBrush>(brush))
	{
		auto _brush = as<EffectBrush>(brush);
		material = _brush->material;
	}

	auto mesh = createRef<Mesh>(vertexs, indices, material);
	mesh->draw(glm::mat4(1.0), sharedCamera2D(), {});

	_beginBatch(false);
}

void Renderer2D::endBatch()
{
	GLsizeiptr size = (uint8_t *)s_Data.quadBufferPtr - (uint8_t *)s_Data.quadBuffer;
	glBindBuffer(GL_ARRAY_BUFFER, s_Data.vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.quadBuffer);

	//激活使用的所有采样单元
	for (auto i = 0u; i < s_Data.usedTextureCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, s_Data.textureIDs[i]);
	}
	
	s_renderer2dShader->use();

	auto const &matVP = nb::sharedCamera2D()->getViewProjectionMatrix();
	s_renderer2dShader->setMat4("nbVP", matVP);

	glBindVertexArray(s_Data.vao);
	glDrawElements(GL_TRIANGLES, s_Data.usedIndexCount, GL_UNSIGNED_INT, nullptr);
	
	s_renderer2dShader->disuse();

	s_Data.RenderStats.drawCount++;
}

void Renderer2D::drawRect(const Rect &rc, const glm::mat4 &transform, const glm::vec4 & color, float opacity)
{
	if (s_Data.usedIndexCount >= MaxIndexCount)
	{
		endBatch();
		_beginBatch(false);
	}
	 
	const glm::vec4 &_color = color;
	const float &_textureIndex = 0.0f;
	_drawQuad(rc, transform, _color, _textureIndex, nullptr, Rect(0.0f, 0.0f, 1.0f, 1.0f), false, opacity);
}

void Renderer2D::drawImage(const Rect &rc, const glm::mat4 &transform, ref<Texture2D> tex, const Rect &texRect, bool rotated, float opacity)
{
	if (!tex)
		return;

	if (s_Data.usedIndexCount >= MaxIndexCount || s_Data.usedTextureCount > 31)
	{
		endBatch();
		_beginBatch(false);
	}

	float textureIndex = 0.0f;
	for (auto i = 1u; i < s_Data.usedTextureCount; ++i)
	{
		if (s_Data.textureIDs[i] == tex->id())
		{
			textureIndex = (float)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		textureIndex = (float)s_Data.usedTextureCount;
		s_Data.textureIDs[s_Data.usedTextureCount] = tex->id();
		s_Data.usedTextureCount++;
	}

	static const glm::vec4 &color = { 1.0f, 1.0f, 1.0f, 1.0f };
	_drawQuad(rc,transform, color, textureIndex, tex, texRect, rotated, opacity);
}

const Renderer2D::Stats & Renderer2D::getStats()
{
	return s_Data.RenderStats;
}

void Renderer2D::_drawQuad(const Rect &rc, const glm::mat4 &transform,
	const glm::vec4 & color, float textureIndex, ref<Texture2D> tex, const Rect &texRect, bool rotated, float opacity)
{
	glm::vec4 position = { rc.x(), rc.y(), 0.0f, 1.0f };
	glm::vec4 p0 = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 p1 = { rc.width(), 0.0f, 0.0f, 1.0f };
	glm::vec4 p2 = { rc.width(), rc.height(), 0.0f, 1.0f };
	glm::vec4 p3 = { 0.0f, rc.height(), 0.0f, 1.0f };
	glm::vec2 texSourceSize = tex ? glm::vec2(tex->width(), tex->height()) : glm::vec2(0.0f);
	glm::vec2 texTargetOffset = { texRect.x(), texRect.y() };
	glm::vec2 texTargetSize = { texRect.width(), texRect.height() };
	glm::vec2 texCoord0 = { texTargetOffset / texSourceSize };
	glm::vec2 texCoord1 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, texTargetOffset.y / texSourceSize.y };
	glm::vec2 texCoord2 = { (texTargetOffset.x + texTargetSize.x) / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };
	glm::vec2 texCoord3 = { texTargetOffset.x / texSourceSize.x, (texTargetOffset.y + texTargetSize.y) / texSourceSize.y };

	s_Data.quadBufferPtr->position = transform * p0 + position;
	s_Data.quadBufferPtr->color = color;
	s_Data.quadBufferPtr->texCoord = rotated ? texCoord1 : texCoord0;// { 0.0f, 0.0f };
	s_Data.quadBufferPtr->texIndex = textureIndex;
	s_Data.quadBufferPtr->opacity = opacity;
	s_Data.quadBufferPtr++;

	s_Data.quadBufferPtr->position = transform * p1 + position;
	s_Data.quadBufferPtr->color = color;
	s_Data.quadBufferPtr->texCoord = rotated ? texCoord2 : texCoord1;// { 1.0f, 0.0f };
	s_Data.quadBufferPtr->texIndex = textureIndex;
	s_Data.quadBufferPtr->opacity = opacity;
	s_Data.quadBufferPtr++;

	s_Data.quadBufferPtr->position = transform * p2 + position;
	s_Data.quadBufferPtr->color = color;
	s_Data.quadBufferPtr->texCoord = rotated ? texCoord3 : texCoord2;// { 1.0f, 1.0f };
	s_Data.quadBufferPtr->texIndex = textureIndex;
	s_Data.quadBufferPtr->opacity = opacity;
	s_Data.quadBufferPtr++;

	s_Data.quadBufferPtr->position = transform * p3 + position;
	s_Data.quadBufferPtr->color = color;
	s_Data.quadBufferPtr->texCoord = rotated ? texCoord0 : texCoord3;// { 0.0f, 1.0f };
	s_Data.quadBufferPtr->texIndex = textureIndex;
	s_Data.quadBufferPtr->opacity = opacity;
	s_Data.quadBufferPtr++;

	s_Data.usedIndexCount += 6;
	s_Data.RenderStats.quadCount++;
}

void Renderer2D::drawEffect(const Rect& rc, const glm::mat4 & transform, ref<Material> material, const std::vector<ref<Light>> &lights)
{
	endBatch();

	glm::vec4 position = {rc.x(), rc.y(), 0.0f, 1.0f };
	glm::vec4 p0 = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 p1 = { rc.width(), 0.0f, 0.0f, 1.0f };
	glm::vec4 p2 = { rc.width(), rc.height(), 0.0f, 1.0f };
	glm::vec4 p3 = { 0.0f, rc.height(), 0.0f, 1.0f };
	std::vector<Vertex> vertexs(4);
	vertexs[0].position = transform * p0 + position;
	vertexs[1].position = transform * p1 + position;
	vertexs[2].position = transform * p2 + position;
	vertexs[3].position = transform * p3 + position;
	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
	vertexs[1].texCoord = glm::vec2(1.0, 0.0);
	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
	std::vector<uint16_t> indices = { 0, 1, 2, 0, 2, 3 };
	auto mesh = createRef<Mesh>(vertexs, indices, material);
	mesh->draw(glm::mat4(1.0), sharedCamera2D(), lights);

	_beginBatch(false);
}

#include <codecvt>
void Renderer2D::drawText(ref<Font> font, const Point & pt, const std::string & text)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	std::wstring unicodeStr = cvt.from_bytes(text);

	Point offset = pt;
	for (int i = 0; i != unicodeStr.size(); ++i)
	{
		auto glyph = nb::getGlyph(font, unicodeStr[i]);
		Rect drawRC(glyph->rc.x() + offset.x, glyph->rc.y() + offset.y, glyph->rc.size());
		offset += { glyph->advanceX, 0.0f };

		auto tex = glyph->texture;
		Rect texRect = Rect(glyph->uv[3].x * tex->width(), glyph->uv[3].y * tex->height(), 
			(glyph->uv[2].x - glyph->uv[3].x) * tex->width(), (glyph->uv[0].y - glyph->uv[3].y) * tex->height());

		drawImage(drawRC, glm::mat4(1.0f), tex, texRect, false, 1.0f);
	}
}
