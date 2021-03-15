#include "newbrush/Texture.h"
#include "newbrush/GLUnit.h"
#include "newbrush/Log.h"
#include "newbrush/Bitmap.h"
#include <map>
#include "simdjson.h"

using namespace nb;
using namespace simdjson;

void glFormatAndType(int bmChannels, int &glFormat, int &glType)
{
	switch (bmChannels)
	{
	case 1:	glFormat = GL_RED;	glType = GL_UNSIGNED_BYTE;			break;
	case 2:	glFormat = GL_RGB;	glType = GL_UNSIGNED_SHORT_5_6_5;	break;
	case 3:	glFormat = GL_RGB;	glType = GL_UNSIGNED_BYTE;			break;
	case 4:	glFormat = GL_RGBA;	glType = GL_UNSIGNED_BYTE;			break;
	default:														break;
	}
}

Texture::Texture()
	: m_samplerUnit(0)
{
	glGenTextures(1, &m_handle);
	auto err = glGetError();
	nbThrowExceptionIf(err == GL_INVALID_OPERATION, std::logic_error, "glGenTextures fail, maybe glContext is not ready. err=%d", err);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
}

unsigned Texture::id() const
{
	return m_handle;
}

void Texture::setSamplerUnit(unsigned unit)
{
	m_samplerUnit = unit;
}

unsigned Texture::samplerUnit()
{
	return m_samplerUnit;
}

void Texture::activeAndBind()
{
	active();
	bind();
}

void Texture::active()
{
	glActiveTexture(GL_TEXTURE0 + m_samplerUnit);
}

////////////////////
Texture2D::Texture2D()
{
	setWrappingS(TextureWrappingE::Repeat);
	setWrappingT(TextureWrappingE::Repeat);
	setMagnifyFilter(TextureFilterE::Point);
	setNarrowFilter(TextureFilterE::Point);
}

Texture2D::Texture2D(const std::string & path)
{
	setWrappingS(TextureWrappingE::Repeat);
	setWrappingT(TextureWrappingE::Repeat);
	setMagnifyFilter(TextureFilterE::Point);
	setNarrowFilter(TextureFilterE::Point);
	update(path);
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setWrappingS(TextureWrappingE wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)(wrapping));
	unbind();
}

void Texture2D::setWrappingT(TextureWrappingE wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)(wrapping));
	unbind();
}

TextureWrappingE Texture2D::wrappingS() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &v);
	return (TextureWrappingE)v;
}

TextureWrappingE Texture2D::wrappingT() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &v);
	return (TextureWrappingE)v;
}

void Texture2D::setMagnifyFilter(TextureFilterE filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)(filter));
	unbind();
}

void Texture2D::setNarrowFilter(TextureFilterE filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)(filter));
	unbind();
}

TextureFilterE Texture2D::magnifyFilter() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &v);
	return (TextureFilterE)v;
}

TextureFilterE Texture2D::narrowFilter() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &v);
	return (TextureFilterE)v;
}

void Texture2D::update(const std::string & path)
{
	auto bm = createRef<Bitmap>(path);
	if (!bm->isValid()) 
		Log::warn("path '{}' is invalid.", path);
	else
		update(bm);
}

void Texture2D::update(ref<Bitmap> bm)
{
	int glFormat = 0, glType = 0;
	glFormatAndType(bm->channels(), glFormat, glType);
	if (glFormat != 0)
	{
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, glFormat, bm->width(), bm->height(), 0, glFormat, glType, bm->data());
		unbind();
	}
	m_width = bm->width();
	m_height = bm->height();
}

void Texture2D::genMipmap()
{
	bind();	
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
}

float Texture2D::width() const
{
	return m_width;
}

float Texture2D::height() const
{
	return m_height;
}

/////////////////
TextureCubemap::TextureCubemap()
{
	setWrappingS(TextureWrappingE::Repeat);
	setWrappingT(TextureWrappingE::Repeat);
	setMagnifyFilter(TextureFilterE::Point);
	setNarrowFilter(TextureFilterE::Point);
}

void TextureCubemap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
}

void TextureCubemap::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubemap::setWrappingS(TextureWrappingE wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (int)(wrapping));
	unbind();
}

void TextureCubemap::setWrappingT(TextureWrappingE wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (int)(wrapping));
	unbind();
}

TextureWrappingE TextureCubemap::wrappingS() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, &v);
	return (TextureWrappingE)v;
}

TextureWrappingE TextureCubemap::wrappingT() const
{
	int v = 0;
	glGetTexParameteriv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, &v);
	return (TextureWrappingE)v;
}

void TextureCubemap::setMagnifyFilter(TextureFilterE filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (int)(filter));
	unbind();
}

void TextureCubemap::setNarrowFilter(TextureFilterE filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (int)(filter));
	unbind();
}

TextureFilterE TextureCubemap::magnifyFilter() const
{
	return TextureFilterE();
}

TextureFilterE TextureCubemap::narrowFilter() const
{
	return TextureFilterE();
}

