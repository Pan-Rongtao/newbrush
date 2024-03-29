#include "newbrush/rvl/gles/Material.h"

using namespace nb;

Material::Material()
{
}

Material::Material(const std::vector<TexturePtr> &textures)
	: m_textures(textures)
{
}

Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
	: m_ambient(ambient)
	, m_diffuse(diffuse)
	, m_specular(specular)
{
}

std::vector<TexturePtr>& Material::textures()
{
	return m_textures;
}

const std::vector<TexturePtr>& Material::textures() const
{
	return m_textures;
}

glm::vec3& Material::getAmbient()
{
	return m_ambient;
}
const glm::vec3& Material::getAmbient() const
{
	return m_ambient;
}

glm::vec3& Material::getDiffuse()
{
	return m_diffuse;
}

const glm::vec3& Material::getDiffuse() const
{
	return m_diffuse;
}

glm::vec3& Material::getSpecular()
{
	return m_specular;
}

const glm::vec3& Material::getSpecular() const
{
	return m_specular;
}
