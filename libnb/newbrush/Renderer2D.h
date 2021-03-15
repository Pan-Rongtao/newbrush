#pragma once
#include "glm/glm.hpp"
#include "newbrush/Material.h"
#include "newbrush/Light.h"
#include "newbrush/Types.h"
#include "newbrush/Texture.h"
#include "newbrush/Brush.h"

namespace nb
{

class Renderer2D
{
public:
	static void beginBatch();

	static void drawPolyline(ref<Brush> brush, const std::vector<glm::vec2> &points, float size, const glm::vec2 &offset);
	static void drawPolygon(ref<Brush> brush, const std::vector<glm::vec2> &points, const glm::vec2 &offset);

	static void drawRect(const Rect &rc, const glm::mat4 &transform, const glm::vec4& color, float opacity);
	static void drawImage(const Rect &rc, const glm::mat4 &transform, ref<Texture2D> tex, const Rect &texRect, bool rotated, float opacity);
	static void drawEffect(const Rect &rc, const glm::mat4 &transform, ref<Material> material, const std::vector<ref<Light>> &lights);

	static void endBatch();


	struct Stats
	{
		unsigned drawCount = 0;
		unsigned quadCount = 0;
	};

	static const Stats& getStats();

private:
	static void init();
	static void _beginBatch(bool resetStats);
	static void shutdown();
	static void _drawQuad(const Rect &rc, const glm::mat4 &transform, const glm::vec4& color, float textureIndex, ref<Texture2D> tex, const Rect &texRect, bool rotated, float opacity);
};

}