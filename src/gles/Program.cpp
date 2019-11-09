#include "gles/Program.h"
#include "gles/Shader.h"
#include <GLES2/gl2.h>
#include <cstring>
#include <glm/gtc/type_ptr.hpp>

using namespace nb::gl;

Program::Program()
	: Program(nullptr, nullptr)
{
}

Program::Program(std::shared_ptr<VertexShader> verShader, std::shared_ptr<FragmentShader> fragShader)
	: m_vertexShader(verShader)
	, m_fragmentShader(fragShader)
	, m_programHandle(0)
{
	m_programHandle = glCreateProgram();
	if (m_programHandle == 0)
		nbThrowException(std::runtime_error, "glCreateProgram fail, glGetError[%d]", glGetError());
}

Program::~Program()
{
	if(m_programHandle != 0)
	{
		glDeleteProgram(m_programHandle);
		m_programHandle = 0;
	}
}

void Program::setVertexShader(std::shared_ptr<VertexShader> verShader)
{
	m_vertexShader = verShader;
}

std::shared_ptr<VertexShader> Program::vertexShader()
{
	return m_vertexShader;
}

void Program::setFragmentShader(std::shared_ptr<FragmentShader> fragShader)
{
	m_fragmentShader = fragShader;
}

std::shared_ptr<FragmentShader> Program::fragmentShader()
{
	return m_fragmentShader;
}

void Program::link()
{
	glAttachShader(m_programHandle, m_vertexShader->handle());
	glAttachShader(m_programHandle, m_fragmentShader->handle());
	glLinkProgram(m_programHandle);
	int nLinkStatus;
	glGetProgramiv(m_programHandle, GL_LINK_STATUS, &nLinkStatus);
	if(nLinkStatus == 0)
	{
		GLint nLogLen;
		glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &nLogLen);

		char *pLog = new char[nLogLen];
		glGetProgramInfoLog(m_programHandle, nLogLen, nullptr, pLog);
		std::string sLog = pLog;
		delete []pLog;
		nbThrowException(std::runtime_error, "program link fail, reason: %s", sLog.data());
	}
}

int Program::getAttributeLocation(const char *name) const
{
	return glGetAttribLocation(m_programHandle, name);
}

int Program::getUniformLocation(const char *name) const
{
	return glGetUniformLocation(m_programHandle, name);
}

void Program::bindAttributeLocation(unsigned int location, const char *name)
{
	glBindAttribLocation(m_programHandle, location, name);
}

void Program::use()
{
	glUseProgram(m_programHandle);
}

void Program::disuse()
{
	glUseProgram(0);
}

void Program::vertexAttribute(int location, float v)
{
	glVertexAttrib1f(location, v);
}

void Program::vertexAttribute(int location, const glm::vec2 &vec)
{
	glVertexAttrib2f(location, vec.x, vec.y);
}

void Program::vertexAttribute(int location, const glm::vec3 &vec)
{
	glVertexAttrib3f(location, vec.x, vec.y, vec.z);
}

void Program::vertexAttribute(int location, const glm::vec4 &vec)
{
	glVertexAttrib4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Program::vertexAttributePointer(int location, int dimension, int stride, const void *data)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, dimension, GL_FLOAT, GL_FALSE, stride, data);
}

void Program::uniform(int location, float v)
{
	glUniform1f(location, v);
}

void Program::uniform(int location, const std::vector<float> &v)
{
	glUniform1fv(location, (GLsizei)v.size(), v.empty() ? nullptr : v.data());
}

