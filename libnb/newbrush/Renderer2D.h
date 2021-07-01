#pragma once
#include "newbrush/Brush.h"
#include "newbrush/Font.h"

namespace nb
{

class Renderer2D
{
public:
	static void beginBatch();

	static void drawPolyline(ref<Brush> brush, const std::vector<glm::vec2> &points, float size, const glm::vec2 &offset);
	static void drawPolygon(ref<Brush> brush, const std::vector<glm::vec2> &points, const glm::vec2 &offset);

	static void drawRect(const Rect &rc, const glm::mat4 &transform, const glm::vec4& color, float opacity);
	static void drawImage(const Rect &rc, const glm::mat4 &transform, const TextureFrame &texFrame, float opacity);
	static void drawEffect(const Rect &rc, const glm::mat4 &transform, ref<Material> material, const std::vector<ref<Light>> &lights);

	static void drawText(ref<Font> font, const Point &pt, const std::string &text);

	static void drawBorder(const Rect &rc, const glm::vec4& color);

	static void endBatch();
	static void _beginBatch(bool resetStats);


	struct Stats
	{
		unsigned drawCount = 0;
		unsigned quadCount = 0;
	};

	static const Stats& getStats();

private:
	static void init();
	static void shutdown();
	static void _drawQuad(const Rect &rc, const glm::mat4 &transform, const glm::vec4& color, float textureIndex, const TextureFrame &texFrame, float opacity);
};

}