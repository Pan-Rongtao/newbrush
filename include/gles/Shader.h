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
#include "../core/Def.h"
#include <string>

namespace nb{ namespace gl{

class NB_API Shader
{
public:
	//设置源码
	void setSource(const std::string &source);

	//获取源码
	const std::string &source() const;

	//编译
	//异常：编译失败
	void compile();

	//是否已编译
	bool hasCompiled() const;

	//获取shader句柄
	unsigned int handle() const;

	virtual ~Shader();

protected:
	Shader();
	Shader(const std::string &source);

	std::string			m_Source;
	unsigned int		m_ShaderHandle;
};

class NB_API VertexShader : public Shader
{
public:
	//构建一个顶点着色器，源码为空
	VertexShader();

	//构建一个顶点着色器，源码为sourceCode
	VertexShader(const std::string &source);

};

class NB_API FragmentShader : public Shader
{
public:
	FragmentShader();
	FragmentShader(const std::string &source);

};

}}
