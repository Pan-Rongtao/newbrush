#pragma once
#include "newbrush/Node.h"
#include "newbrush/Types.h"

namespace nb 
{

class Shader;

//光基类
class NB_API Light : public Node
{
	RTTR_ENABLE(Node)
public:
	virtual ~Light() = default;

	virtual void uploadUniform(ref<Shader> shader) const;

	std::string name;
	Color ambient{ 127, 127, 127 };
	Color diffuse{ 127, 127, 127 };
	Color specular{ 127, 127, 127 };
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
	DirectionalLight() : direction(glm::vec3(0.0, 0.0, -1.0)) {}

	virtual void uploadUniform(ref<Shader> shader) const override;

	glm::vec3 direction;
};

//点光源基类
class NB_API PointLightBase : public Light
{
	RTTR_ENABLE(Light)
public:
	virtual void uploadUniform(ref<Shader> shader) const override;

	glm::vec3 position{0.0f, 0.0f, 5.0f};			//光位置
	float constantAttenuation{1.0f};	//光强度按其随距离减弱的常数值
	float linearAttenuation{0.0f};		//光强度随距离线性减弱的值
	float quadraticAttenuation{0.0f};	//光效果随距离而减弱的值（由二次运算计算所得）
};

//点光源
class NB_API PointLight : public PointLightBase
{
	RTTR_ENABLE(PointLightBase)
public:
	PointLight() = default;

};

//聚光灯
class NB_API SpotLight : public PointLightBase
{
	RTTR_ENABLE(PointLightBase)
public:
	virtual void uploadUniform(ref<Shader> shader) const override;

	glm::vec3 direction{ 0.0f, 0.0f, -1.0f };	//投射光线的方向
	float innerConeAngle{90.0f};				//内圈锥形投影部分的角度
	float outerConeAngle{180.0f};				//外圈锥形投影部分的角度
};

}