void TextureCubemap::update(const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back)
{
	auto updateOne = [](const std::string &path, int index)
	{
		Bitmap bm(path);
		int glFormat = 0, glType = 0;
		glFormatAndType(bm.channels(), glFormat, glType);
		if (glFormat != 0)
		{
			glTexImage2D(index, 0, glFormat, bm.width(), bm.height(), 0, glFormat, glType, bm.data());
		}
	};

	bind();
	updateOne(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	updateOne(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	updateOne(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	updateOne(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	updateOne(back, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	updateOne(front, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	unbind();
}

namespace nb
{
class NB_API TextureAtlas : public Texture2D, public std::enable_shared_from_this<TextureAtlas>
{
public:
	void load(const std::string &imagePath, const std::string &cfgPath);
	const TextureFrame &getFrame(const std::string &frameName);

private:
	TextureFrame parseOneFrame(const dom::object &frameObj);
	std::map<std::string, TextureFrame> m_frames;
};
}

static TextureFrame g_sInvalidFrame{ 0 };
TextureFrame TextureAtlas::parseOneFrame(const dom::object &frameObj)
{
	auto trimmed = frameObj["trimmed"].get_bool().first;
	auto rotated = frameObj["rotated"].get_bool().first;
	auto frame = frameObj["frame"].get_object().first;
	auto spriteSourceSize = frameObj["spriteSourceSize"].get_object().first;
	auto sourceSize = frameObj["sourceSize"].get_object().first;
	auto frameX = frame["x"].get_int64().first;
	auto frameY = frame["y"].get_int64().first;
	auto frameW = frame["w"].get_int64().first;
	auto frameH = frame["h"].get_int64().first;
	auto spriteSourceX = spriteSourceSize["x"].get_int64().first;
	auto spriteSourceY = spriteSourceSize["y"].get_int64().first;
	auto spriteSourceW = spriteSourceSize["w"].get_int64().first;
	auto spriteSourceH = spriteSourceSize["h"].get_int64().first;
	auto sourceW = sourceSize["w"].get_int64().first;
	auto sourceH = sourceSize["h"].get_int64().first;

	TextureFrame texFrame;
	texFrame.offset			= { (float)frameX, (float)frameY };
	texFrame.size			= { (float)spriteSourceW, (float)spriteSourceH };
	texFrame.trimmedSize	= { (float)spriteSourceX, (float)spriteSourceY };
	texFrame.rotated		= { rotated };
	return texFrame;
}

void TextureAtlas::load(const std::string &imagePath, const std::string & cfgPath)
{
	update(imagePath);

	dom::parser parser;
	auto result = parser.load(cfgPath);
	nbThrowExceptionIf(result.second, std::runtime_error, "parsing[%s] fail, error=[%d], error_message=[%s]",
		cfgPath.data(), result.second, error_message(result.second));

	auto frames = parser.doc.root()["frames"].get_object().first;
	for (auto const &f : frames)
	{
		std::string key = f.key.data();
		TextureFrame texFrame = parseOneFrame(f.value.get_object().first);
		texFrame.texture = shared_from_this();// m_texture;
		m_frames.insert({ key, texFrame });
	}
}

const TextureFrame &TextureAtlas::getFrame(const std::string & frameName)
{
	auto iter = m_frames.find(frameName);
	return iter == m_frames.end() ? g_sInvalidFrame : iter->second;
}

std::map<std::string, ref<Texture>> g_textures;
ref<Texture2D> TextureLibrary::addTexture2D(const std::string & name, const std::string & imagePath)
{
	auto iter = g_textures.find(name);
	if (iter != g_textures.end())
	{
		nbThrowException(std::logic_error, "[%s] is already exists.", name.data());
		return nullptr;
	}
	else
	{
		auto tex = createRef<Texture2D>(imagePath);
		g_textures[name] = tex;
		return tex;
	}

}

void TextureLibrary::addTextureAtlas(const std::string &name, const std::string & imagePath, const std::string & cfgPath)
{
	auto iter = g_textures.find(name);
	nbThrowExceptionIf(iter != g_textures.end(), std::logic_error, "[%s] is already exists.", name.data());

	auto texAtlases = createRef<TextureAtlas>();
	texAtlases->load(imagePath, cfgPath);
	g_textures[name] = texAtlases;
}

void TextureLibrary::addTextureCubemap(const std::string &name, const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back)
{
	auto iter = g_textures.find(name);
	nbThrowExceptionIf(iter != g_textures.end(), std::logic_error, "[%s] is already exists.", name.data());

	auto texCubemap = createRef<TextureCubemap>();
	texCubemap->update(top, bottom, left, right, front, back);
	g_textures[name] = texCubemap;
}

ref<Texture2D> TextureLibrary::getTexture2D(const std::string & name)
{
	auto iter = g_textures.find(name);
	return iter == g_textures.end() ? nullptr : as<Texture2D>(iter->second);
}

const TextureFrame &TextureLibrary::getFrameFromTextureAtlas(const std::string &name, const std::string &frameName)
{
	auto iter = g_textures.find(name);
	if (iter == g_textures.end())
	{
		return g_sInvalidFrame;
	}
	else
	{
		auto texAtlas = as<TextureAtlas>(iter->second);
		return texAtlas ? texAtlas->getFrame(frameName) : g_sInvalidFrame;
	}
}

ref<TextureCubemap> TextureLibrary::getTextureCubemap(const std::string & name)
{
	auto iter = g_textures.find(name);
	return iter == g_textures.end() ? nullptr : as<TextureCubemap>(iter->second);
}
