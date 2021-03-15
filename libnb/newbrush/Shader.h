#pragma once
#include <string>
#include "newbrush/Object.h"
#include "glm/glm.hpp"

namespace nb
{

class NB_API Shader
{
public:
	Shader(const Shader &other) = delete;
	void operator =(const Shader &other) = delete;
	~Shader();

	//编译链接
	//异常：std::runtime_error
	void compileLink(const std::string &vsSource, const std::string &fsSource);

	int getAttributeLocation(const char *name) const;
	int getUniformLocation(const char *name) const;
	void bindAttributeLocation(uint32_t location, const char *name);

	uint32_t id();

	//激活/反激活
	void use();
	void disuse();

	//更新位置为location的attribute
	void vertexAttribute(int location, float v);
	void vertexAttribute(int location, const glm::vec2 &vec);
	void vertexAttribute(int location, const glm::vec3 &vec);
	void vertexAttribute(int location, const glm::vec4 &vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//更新位置为name的unform
	void setBool(const char *name, bool v);

	//float
	void setFloat(const char *name, float v);
	void setFloatArray(const char *name, const std::vector<float> &v);
	void setFloat2(const char *name, const glm::vec2 &v);
	void setFloat2Array(const char *name, const std::vector<glm::vec2> &v);
	void setFloat3(const char *name, const glm::vec3 &v);
	void setFloat3Array(const char *name, const std::vector<glm::vec3> &v);
	void setFloat4(const char *name, const glm::vec4 &v);
	void setFloat4Array(const char *name, const std::vector<glm::vec4> &v);

	//int
	void setInt(const char *name, int v);
	void setIntArray(const char *name, const std::vector<int> &v);
	void setIntArray(const char *name, int *v, int count);
	void setInt2(const char *name, const glm::ivec2 &vec);
	void setInt2Array(const char *name, const std::vector<glm::ivec2> &v);
	void setInt3(const char *name, const glm::ivec3 &vec);
	void setInt3Array(const char *name, const std::vector<glm::ivec3> &v);
	void setInt4(const char *name, const glm::ivec4 &vec);
	void setInt4Array(const char *name, const std::vector<glm::ivec4> &v);

	//mat
	void setMat2(const char *name, const glm::mat2 &v);
	void setMat2Array(const char *name, const std::vector<glm::mat2> &v);
	void setMat3(const char *name, const glm::mat3 &matrix);
	void setMat3Array(const char *name, const std::vector<glm::mat3> &v);
	void setMat4(const char *name, const glm::mat4 &matrix);
	void setMat4Array(const char *name, const std::vector<glm::mat4> &v);

private:
	Shader();

	uint32_t m_programHandle;
	friend class ShaderLibrary;
};

class NB_API ShaderLibrary
{
public:
	static ref<Shader> add(const std::string &name, const std::string &vsSource, const std::string &fsSource);
	static ref<Shader> addFromFile(const std::string &name, const std::string &filePath);
	static bool exists(const std::string &name);
	static ref<Shader> get(const std::string &name);

private:
	static void initSystemShader();
};

}
