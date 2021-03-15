#pragma once
#include "newbrush/Object.h"
#include "newbrush/Types.h"

namespace nb 
{

class Camera;
class Shader;
class Texture;

class NB_API Material : public Object
{
	RTTR_ENABLE(Object)
public:
	//执行更新uniform的动作，在mesh渲染时调用
	virtual void uploadUniform(ref<Camera> camera) = 0;

	std::string name;
	ref<Shader> shader;

protected:
	Material() = default;
	Material(ref<Shader> _shader);

};

//////
class NB_API SolidColorMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	SolidColorMaterial();
	SolidColorMaterial(const Color &_color);

	virtual void uploadUniform(ref<Camera> camera) override;

	Color color;
};

////////////////
class NB_API GradientStop
{
public:
	float offset;
	Color color;
};

class NB_API LinearGrandientMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	LinearGrandientMaterial();
	LinearGrandientMaterial(float _lenght, const std::vector<GradientStop> &_grandients);

	virtual void uploadUniform(ref<Camera> camera) override;

	bool vertical;
	float lenght;
	std::vector<GradientStop> grandients;
};
/////////////////////////////
class NB_API PhongMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	PhongMaterial();

	virtual void uploadUniform(ref<Camera> camera) override;

	Color ambient;				//环境光影响因子
	Color diffuse;				//漫反射光影响因子
	Color specular;				//镜面高光音影响因子
	Color emission;				//自发光颜色
	float shineness;			//光照强度因子
	float opacity;
	ref<Texture> diffuseMapping;	//漫反射贴图
	ref<Texture> specularMapping;	//高光贴图
	ref<Texture> emissionMapping;	//自发光贴图
};

class NB_API SkyBoxMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	SkyBoxMaterial();
	SkyBoxMaterial(ref<Texture> _cubeMapping);

	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture> cubeMapping;
};

class NB_API CubemapMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	CubemapMaterial();

	virtual void uploadUniform(ref<Camera> camera) override;

	Color ambient;				//环境光影响因子
	Color diffuse;				//漫反射光影响因子
	Color specular;				//镜面高光音影响因子
	Color cubeMapColor;
	ref<Texture> diffuseMapping;	//漫反射贴图
	ref<Texture> cubeMapping;		//立方体贴图
};

}