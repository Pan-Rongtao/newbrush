#include "gles/Shader.h"
#include "core/Exception.h"
#include <GLES2/gl2.h>

using namespace nb::gl;

Shader::Shader()
: m_ShaderHandle(0)
{
}

Shader::~Shader()
{
	if(m_ShaderHandle != 0)
	{
		glDeleteShader(m_ShaderHandle);
		m_ShaderHandle = 0;
	}
}

Shader::Shader(const std::string &source)
: m_Source(source)
{
}

void Shader::setSource(const std::string &source)
{
	m_Source = source;
}

const std::string &Shader::source() const
{
	return m_Source;
}

void Shader::compile()
{
	const char *pSource = m_Source.data();
	glShaderSource(m_ShaderHandle, 1, &pSource, nullptr);
	glCompileShader(m_ShaderHandle);
	GLint nShaderStatus;
	glGetShaderiv(m_ShaderHandle, GL_COMPILE_STATUS, &nShaderStatus);
	if(!nShaderStatus)
	{
		GLint nLogLeng;
		glGetShaderiv(m_ShaderHandle, GL_INFO_LOG_LENGTH, &nLogLeng);

		char *pLog = new char[nLogLeng];
		glGetShaderInfoLog(m_ShaderHandle, nLogLeng, nullptr, pLog);
		std::string sLog = pLog;
		delete []pLog;

		NB_THROW_EXCEPTION((std::string("shader::compile fail, reason:") + sLog).data());
	}
}

bool Shader::hasCompiled() const
{
	GLint status;
	glGetShaderiv(handle(), GL_COMPILE_STATUS, &status);
	return status != 0;
}

unsigned int Shader::handle() const
{
	return m_ShaderHandle;
}

/////////////
VertexShader::VertexShader()
{
	m_ShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	if(m_ShaderHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create vertex shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}

VertexShader::VertexShader(const std::string &source)
: Shader(source)
{
	m_ShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	if(m_ShaderHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create vertex shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}

/////
FragmentShader::FragmentShader()
{
	m_ShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	if(m_ShaderHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create fragment shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}

FragmentShader::FragmentShader(const std::string &source)
: Shader(source)
{
	m_ShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	if(m_ShaderHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create fragment shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}
