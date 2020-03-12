#include "newbrush/gles/Material.h"
#include "newbrush/gles/Program.h"

using namespace nb;

Material::Material()
{
}

Material::Material(const std::vector<std::shared_ptr<Texture>> &textures)
	: m_textures(textures)
{
}

std::vector<std::shared_ptr<Texture>>& Material::textures()
{
	return m_textures;
}

const std::vector<std::shared_ptr<Texture>>& Material::textures() const
{
	return m_textures;
}
