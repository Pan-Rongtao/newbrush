/*******************************************************
**	Shader
**
**	着色器
**	
**		模型是Opengl可编程的片段，是运行于GPU的代码段。一般而言，
**	Shader分为顶点着色器VertexShader 和片元着色器FragmentShader。
**	Shader编译后需经过Program link才有意义
**
**		Shader（着色器基类）
**		VertexShader（顶点着色器）
**		FragmentShader（片元着色器）
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/model/Def.h"
#include <string>

namespace nb{

enum class ShaderTypeE
{
	Vertex,
	Fragment,
};

class NB_API Shader
{
public:
	Shader(ShaderTypeE type);
	Shader(ShaderTypeE type, const std::string &source);

	~Shader();
	Shader(const Shader &other) = delete;
	void operator =(const Shader &other) = delete;

	//设置源码
	void setSource(const std::string &source);

	//源码
	std::string &source();
	const std::string &source() const;

	//编译
	//异常：编译失败
	void compile();

	//是否已编译
	bool hasCompiled() const;

	//获取shader句柄
	uint32_t handle() const;

private:
	ShaderTypeE m_type;
	std::string m_source;
	uint32_t m_shaderHandle;
};

using ShaderPtr = std::shared_ptr<Shader>;
}
