#pragma once
#include "../core/Def.h"
#include "../core/Vec3.h"

namespace nb{ namespace gl {

struct DirectionalLight
{
public:
	nb::core::Vec3	direction;		//方向
	nb::core::Vec3	color;			//颜色

	nb::core::Vec3	ambient;		//环境
	nb::core::Vec3	diffuse;		//漫反射
	nb::core::Vec3	specular;		//高光

	float			indensity;		//强度
};

struct PointLight
{
public:
	nb::core::Vec3	position;		//位置
	nb::core::Vec3	color;			//颜色

	nb::core::Vec3	ambient;		//环境
	nb::core::Vec3	diffuse;		//漫反射
	nb::core::Vec3	specular;		//高光

	float			constant;		//衰减常数
	float			linear;			//一次项
	float			quadratic;		//二次项

	float			indensity;		//强度
};

struct SpotLight
{
	nb::core::Vec3	position;		//位置
	nb::core::Vec3	direction;		//方向
	nb::core::Vec3	color;			//颜色

	nb::core::Vec3	ambient;		//环境
	nb::core::Vec3	diffuse;		//漫反射
	nb::core::Vec3	specular;		//高光

	float			cutoff;			//切光角
	float			constant;		//衰减常数
	float			linear;			//一次项
	float			quadratic;		//二次项

	float			indensity;		//强度
};

}}