#include "newbrush/Application.h"
#include "newbrush/Shader.h"

using namespace nb;

void Light::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	shader->setFloat3("light.ambient", glm::vec3(ambient.rf(), ambient.gf(), ambient.bf()));
	shader->setFloat3("light.diffuse", glm::vec3(diffuse.rf(), diffuse.gf(), diffuse.bf()));
	shader->setFloat3("light.specular", glm::vec3(specular.rf(), specular.gf(), specular.bf()));
}

void DirectionalLight::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	Light::uploadUniform(shader);
	shader->setFloat3("light.direction", direction);
}

void PointLightBase::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	Light::uploadUniform(shader);
	shader->setFloat3("light.position", position);
	shader->setFloat("light.constantAttenuation", constantAttenuation);
	shader->setFloat("light.linearAttenuation", linearAttenuation);
	shader->setFloat("light.quadraticAttenuation", quadraticAttenuation);
}

void SpotLight::uploadUniform(ref<Shader> shader) const
{
	if (!shader) return;

	PointLightBase::uploadUniform(shader);
	shader->setFloat3("light.direction", direction);
	shader->setFloat("light.innerConeAngle", innerConeAngle);
	shader->setFloat("light.outerConeAngle", outerConeAngle);
}
