#pragma once
#include "newbrush/Object.h"
#include "newbrush/Types.h"
#include "newbrush/Texture.h"
#include "newbrush/Material.h"
#include "newbrush/Light.h"

namespace nb
{

class NB_API Brush : public Object
{
	RTTR_ENABLE(Object)
public:
	virtual ~Brush() = default;

	float opacity;

protected:
	Brush();

};

class NB_API SolidColorBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	SolidColorBrush();
	SolidColorBrush(const Color &_color);

	static ref<SolidColorBrush> get(const Color &c);

	Color color;
};

class NB_API LinearGradientBrush : public Brush
{
public:
	glm::vec2 startPoint;
	glm::vec2 endPoint;
	std::vector<std::pair<float, Color>> stops;
};

class NB_API ImageBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	ImageBrush();
	ImageBrush(ref<Texture2D> texture);
	ImageBrush(ref<Texture2D> texture, const glm::vec2 &targetOffset, const glm::vec2 &targetSize, bool _rotated);

	static ref<ImageBrush> createWitchTextureFrame(const TextureFrame &texFrame);
	static ref<ImageBrush> createWitchTextureFrameName(const std::string &texAtlasKey, const std::string &frameName);

	ref<Texture2D> texture;
	glm::vec2 targetOffset;
	glm::vec2 targetSize;
	bool rotated;
};

class NB_API EffectBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	EffectBrush();
	EffectBrush(ref<Material> material, ref<Light> light = nullptr);

	ref<Material> material;
	ref<Light> light;
};

class NB_API BrushLibrary
{
public:
	static void add(const std::string &name, ref<Brush> brush);
	static void addSolidColorBrush(const std::string &name, const Color &color);
	static void addImageBrush(const std::string &name, const std::string &imagePath);
	static void addImageBrushFromTextureAtlas(const std::string &name, const std::string &texAtlasKey, const std::string &frameName);
	static ref<Brush> get(const std::string &name);
};

}