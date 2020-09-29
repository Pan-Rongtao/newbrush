#pragma once
#include "newbrush/model/Program.h"
#include "newbrush/model/Camera.h"
#include "newbrush/model/Texture.h"
#include "newbrush/model/Color.h"

namespace nb {

class NB_API Material : public Object
{
	RTTR_ENABLE(Object)
public:
	void setName(const std::string &name);
	const std::string &name() const;

	//program
	void setProgram(ProgramPtr program);
	ProgramPtr program();

	//执行更新uniform的动作，在mesh渲染时调用
	virtual void uploadUniform(CameraPtr camera);

protected:
	Material() = default;
	Material(ProgramPtr program);

	std::string m_name;
	ProgramPtr m_program;
};

//////
class NB_API SolidColorMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	SolidColorMaterial();
	SolidColorMaterial(const Color &color);

	void setColor(const Color &color);
	const Color &color() const;

protected:
	virtual void uploadUniform(CameraPtr camera) override;

private:
	Color m_color;
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
	LinearGrandientMaterial(float height, const std::vector<GradientStop> &grandients);

	void setHeight(float height);
	float height() const;

	void setGrandients(const std::vector<GradientStop> &grandients);
	const std::vector<GradientStop> &grandients();

protected:
	virtual void uploadUniform(CameraPtr camera) override;

private:
	float m_height;
	std::vector<GradientStop> m_grandients;
};

//////
class NB_API ImageMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	ImageMaterial();
	ImageMaterial(const TexturePtr &texture);

	void setTexture(const TexturePtr &texture);
	const TexturePtr &texture() const;

protected:
	virtual void uploadUniform(CameraPtr camera) override;

private:
	TexturePtr m_texture;
};

/////////////////////////////
class NB_API PhongMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	PhongMaterial();

	virtual void uploadUniform(CameraPtr camera) override;
	
	//环境光影响因子
	void setAmbient(const Color &ambient);
	const Color &ambient() const;

	//漫反射光影响因子
	void setDiffuse(const Color &diffuse);
	const Color &diffuse() const;

	//镜面高光音影响因子
	void setSpecular(const Color &specular);
	const Color &specular() const;

	//自发光颜色
	void setEmission(const Color &emission);
	const Color &emission() const;

	//光照强度因子
	void setShineness(const float &shineness);
	const float &shineness() const;

	//漫反射贴图
	void setDiffuseMapping(TexturePtr diffuseMapping);
	TexturePtr diffuseMapping();

	//高光贴图
	void setSpecularMapping(TexturePtr specularMapping);
	TexturePtr specularMapping();

	//自发光贴图
	void setEmissionMapping(TexturePtr emissionMapping);
	TexturePtr emissionMapping();

private:
	Color m_ambient;
	Color m_diffuse;
	Color m_specular;
	Color m_emission;
	float m_shineness;

	TexturePtr m_diffuseMapping;
	TexturePtr m_specularMapping;
	TexturePtr m_emissionMapping;
};

class NB_API CubemapMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	CubemapMaterial();

	virtual void uploadUniform(CameraPtr camera) override;

	//环境光影响因子
	void setAmbient(const Color &ambient);
	const Color &ambient() const;

	//漫反射光影响因子
	void setDiffuse(const Color &diffuse);
	const Color &diffuse() const;

	//镜面高光音影响因子
	void setSpecular(const Color &specular);
	const Color &specular() const;

	//漫反射贴图
	void setDiffuseMapping(TexturePtr diffuseMapping);
	TexturePtr diffuseMapping();

	//立方体贴图
	void setCubeMapping(TexturePtr cubeMapping);
	TexturePtr cubeMapping();

private:
	Color m_ambient;
	Color m_diffuse;
	Color m_specular;

	TexturePtr m_diffuseMapping;
	TexturePtr m_cubeMapping;
};

/////////////////////////////
class NB_API VarMaterial : public Material
{
	RTTR_ENABLE(Material)
public:
	virtual void uploadUniform(CameraPtr camera) override;

	//存储uniform变量，以便下次上传数据使用
	template<class T>
	void storeUniform(const std::string &name, const T &v)
	{
		static_assert(
			std::is_same<T, bool>::value ||
			std::is_same<T, short>::value ||
			std::is_same<T, unsigned short>::value ||
			std::is_same<T, int>::value ||
			std::is_same<T, unsigned int>::value ||
			std::is_same<T, long>::value ||
			std::is_same<T, unsigned long>::value ||
			std::is_same<T, float>::value ||
			std::is_same<T, double>::value ||

			std::is_same<T, glm::vec2>::value ||
			std::is_same<T, glm::vec3>::value ||
			std::is_same<T, glm::vec4>::value ||
			std::is_same<T, glm::ivec2>::value ||
			std::is_same<T, glm::ivec3>::value ||
			std::is_same<T, glm::ivec4>::value ||
			std::is_same<T, glm::mat2x2>::value ||
			std::is_same<T, glm::mat3x3>::value ||
			std::is_same<T, glm::mat4x4>::value ||

			std::is_same<T, std::vector<float>>::value ||
			std::is_same<T, std::vector<glm::vec2>>::value ||
			std::is_same<T, std::vector<glm::vec3>>::value ||
			std::is_same<T, std::vector<glm::vec4>>::value ||
			std::is_same<T, std::vector<int>>::value ||
			std::is_same<T, std::vector<glm::ivec2>>::value ||
			std::is_same<T, std::vector<glm::ivec3>>::value ||
			std::is_same<T, std::vector<glm::ivec4>>::value ||
			std::is_same<T, std::vector<glm::mat2x2>>::value ||
			std::is_same<T, std::vector<glm::mat3x3>>::value ||
			std::is_same<T, std::vector<glm::mat4x4>>::value
			, "only support type[short, int, long, float, double, vec2, vec3, vec4, mat2x2, mat3x3, mat4x4 or their vector types].");

		if (name.empty())
		{
			nbThrowException(std::invalid_argument, "name is empty.");
		}
		m_uniforms[name] = v;
	}

private:
	std::map<std::string, var> m_uniforms;
};

using MaterialPtr = std::shared_ptr<Material>;
using PhongMaterialPtr = std::shared_ptr<PhongMaterial>;
using CubemapMaterialPtr = std::shared_ptr<CubemapMaterial>;
using VarMaterialPtr = std::shared_ptr<VarMaterial>;

}