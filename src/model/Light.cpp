#include "newbrush/model/Light.h"

using namespace nb;

Light::Light()
	: m_ambient(Colors::white())
	, m_diffuse(Colors::white())
	, m_specular(Colors::white())
{
}

void Light::setName(const std::string & name)
{
	m_name = name;
}

const std::string & Light::name() const
{
	return m_name;
}

void Light::setAmbient(const Color & ambient)
{
	m_ambient = ambient;
}

const Color & Light::ambient() const
{
	return m_ambient;
}

void Light::setDiffuse(const Color & diffuse)
{
	m_diffuse = diffuse;
}

const Color & Light::diffuse() const
{
	return m_diffuse;
}

void Light::setSpecular(const Color & specular)
{
	m_specular = specular;
}

const Color & Light::specular() const
{
	return m_specular;
}

std::vector<std::pair<std::string, var>> Light::toUniforms() const
{
	return
	{
		{ "light.ambient", glm::vec3(m_ambient.redF(), m_ambient.greenF(), m_ambient.blueF()) },
		{ "light.diffuse", glm::vec3(m_diffuse.redF(), m_diffuse.greenF(), m_diffuse.blueF()) },
		{ "light.specular", glm::vec3(m_specular.redF(), m_specular.greenF(), m_specular.blueF()) },
	};
}

////////////////
DirectionalLight::DirectionalLight()
	: m_direction(glm::vec3(0.0, 0.0, -1.0))
{
}

void DirectionalLight::setDirection(const glm::vec3 & direction)
{
	m_direction = direction;
}

const glm::vec3 &DirectionalLight::direction() const
{
	return m_direction;
}

std::vector<std::pair<std::string, var>> DirectionalLight::toUniforms() const
{
	auto ret = Light::toUniforms();
	ret.insert(ret.end(),
	{
		{ "light.direction", m_direction },
	});
	return ret;
}

//////////
PointLightBase::PointLightBase()
	: m_position(glm::vec3(5.0))
	, m_constantAttenuation(1.0)
	, m_linearAttenuation(0.0)
	, m_quadraticAttenuation(0.0)
{
}

void PointLightBase::setPosition(const glm::vec3 & position)
{
	m_position = position;
}

const glm::vec3 & PointLightBase::position() const
{
	return m_position;
}

void PointLightBase::setConstantAttenuation(float constantAttenuation)
{
	m_constantAttenuation = constantAttenuation;
}

float PointLightBase::constantAttenuation() const
{
	return m_constantAttenuation;
}

void PointLightBase::setLinearAttenuation(float linearAttenuation)
{
	m_linearAttenuation;
}

float PointLightBase::linearAttenuation() const
{
	return m_linearAttenuation;
}

void PointLightBase::setQuadraticAttenuation(float quadraticAttenuation)
{
	m_quadraticAttenuation = quadraticAttenuation;
}

float PointLightBase::quadraticAttenuation()
{
	return m_quadraticAttenuation;
}

std::vector<std::pair<std::string, var>> PointLightBase::toUniforms() const
{
	auto ret = Light::toUniforms();
	ret.insert(ret.end(),
	{
		{ "light.position", m_position },
		{ "light.constantAttenuation", m_constantAttenuation },
		{ "light.linearAttenuation", m_linearAttenuation },
		{ "light.quadraticAttenuation", m_quadraticAttenuation },
	});
	return ret;
}

////////
PointLight::PointLight()
{
}

SpotLight::SpotLight()
	: m_direction(glm::vec3(0.0, 0.0, -1.0))
	, m_innerConeAngle(90.0)
	, m_outerConeAngle(180.0)
{
}

void SpotLight::setDirection(const glm::vec3 & direction)
{
	m_direction = direction;
}

const glm::vec3 & SpotLight::direction() const
{
	return m_direction;
}

void SpotLight::setInnerConeAngle(float innerConeAngle)
{
	m_innerConeAngle = innerConeAngle;
}

float SpotLight::innerConeAngle() const
{
	return m_innerConeAngle;
}

void SpotLight::setOuterConeAngle(float outerConeAngle)
{
	m_outerConeAngle = outerConeAngle;
}

float SpotLight::outerConeAngle() const
{
	return m_outerConeAngle;
}

std::vector<std::pair<std::string, var>> SpotLight::toUniforms() const
{
	auto ret = Light::toUniforms();
	ret.insert(ret.end(),
	{
		{ "light.direction", m_direction },
		{ "light.innerConeAngle", m_innerConeAngle },
		{ "light.outerConeAngle", m_outerConeAngle },
	});
	return ret;
}
