#include "newbrush/model/Material.h"

using namespace nb;

void Material::setName(const std::string & name)
{
	m_name = name;
}

const std::string & Material::name() const
{
	return m_name;
}

void Material::setProgram(ProgramPtr program)
{
	m_program = program;
}

ProgramPtr Material::program()
{
	return m_program;
}

void Material::uploadUniform(CameraPtr camera)
{
}

Material::Material(ProgramPtr program)
	: m_program(program)
{
}
/////////////////
SolidColorMaterial::SolidColorMaterial()
	: SolidColorMaterial(Colors::black())
{
}

SolidColorMaterial::SolidColorMaterial(const Color & color)
	: Material(Programs::primitive())
	, m_color(color)
{
}

void SolidColorMaterial::setColor(const Color & color)
{
	m_color = color;
}

const Color & SolidColorMaterial::color() const
{
	return m_color;
}

void SolidColorMaterial::uploadUniform(CameraPtr camera)
{
	if (!m_program)	return;

	m_program->uniform(m_program->getUniformLocation("color"), glm::vec4(m_color.redF(), m_color.greenF(), m_color.blueF(), m_color.alphaF()));
}
/////////////////////
ImageMaterial::ImageMaterial()
	: ImageMaterial(nullptr)
{
}

ImageMaterial::ImageMaterial(const TexturePtr &texture)
	: Material(Programs::image())
	, m_texture(texture)
{
}

void ImageMaterial::setTexture(const TexturePtr &texture)
{
	m_texture = texture;
}

const TexturePtr &ImageMaterial::texture() const
{
	return m_texture;
}

void ImageMaterial::uploadUniform(CameraPtr camera)
{
	if (!m_program)	return;

	if (m_texture)
	{
		m_texture->bind();
		m_texture->active();
	}
}

////////////////////
LinearGrandientMaterial::LinearGrandientMaterial()
	: LinearGrandientMaterial(800.0f, {})
{
}

LinearGrandientMaterial::LinearGrandientMaterial(float height, const std::vector<GradientStop> &grandients)
	: Material(Programs::gradientPrimitive())
	, m_height(height)
	, m_grandients(grandients)
{
}

void LinearGrandientMaterial::setHeight(float height)
{
	m_height = height;
}

float LinearGrandientMaterial::height() const
{
	return m_height;
}

void LinearGrandientMaterial::setGrandients(const std::vector<GradientStop> &grandients)
{
	m_grandients = grandients;
}

const std::vector<GradientStop> &LinearGrandientMaterial::grandients()
{
	return m_grandients;
}

void LinearGrandientMaterial::uploadUniform(CameraPtr camera)
{
	if (!m_program || m_grandients.empty())	return;

	std::vector<glm::vec4> colors;
	std::vector<float> offsets;
	for (auto const &one : m_grandients)
	{
		colors.push_back(glm::vec4(one.color.redF(), one.color.greenF(), one.color.blueF(), one.color.alphaF()));
		offsets.push_back(one.offset);
	}

	m_program->uniform(m_program->getUniformLocation("height"), m_height);
	m_program->uniform(m_program->getUniformLocation("size"), (int)m_grandients.size());
	m_program->uniform(m_program->getUniformLocation("offsets"), offsets);
	m_program->uniform(m_program->getUniformLocation("colors"), colors);
}

//////////////
PhongMaterial::PhongMaterial()
	: Material(Programs::phong())
	, m_shineness(3.0)
{
}

void PhongMaterial::uploadUniform(CameraPtr camera)
{
	if (!m_program)	return;

	m_program->uniform(m_program->getUniformLocation("viewPos"), camera->position());
	if (m_diffuseMapping)
	{
		m_diffuseMapping->bind();
		m_diffuseMapping->active();
		if (m_specularMapping)
		{
			m_specularMapping->bind();
			m_specularMapping->active();
		}
		if (m_emissionMapping)
		{
			m_emissionMapping->bind();
			m_emissionMapping->active();
		}
	}
	else
	{
		m_program->uniform(m_program->getUniformLocation("material.ambient"), glm::vec3(m_ambient.redF(), m_ambient.greenF(), m_ambient.blueF()));
		m_program->uniform(m_program->getUniformLocation("material.diffuse"), glm::vec3(m_diffuse.redF(), m_diffuse.greenF(), m_diffuse.blueF()));
		m_program->uniform(m_program->getUniformLocation("material.specular"), glm::vec3(m_specular.redF(), m_specular.greenF(), m_specular.blueF()));
		m_program->uniform(m_program->getUniformLocation("material.emission"), glm::vec3(m_emission.redF(), m_emission.greenF(), m_emission.blueF()));
	}
	m_program->uniform(m_program->getUniformLocation("hasTexture"), m_diffuseMapping || m_specularMapping || m_emissionMapping);
	m_program->uniform(m_program->getUniformLocation("material.shininess"), m_shineness);
}

