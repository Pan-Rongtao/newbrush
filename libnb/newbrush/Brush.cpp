#include "newbrush/Brush.h"

using namespace nb;

Brush::Brush()
	: opacity(1.0f)
{}

SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(Color())
{}

SolidColorBrush::SolidColorBrush(const Color &_color)
	: color(_color)
{}

ref<SolidColorBrush> SolidColorBrush::get(const Color & c)
{
	ref<SolidColorBrush> brush = createRef<SolidColorBrush>(c);
	return brush;
}

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(ref<Texture2D> _texture)
	: ImageBrush(_texture, { 0.0f, 0.0f }, { _texture ? _texture->width() : 0.0f, _texture ? _texture->height() : 0.0f }, false)
{
}

ImageBrush::ImageBrush(ref<Texture2D> _texture, const glm::vec2 & _targetOffset, const glm::vec2 & _targetSize, bool _rotated)
	: texture(_texture)
	, targetOffset(_targetOffset)
	, targetSize(_targetSize)
	, rotated(_rotated)
{
}

ref<ImageBrush> ImageBrush::createWitchTextureFrame(const TextureFrame & texFrame)
{
	glm::vec2 targetSize = texFrame.rotated ? glm::vec2(texFrame.size.y, texFrame.size.x) : glm::vec2(texFrame.size.x, texFrame.size.y);
	auto brush = createRef<ImageBrush>(texFrame.texture, texFrame.offset, targetSize, texFrame.rotated);
	return brush;
}

ref<ImageBrush> ImageBrush::createWitchTextureFrameName(const std::string & texAtlasKey, const std::string & frameName)
{
	auto texFrame = TextureLibrary::getFrameFromTextureAtlas(texAtlasKey, frameName);
	return createWitchTextureFrame(texFrame);
}

EffectBrush::EffectBrush()
	: EffectBrush(nullptr, nullptr)
{
}

EffectBrush::EffectBrush(ref<Material> _material, ref<Light> _light)
	: material(_material)
	, light(_light)
{
}

static std::map<std::string, ref<Brush>> g_brushes;
void BrushLibrary::add(const std::string & name, ref<Brush> brush)
{
	auto ret = g_brushes.insert({ name, brush });
	nbThrowExceptionIf(!ret.second, std::logic_error, "brush [%s] is already exist.", name.data());
}

void BrushLibrary::addSolidColorBrush(const std::string & name, const Color & color)
{
	add(name, createRef<SolidColorBrush>(color));
}

void BrushLibrary::addImageBrush(const std::string & name, const std::string & imagePath)
{
	add(name, createRef<ImageBrush>(createRef<Texture2D>(imagePath)));
}

void BrushLibrary::addImageBrushFromTextureAtlas(const std::string &name, const std::string &texAtlasKey, const std::string &frameName)
{
	add(name, ImageBrush::createWitchTextureFrameName(texAtlasKey, frameName));
}

ref<Brush> BrushLibrary::get(const std::string & name)
{
	auto iter = g_brushes.find(name);
	return iter == g_brushes.end() ? nullptr : iter->second;
}
