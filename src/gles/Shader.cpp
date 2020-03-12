#include "newbrush/gles/Shader.h"
#include <GLES2/gl2.h>

using namespace nb;

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
	glShaderSource(m_shaderHandle, 1, &pSource, NULL);
	glCompileShader(m_shaderHandle);
	GLint nShaderStatus;
	glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &nShaderStatus);
	if(!nShaderStatus)
	{
		GLint nLogLen;
		glGetShaderiv(m_shaderHandle, GL_INFO_LOG_LENGTH, &nLogLen);

		char *pLog = new char[nLogLen];
		glGetShaderInfoLog(m_shaderHandle, nLogLen, nullptr, pLog);
		std::string sLog = pLog;
		delete []pLog;

		nbThrowException(std::runtime_error, "shader::compile fail, reason: %s", sLog.data());
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
	if (m_shaderHandle == 0)
		nbThrowException(std::logic_error, "glCreateShader fail, make sure has make current context. glGetError[%d]", glGetError());
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
		nbThrowException(std::logic_error, "glCreateShader fail, make sure has make current context. glGetError[%d]", glGetError());
}