void PhongMaterial::setAmbient(const Color & ambient)
{
	m_ambient = ambient;
}

const Color& PhongMaterial::ambient() const
{
	return m_ambient;
}

void PhongMaterial::setDiffuse(const Color & diffuse)
{
	m_diffuse = diffuse;
}

const Color& PhongMaterial::diffuse() const
{
	return m_diffuse;
}

void PhongMaterial::setSpecular(const Color & specular)
{
	m_specular = specular;
}

const Color& PhongMaterial::specular() const
{
	return m_specular;
}

void PhongMaterial::setEmission(const Color & emission)
{
	m_emission = emission;
}

const Color & PhongMaterial::emission() const
{
	return m_emission;
}

void PhongMaterial::setShineness(const float &shineness)
{
	m_shineness = shineness;
}

const float & PhongMaterial::shineness() const
{
	return m_shineness;
}

void PhongMaterial::setDiffuseMapping(TexturePtr diffuseMapping)
{
	m_diffuseMapping = diffuseMapping;
}

TexturePtr PhongMaterial::diffuseMapping()
{
	return m_diffuseMapping;
}

void PhongMaterial::setSpecularMapping(TexturePtr specularMapping)
{
	m_specularMapping = specularMapping;
}

TexturePtr PhongMaterial::specularMapping()
{
	return m_specularMapping;
}

void PhongMaterial::setEmissionMapping(TexturePtr emissionMapping)
{
	m_emissionMapping = emissionMapping;
}

TexturePtr PhongMaterial::emissionMapping()
{
	return m_emissionMapping;
}

///////////////////////////
CubemapMaterial::CubemapMaterial()
	: Material(Programs::cube())
	, m_ambient(Color(0, 0, 0))
	, m_diffuse(Color(168, 168, 168))
	, m_specular(Color(0, 0, 0))
{
}

void CubemapMaterial::uploadUniform(CameraPtr camera)
{
	if (!m_program)	return;

	m_program->uniform(m_program->getUniformLocation("viewPos"), camera->position());
	if (m_diffuseMapping)
	{
		m_program->uniform(m_program->getUniformLocation("hasTextures"), true);
		m_diffuseMapping->bind();
		m_diffuseMapping->active();
	}
	else
	{
		m_program->uniform(m_program->getUniformLocation("hasTextures"), false);
	}

	if (m_cubeMapping)
	{
		m_program->uniform(m_program->getUniformLocation("hasCubemap"), true);
		m_cubeMapping->bind();
		m_cubeMapping->active();
	}
	else
	{
		m_program->uniform(m_program->getUniformLocation("hasCubemap"), false);
	}
	m_program->uniform(m_program->getUniformLocation("material.ambient"), glm::vec3(m_ambient.redF(), m_ambient.greenF(), m_ambient.blueF()));
	m_program->uniform(m_program->getUniformLocation("material.diffuse"), glm::vec3(m_diffuse.redF(), m_diffuse.greenF(), m_diffuse.blueF()));
	m_program->uniform(m_program->getUniformLocation("material.specular"), glm::vec3(m_specular.redF(), m_specular.greenF(), m_specular.blueF()));
}

void CubemapMaterial::setAmbient(const Color & ambient)
{
	m_ambient = ambient;
}

const Color& CubemapMaterial::ambient() const
{
	return m_ambient;
}

void CubemapMaterial::setDiffuse(const Color & diffuse)
{
	m_diffuse = diffuse;
}

const Color& CubemapMaterial::diffuse() const
{
	return m_diffuse;
}

void CubemapMaterial::setSpecular(const Color & specular)
{
	m_specular = specular;
}

const Color& CubemapMaterial::specular() const
{
	return m_specular;
}

void CubemapMaterial::setDiffuseMapping(TexturePtr diffuseMapping)
{
	m_diffuseMapping = diffuseMapping;
}

TexturePtr CubemapMaterial::diffuseMapping()
{
	return m_diffuseMapping;
}

void CubemapMaterial::setCubeMapping(TexturePtr cubeMapping)
{
	m_cubeMapping = cubeMapping;
}

TexturePtr CubemapMaterial::cubeMapping()
{
	return m_cubeMapping;
}

////////////////////
void VarMaterial::uploadUniform(CameraPtr camera)
{
	if (!m_program)	return;

	for (auto const &iter : m_uniforms)
	{
		auto location = m_program->getUniformLocation(iter.first.data());
		auto const &v = iter.second;
		m_program->uniformVar(location, v);
	}
}
