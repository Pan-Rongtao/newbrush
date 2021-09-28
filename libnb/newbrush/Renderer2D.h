#pragma once
#include "newbrush/Brush.h"
#include "newbrush/Font.h"

namespace nb
{

class Renderer2D
{
public:
	static void beginBatch();

	//rcClip为负表示不裁剪
	static void drawRect(const Rect &rc, const glm::mat4 &transform, const glm::vec4& color, float opacity, const Rect &rcClip = {-1.0f, -1.0f, -1.0f, -1.0f});
	static void drawImage(const Rect &rc, const glm::mat4 &transform, const TextureFrame &texFrame, float opacity, const Rect &rcClip = { -1.0f, -1.0f, -1.0f, -1.0f });
	static void drawEffect(const Rect &rc, const glm::mat4 &transform, ref<Material> material, const std::vector<ref<Light>> &lights, const Rect &rcClip = { -1.0f, -1.0f, -1.0f, -1.0f });

	static void drawText(ref<Font> font, const Point &pt, const std::string &text, const glm::vec4 &color = glm::vec4(0.0, 0.0, 0.0, 1.0), float opacity = 1.0f);
	static void drawText(ref<Font> font, const Point &pt, const std::wstring &unicodeStr, const glm::vec4 &color = glm::vec4(0.0, 0.0, 0.0, 1.0), float opacity = 1.0f);

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
	static void _drawImage(const Rect &rc, const glm::mat4 &transform, const TextureFrame &texFrame, float opacity, const glm::vec4& color);
};

}