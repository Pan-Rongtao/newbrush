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
#include "system/String.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Shader
{
public:
	//设置源码
	void SetSourceCode(const nb::System::String &sourceCode);

	//获取源码
	nb::System::String GetSourceCode() const;

	//编译
	//异常：编译失败
	void Compile();

	//是否已编译
	bool HasCompiled() const;

	//获取shader句柄
	unsigned int GetShaderHandle() const;

	//是否相同
	bool Equal(Shader *shader) const;

	virtual ~Shader();

protected:
	Shader();
	Shader(const nb::System::String &sourceCode);

	nb::System::String	m_SourceCode;
	unsigned int		m_ShaderHandle;
};

class NB_EXPORT VertexShader : public Shader
{
public:
	//构建一个顶点着色器，源码为空
	VertexShader();

	//构建一个顶点着色器，源码为sourceCode
	VertexShader(const nb::System::String &sourceCode);

public:
	//通用顶点着色器
	static VertexShader *Common();
};

class NB_EXPORT FragmentShader : public Shader
{
public:
	FragmentShader();
	FragmentShader(const nb::System::String &sourceCode);

public:
	//通用片元着色器
	static FragmentShader *Common();
};

}}}
