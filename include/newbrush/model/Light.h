#pragma once
#include "newbrush/model/Object.h"
#include "newbrush/model/Any.h"
#include "newbrush/model/Color.h"
#include "newbrush/glm.h"

namespace nb {

//光基类
class NB_API Light : public Object
{
	RTTR_ENABLE(Object)
public:
	virtual ~Light() = default;

	void setName(const std::string &name);
	const std::string &name() const;

	void setAmbient(const Color &ambient);
	const Color &ambient() const;

	void setDiffuse(const Color &diffuse);
	const Color &diffuse() const;

	void setSpecular(const Color &specular);
	const Color &specular() const;

	virtual std::vector<std::pair<std::string, var>> toUniforms() const;

protected:
	Light();

private:
	std::string m_name;
	Color m_ambient;
	Color m_diffuse;
	Color m_specular;
};

//环境光
class NB_API AmbientLight : public Light
{
	RTTR_ENABLE(Light)
public:
	AmbientLight() = default;
};

//方向光
class NB_API DirectionalLight : public Light
{
	RTTR_ENABLE(Light)
public:
	DirectionalLight();

	void setDirection(const glm::vec3 &direction);
	const glm::vec3 &direction() const;

	virtual std::vector<std::pair<std::string, var>> toUniforms() const override;

private:
	glm::vec3 m_direction;	//方向
};

//点光源基类
class NB_API PointLightBase : public Light
{
	RTTR_ENABLE(Light)
public:
	void setPosition(const glm::vec3 &position);
	const glm::vec3 &position() const;

	void setConstantAttenuation(float constantAttenuation);
	float constantAttenuation() const;

	void setLinearAttenuation(float linearAttenuation);
	float linearAttenuation() const;

	void setQuadraticAttenuation(float quadraticAttenuation);
	float quadraticAttenuation();

	virtual std::vector<std::pair<std::string, var>> toUniforms() const override;

protected:
	PointLightBase();

private:
	glm::vec3 m_position;			//光位置
	float m_constantAttenuation;	//光强度按其随距离减弱的常数值
	float m_linearAttenuation;		//光强度随距离线性减弱的值
	float m_quadraticAttenuation;	//光效果随距离而减弱的值（由二次运算计算所得）
};

//点光源
class NB_API PointLight : public PointLightBase
{
	RTTR_ENABLE(PointLightBase)
public:
	PointLight();

};

//聚光灯
class NB_API SpotLight : public PointLightBase
{
	RTTR_ENABLE(PointLightBase)
public:
	SpotLight();

	void setDirection(const glm::vec3 &direction);
	const glm::vec3 &direction() const;

	void setInnerConeAngle(float innerConeAngle);
	float innerConeAngle() const;

	void setOuterConeAngle(float outerConeAngle);
	float outerConeAngle() const;

	virtual std::vector<std::pair<std::string, var>> toUniforms() const override;

private:
	glm::vec3 m_direction;	//投射光线的方向
	float m_innerConeAngle;	//内圈锥形投影部分的角度
	float m_outerConeAngle;	//外圈锥形投影部分的角度

};

using LightPtr = std::shared_ptr<Light>;
using AmbientLightPtr = std::shared_ptr<AmbientLight>;
using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
using PointLightPtr = std::shared_ptr<PointLight>;
using SpotLightPtr = std::shared_ptr<SpotLight>;

}