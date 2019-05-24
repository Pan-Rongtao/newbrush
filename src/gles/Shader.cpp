#include "gles/Shader.h"
#include "core/Exception.h"
#include <GLES2/gl2.h>

using namespace nb::gl;

Shader::Shader()
	: m_shaderHandle(0)
{
}

Shader::~Shader()
{
	if (m_shaderHandle != 0)
		glDeleteShader(m_shaderHandle);
}

Shader::Shader(const std::string &source)
	: m_source(source)
	, m_shaderHandle(0)
{
}

void Shader::setSource(const std::string &source)
{
	m_source = source;
}

std::string &Shader::source()
{
	return m_source;
}

const std::string &Shader::source() const
{
	return m_source;
}

void Shader::compile()
{
	const char *pSource = m_source.data();
	glShaderSource(m_shaderHandle, 1, &pSource, nullptr);
	glCompileShader(m_shaderHandle);
	GLint nShaderStatus;
	glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &nShaderStatus);
	if(!nShaderStatus)
	{
		GLint nLogLeng;
		glGetShaderiv(m_shaderHandle, GL_INFO_LOG_LENGTH, &nLogLeng);

		char *pLog = new char[nLogLeng];
		glGetShaderInfoLog(m_shaderHandle, nLogLeng, nullptr, pLog);
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
	return m_shaderHandle;
}

/////////////
VertexShader::VertexShader()
	: VertexShader("")
{
}

VertexShader::VertexShader(const std::string &source)
	: Shader(source)
{
	m_shaderHandle = glCreateShader(GL_VERTEX_SHADER);
	if(m_shaderHandle == 0)
	{
		char info[100] = {0};
		snprintf(info, sizeof(info), "create vertex shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		throw nb::core::LogicException(__FILE__, __LINE__);
	}
}

/////
FragmentShader::FragmentShader()
	: FragmentShader("")
{
}

FragmentShader::FragmentShader(const std::string &source)
	: Shader(source)
{
	m_shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	if(m_shaderHandle == 0)
	{
		char info[100] = {0};
		snprintf(info, sizeof(info), "create fragment shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}