void Program::uniform(int location, const glm::vec2 &vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void Program::uniform(int location, const std::vector<glm::vec2> &v)
{
	glUniform2fv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::vec3 &vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Program::uniform(int location, const std::vector<glm::vec3> &v)
{
	glUniform3fv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::vec4 &vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Program::uniform(int location, const std::vector<glm::vec4> &v)
{
	glUniform4fv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, int v)
{
	glUniform1i(location, v);
}

void Program::uniform(int location, const std::vector<int> &v)
{
	glUniform1iv(location, (GLsizei)v.size(), v.empty() ? nullptr : v.data());
}

void Program::uniform(int location, const glm::ivec2 &vec)
{
	glUniform2i(location, vec.x, vec.y);
}

void Program::uniform(int location, const std::vector<glm::ivec2> &v)
{
	glUniform2iv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::ivec3 &vec)
{
	glUniform3i(location, vec.x, vec.y, vec.z);
}

void Program::uniform(int location, const std::vector<glm::ivec3> &v)
{
	glUniform3iv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::ivec4 &vec)
{
	glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
}

void Program::uniform(int location, const std::vector<glm::ivec4> &v)
{
	glUniform4iv(location, (GLsizei)v.size(), v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::mat2x2 &matrix)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::uniform(int location, const std::vector<glm::mat2x2> &v)
{
	glUniformMatrix2fv(location, (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::mat3x3 &matrix)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::uniform(int location, const std::vector<glm::mat3x3> &v)
{
	glUniformMatrix3fv(location, (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

void Program::uniform(int location, const glm::mat4x4 &matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::uniform(int location, const std::vector<glm::mat4x4> &v)
{
	glUniformMatrix4fv(location, (GLsizei)v.size(), GL_FALSE, v.empty() ? nullptr : glm::value_ptr(v[0]));
}

////////////////programs

std::shared_ptr<Program> Programs::primitive()
{
	static std::shared_ptr<Program> p;
	if (p)	return p;

	constexpr char vs[] =
		"attribute vec4 nbPos;"
		"attribute vec4 nbColor;"
		"attribute vec2 nbTexCoord;"
		"uniform mat4 nbMvp;"
		"varying vec4 _color;"
		"varying vec2 _texCoord;"
		"void main()"
		"{"
		"	_color = nbColor;"
		"	_texCoord = nbTexCoord;"
		"	gl_Position = nbMvp * nbPos;"
		"}";
	constexpr char fs[] =
		"uniform bool nbColorMode;"
		"varying vec4 _color;"
		"varying vec2 _texCoord;"
		"uniform sampler2D sampler;"
		"void main()"
		"{"
		"	if(nbColorMode)"
		"		gl_FragColor = _color;"
		"	else"
		"		gl_FragColor = texture2D(sampler, _texCoord);"
		"}";
	p = compileBindLink(vs, fs);
	return p;
}

std::shared_ptr<Program> Programs::gradientPrimitive()
{
	static std::shared_ptr<Program> p;
	if (p)	return p;

	constexpr char vs[] =
		"attribute vec4 nbPos;"
		"uniform mat4 nbMvp;"
		"void main()"
		"{"
		"	gl_Position = nbMvp * nbPos;"
		"}";
	constexpr char fs[] =
		"uniform int size;"
		"uniform vec4 colors[100];"
		"uniform float offsets[100];"
		"void main()"
		"{"
		"	vec2 u_resolution = vec2(400, 400);"
		"	float y = gl_FragCoord.y / u_resolution.y;"
		"	vec4 color = mix(colors[0], colors[1], smoothstep(offsets[0], offsets[1], y));"
		"	for(int i = 2; i < size; ++i)"
		"		color = mix(color, colors[i], smoothstep(offsets[i-1], offsets[i], y));"
		"	gl_FragColor = color;"
		"}";
	p = compileBindLink(vs, fs);
	return p;
}

std::shared_ptr<Program> Programs::phong()
{
	static std::shared_ptr<Program> p;
	if (p)	return p;

	constexpr char vs[] =
		"attribute vec4	nbPos;"
		"attribute vec2	nbTexCoord;"
		"attribute vec3	nbNormal;"
		"uniform mat4 nbMvp;"
		"uniform mat4 nbM;"
		"uniform mat4 nbV;"
		"uniform mat4 nbP;"
		"varying vec2 _texCoord;"
		"varying vec3 _normal;"
		"varying vec3 _fragPos;"
		"void main()"
		"{"
		"	gl_Position = nbMvp * nbPos; "
		"	_texCoord = nbTexCoord;"
		"	_normal = mat3(nbM) * nbNormal;"
		"	_fragPos = vec3(nbM * nbPos);"
		"}";
	constexpr char fs[] =
		"struct Material"
		"{"
		"	sampler2D base;"
		"	float shininess;"
		"};"
		"struct Light"
		"{"
		"	vec3 direction;"
		"	vec3 ambient;"
		"	vec3 diffuse;"
		"	vec3 specular;"
		"};"
		"varying vec2 _texCoord;"
		"varying vec3 _normal;"
		"varying vec3 _fragPos;"
		"uniform vec3 viewPos;"
		"uniform Material material;"
		"uniform Light light;"
		"void main()"
		"{"
		"	vec3 ambient = light.ambient;"
		"	vec3 norm = normalize(_normal);"
		"	vec3 lightDir = normalize(light.direction);"
		"	float diffFactor = max(dot(norm, lightDir), 0.0);"
		"	vec3 diffuse = light.diffuse * diffFactor;"
		"	vec3 viewDir = normalize(viewPos - _fragPos);"
		"	vec3 reflectDir = normalize(reflect(lightDir, norm));"
		"	float specFactor = pow(max(dot(norm, normalize(viewDir + lightDir)), 0.0), material.shininess);"
		"	vec3 specular = light.specular * specFactor;"
		"	vec3 baseColor = vec3(1.0f, 0.5f, 0.31f);"
		"	gl_FragColor = vec4((ambient + diffuse + specular) * baseColor, 1.0f);"
		"}";
	p = compileBindLink(vs, fs);
	return p;
}

std::shared_ptr<Program> Programs::cube()
{
	static std::shared_ptr<Program> p;
	if (p)	return p;

	constexpr char vs[] =
		"attribute vec4 nbPos;"
		"uniform mat4 nbMvp;"
		"varying vec3 _texCoord;"
		"void main()"
		"{"
		"	gl_Position = nbMvp * nbPos;"
		"	_texCoord = -nbPos.xyz;"
		"}";
	constexpr char fs[] =
		"varying vec3 _texCoord;"
		"uniform samplerCube sampler;"
		"void main()"
		"{"
		"	gl_FragColor = textureCube(sampler, _texCoord);"
		"}";
	p = compileBindLink(vs, fs);
	return p;
}

std::shared_ptr<Program> Programs::glpy()
{
	static std::shared_ptr<Program> p;
	if (p) return p;

	constexpr char vs[] =
		"attribute vec4 nbPos;"
		"attribute vec2 nbTexCoord;"
		"uniform mat4 nbMvp;"
		"varying vec2 _texCoord;"
		"void main()"
		"{"
		"	_texCoord = nbTexCoord;"
		"	gl_Position = nbMvp * nbPos;"
		"}";
	constexpr char fs[] =
		"varying vec2 _texCoord;"
		"uniform vec4 fontColor;"
		"uniform sampler2D sampler;"
		"void main()"
		"{"
		"	vec4 color = texture2D(sampler, _texCoord);"
		"	gl_FragColor = color.w * fontColor;"
		"}";
	p = compileBindLink(vs, fs);
	return p;
}

std::shared_ptr<Program> Programs::compileBindLink(const std::string &vs, const std::string &fs)
{
	auto p = std::make_shared<Program>(std::make_shared<VertexShader>(vs), std::make_shared<FragmentShader>(fs));
	p->vertexShader()->compile();
	p->fragmentShader()->compile();
	//必须在link之前绑定
	p->bindAttributeLocation(Program::nbPositionLocation, Program::nbPositionLocationStr);
	p->bindAttributeLocation(Program::nbColorLocation, Program::nbColorLocationStr);
	p->bindAttributeLocation(Program::nbTexCoordLocaltion, Program::nbTexCoordLocaltionStr);
	p->bindAttributeLocation(Program::nbNormalLocation, Program::nbNormalLocationStr);
	p->link();
	return p;
}
