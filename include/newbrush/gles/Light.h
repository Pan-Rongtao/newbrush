#pragma once
#include "newbrush/core/Def.h"
#include <glm/glm.hpp>

namespace nb{

struct DirectionalLight
{
public:
	glm::vec3	direction;		//方向
	glm::vec3	color;			//颜色
	glm::vec3	ambient;		//环境
	glm::vec3	diffuse;		//漫反射
	glm::vec3	specular;		//高光
	float		indensity;		//强度
};

struct PointLight
{
public:
	glm::vec3	position;		//位置
	glm::vec3	color;			//颜色
	glm::vec3	ambient;		//环境
	glm::vec3	diffuse;		//漫反射
	glm::vec3	specular;		//高光
	float		constant;		//衰减常数
	float		linear;			//一次项
	float		quadratic;		//二次项
	float		indensity;		//强度
};

struct SpotLight
{
	glm::vec3	position;		//位置
	glm::vec3	direction;		//方向
	glm::vec3	color;			//颜色
	glm::vec3	ambient;		//环境
	glm::vec3	diffuse;		//漫反射
	glm::vec3	specular;		//高光
	float		cutoff;			//切光角
	float		constant;		//衰减常数
	float		linear;			//一次项
	float		quadratic;		//二次项
	float		indensity;		//强度
};

}