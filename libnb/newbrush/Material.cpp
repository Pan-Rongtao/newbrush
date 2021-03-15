#include "newbrush/Material.h"
#include "newbrush/Shader.h"
#include "newbrush/Camera.h"
#include "newbrush/Texture.h"

using namespace nb;

Material::Material(ref<Shader> _shader) 
	: shader(_shader) 
{}

////////////////
SolidColorMaterial::SolidColorMaterial()
	: SolidColorMaterial(Colors::black)
{}

SolidColorMaterial::SolidColorMaterial(const Color &_color)
	: Material(ShaderLibrary::get("system_color"))
	, color(_color)
{}

void SolidColorMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	shader->setFloat4("color", glm::vec4(color.rf(), color.gf(), color.bf(), color.af()));
}

///////
LinearGrandientMaterial::LinearGrandientMaterial()
	: LinearGrandientMaterial(800.0f, {})
{}

LinearGrandientMaterial::LinearGrandientMaterial(float _lenght, const std::vector<GradientStop> &_grandients)
	: Material(ShaderLibrary::get("system_linear"))
	, lenght(_lenght)
	, grandients(_grandients)
	, vertical(true)
{}

void LinearGrandientMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader || grandients.empty())	return;

	std::vector<glm::vec4> colors;
	std::vector<float> offsets;
	for (auto const &one : grandients)
	{
		colors.push_back(glm::vec4(one.color.rf(), one.color.gf(), one.color.bf(), one.color.af()));
		offsets.push_back(one.offset);
	}

	shader->setFloat("lenght", lenght);
	shader->setInt("size", grandients.size());
	shader->setFloatArray("offsets", offsets);
	shader->setFloat4Array("colors", colors);
	shader->setBool("vertical", vertical);
}

/////////////
PhongMaterial::PhongMaterial()
	: Material(ShaderLibrary::get("system_phong"))
	, shineness(32.0f)
	, opacity(1.0f)
{}

void PhongMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	auto cm = nb::as<PerspectiveCamera>(camera);
	if(cm)
		shader->setFloat3("viewPos", cm->getTranslate());
	if (diffuseMapping)
	{
		diffuseMapping->activeAndBind();
		if (specularMapping) specularMapping->activeAndBind();
		if (emissionMapping) emissionMapping->activeAndBind();
	}
	else
	{
		shader->setFloat3("material.ambient", { ambient.rf(), ambient.gf(), ambient.bf() });
		shader->setFloat3("material.diffuse", { diffuse.rf(), diffuse.gf(), diffuse.bf() });
		shader->setFloat3("material.specular", { specular.rf(), specular.gf(), specular.bf() });
		shader->setFloat3("material.emission", { emission.rf(), emission.gf(), emission.bf() });
		shader->setFloat("opacity", opacity);
	}

	shader->setBool("hasTexture", diffuseMapping || specularMapping || emissionMapping);
	shader->setFloat("material.shininess", shineness);
}

///////////////
SkyBoxMaterial::SkyBoxMaterial()
	: SkyBoxMaterial(nullptr) 
{}

SkyBoxMaterial::SkyBoxMaterial(ref<Texture> _cubeMapping)
	: Material(ShaderLibrary::get("system_skybox"))
	, cubeMapping(_cubeMapping) 
{}

void SkyBoxMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader) 
		return;

	if (cubeMapping)
		cubeMapping->activeAndBind();
}

//////////////////
CubemapMaterial::CubemapMaterial()
	: Material(ShaderLibrary::get("system_cubePhong"))
	, ambient(Color(128, 128, 128))
	, diffuse(Color(0, 0, 0))
	, specular(Color(0, 0, 0))
	, cubeMapColor(Color(255, 255, 255))
{}

void CubemapMaterial::uploadUniform(ref<Camera> camera)
{
	if (!shader)
		return;

	auto cm = nb::as<PerspectiveCamera>(camera);
	if (cm)
		shader->setFloat3("viewPos", cm->getTranslate());
	if (diffuseMapping)
	{
		shader->setBool("hasTextures", true);
		diffuseMapping->activeAndBind();
	}
	else
	{
		shader->setBool("hasTextures", false);
	}

	if (cubeMapping)
	{
		shader->setBool("hasCubemap", true);
		cubeMapping->activeAndBind();
	}
	else
	{
		shader->setBool("hasCubemap", false);
	}
	shader->setFloat3("material.ambient", { ambient.rf(), ambient.gf(), ambient.bf() });
	shader->setFloat3("material.diffuse", { diffuse.rf(), diffuse.gf(), diffuse.bf() });
	shader->setFloat3("material.specular", { specular.rf(), specular.gf(), specular.bf() });
	shader->setFloat3("material.cubemapColor", { cubeMapColor.rf(), cubeMapColor.gf(), cubeMapColor.bf() });
}
