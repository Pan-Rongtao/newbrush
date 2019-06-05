#include "gles/Program.h"
#include "gles/Shader.h"
#include <GLES2/gl2.h>
#include <cstring>

using namespace nb::core;
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
		NB_THROW_EXCEPTION(std::runtime_error, "glCreateProgram fail, glGetError[%d]", glGetError());
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
		NB_THROW_EXCEPTION(std::runtime_error, "program link fail, reason: %s", sLog.data());
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

void Program::vertexAttribute(int location, const Vec2 &vec)
{
	glVertexAttrib2f(location, vec.x(), vec.y());
}

void Program::vertexAttribute(int location, const Vec3 &vec)
{
	glVertexAttrib3f(location, vec.x(), vec.y(), vec.z());
}

void Program::vertexAttribute(int location, const Vec4 &vec)
{
	glVertexAttrib4f(location, vec.x(), vec.y(), vec.z(), vec.w());
}

void Program::vertexAttribute(int location, Vec2 *vec)
{
//	glVertexAttrib2fv(location, data);
}

void Program::vertexAttribute(int location, Vec3 *vec)
{
//
}

void Program::vertexAttribute(int location, Vec4 *vec)
{
//
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

void Program::uniform(int location, float *v, int count)
{
	glUniform1fv(location, count, v);
}

void Program::uniform(int location, const Vec2 &vec)
{
	glUniform2f(location, vec.x(), vec.y());
}

void Program::uniform(int location, Vec2 *vec, int count)
{
	int dimension = vec->dimension();
	float *data = new float[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), &(vec->at(0)), dimension * sizeof(float));
	glUniform2fv(location, count, data);
	delete []data;
}

void Program::uniform(int location, const Vec3 &vec)
{
	glUniform3f(location, vec.x(), vec.y(), vec.z());
}

void Program::uniform(int location, Vec3 *vec, int count)
{
	int dimension = vec->dimension();
	float *data = new float[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), &(vec->at(0)), dimension * sizeof(float));
	glUniform3fv(location, count, data);
	delete []data;
}

void Program::uniform(int location, const Vec4 &vec)
{
	glUniform4f(location, vec.x(), vec.y(), vec.z(), vec.w());
}

void Program::uniform(int location, Vec4 *vec, int count)
{
	int dimension = vec->dimension();
	float *data = new float[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), &(vec->at(0)), dimension * sizeof(float));
	glUniform4fv(location, count, data);
	delete []data;
}

void Program::uniform(int location, int v)
{
	glUniform1i(location, v);
}

void Program::uniform(int location, int *v, int count)
{
	glUniform1iv(location, count, v);
}

void Program::uniform(int location, const Vec2I &vec)
{
	glUniform2i(location, vec.x(), vec.y());
}

void Program::uniform(int location, Vec2I *vec, int count)
{
	int dimension = vec->dimension();
	int *data = new int[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].data(), dimension * sizeof(float));
	glUniform2iv(location, count, data);
	delete []data;
}

void Program::uniform(int location, const Vec3I &vec)
{
	glUniform3i(location, vec.x(), vec.y(), vec.z());
}

void Program::uniform(int location, Vec3I *vec, int count)
{
	int dimension = vec->dimension();
	int *data = new int[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].data(), dimension * sizeof(float));
	glUniform3iv(location, count, data);
	delete []data;
}

void Program::uniform(int location, const Vec4I &vec)
{
	glUniform4i(location, vec.x(), vec.y(), vec.z(), vec.w());
}

void Program::uniform(int location, Vec4I *vec, int count)
{
	int dimension = vec->dimension();
	int *data = new int[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].data(), dimension * sizeof(float));
	glUniform4iv(location, count, data);
	delete []data;
}

void Program::uniform(int location, const Matrix2x2 &matrix)
{
	int n = matrix.column() * matrix.row();
	float *data = new float[n];
	memcpy(data, matrix.data(), n * sizeof(float));
	glUniformMatrix2fv(location, 1, GL_FALSE, data);
	delete []data;
}

void Program::uniform(int location, Matrix2x2 *matrix, int count)
{
	int n = matrix->column() * matrix->row();
	float *data = new float[n * count];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * n * sizeof(float), matrix[i].data(), n * sizeof(float));
	glUniformMatrix2fv(location, count, GL_FALSE, data);
	delete []data;
}

void Program::uniform(int location, const Matrix3x3 &matrix)
{
	int n = matrix.column() * matrix.row();
	float *data = new float[n];
	memcpy(data, matrix.data(), n * sizeof(float));
	glUniformMatrix3fv(location, 1, GL_FALSE, data);
	delete []data;
}

void Program::uniform(int location, Matrix3x3 *matrix, int count)
{
	int n = matrix->column() * matrix->row();
	float *data = new float[n * count];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * n * sizeof(float), matrix[i].data(), n * sizeof(float));
	glUniformMatrix3fv(location, count, GL_FALSE, data);
	delete []data;
}

void Program::uniform(int location, const Matrix4x4 &matrix)
{
	int n = matrix.column() * matrix.row();
	float *data = new float[n];
	memcpy(data, matrix.data(), n * sizeof(float));
	glUniformMatrix4fv(location, 1, GL_FALSE, data);
	delete []data;
}

void Program::uniform(int location, Matrix4x4 *matrix, int count)
{
	int n = matrix->column() * matrix->row();
	float *data = new float[n * count];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * n * sizeof(float), matrix[i].data(), n * sizeof(float));
	glUniformMatrix4fv(location, count, GL_FALSE, data);
	delete []data;
}

////////////////programs
std::shared_ptr<Program> Programs::primitive()
{
	static std::shared_ptr<Program> p;
	if (p)
		return p;

	auto verShader = std::make_shared<VertexShader>
		("\
		attribute	vec4	nb_Position;\
		attribute	vec4	nb_Color;\
		attribute	vec2	nb_TextCoord;\
		uniform		mat4	nb_Mvp;\
		varying		vec4	vary_color;\
		varying		vec2	vary_textureCoord;\
		\
		void main()\
		{\
			vary_color = nb_Color;\
			vary_textureCoord = nb_TextCoord;\
			gl_Position = nb_Mvp * nb_Position;\
		}\
	");
	auto fragShader = std::make_shared<FragmentShader>
		("\
		uniform		bool		unif_colorMode;\
		varying		vec4		vary_color;\
		varying		vec2		vary_textureCoord;\
		uniform		sampler2D	unif_sampler;\
		\
		void main()\
		{\
			if(unif_colorMode)\
				gl_FragColor = vary_color;\
			else\
				gl_FragColor = texture2D(unif_sampler, vary_textureCoord);\
		}\
	");
	verShader->compile();
	fragShader->compile();
	p = std::make_shared<Program>(verShader, fragShader);
	//必须在link之前绑定
	p->bindAttributeLocation(Program::positionLocation, "nb_Position");
	p->bindAttributeLocation(Program::colorLocation, "nb_Color");
	p->bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	p->bindAttributeLocation(Program::normalLocation, "nb_Normal");
	p->link();
	return p;
}

std::shared_ptr<Program> nb::gl::Programs::phong()
{
	static std::shared_ptr<Program> p;
	if (p)
		return p;

	auto verShader = std::make_shared<VertexShader>
		("\
		attribute	vec4	nb_Position;\
		attribute	vec2	nb_TextCoord;\
		attribute	vec3	nb_Normal;\
		uniform		mat4	nb_Mvp;\
		uniform		mat4	nb_M;\
		uniform		mat4	nb_V;\
		uniform		mat4	nb_P;\
		\
		varying		vec2	vTextureCoord;\
		varying		vec3	vNormal;\
		varying		vec3	vFragPos;\
		\
		void main()\
		{\
			gl_Position = nb_Mvp * nb_Position;\
			vTextureCoord = nb_TextCoord;\
			vNormal = mat3(nb_M)*nb_Normal;\
			vFragPos = vec3(nb_M * nb_Position);\
		}\
	");
	auto fragShader = std::make_shared<FragmentShader>
		("\
		struct Material {\
			sampler2D base;\
			float	shininess;\
		};\
		struct Light {\
			vec3	direction;\
			vec3	ambient;\
			vec3	diffuse;\
			vec3	specular;\
		};\
		varying		vec2	vTextureCoord;\
		varying		vec3	vNormal;\
		varying		vec3	vFragPos;\
		\
		uniform		vec3	viewPos;\
		uniform		Material	material;\
		uniform		Light	light;\
		\
		void main()\
		{\
			vec3 ambient = light.ambient;\
			\
			vec3 norm = normalize(vNormal);\
			vec3 lightDir = normalize(light.direction);\
			float diffFactor = max(dot(norm, lightDir), 0.0);\
			vec3 diffuse = light.diffuse * diffFactor;\
			\
			vec3 viewDir = normalize(viewPos - vFragPos);\
			vec3 reflectDir = normalize(reflect(lightDir, norm));\
			float specFactor = pow(max(dot(norm, normalize(viewDir+lightDir)), 0.0), material.shininess);\
			vec3 specular = light.specular * specFactor;\
			\
			vec3 baseColor = vec3(1.0f, 0.5f, 0.31f);\
			gl_FragColor = vec4((ambient + diffuse + specular) * baseColor, 1.0f);\
		}\
	");
	verShader->compile();
	fragShader->compile();
	//必须在link之前绑定
	p = std::make_shared<Program>(verShader, fragShader);
	p->bindAttributeLocation(Program::positionLocation, "nb_Position");
	p->bindAttributeLocation(Program::colorLocation, "nb_Color");
	p->bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	p->bindAttributeLocation(Program::normalLocation, "nb_Normal");
	p->link();
	return p;
}

std::shared_ptr<Program> nb::gl::Programs::cube()
{
	static std::shared_ptr<Program> p;
	if (p)
		return p;

	std::shared_ptr<VertexShader> verShader = std::make_shared<VertexShader>
		("\
		attribute	vec4	nb_Position;\
		uniform		mat4	nb_Mvp;\
		varying		vec3	vary_textureCoord;\
		\
		void main()\
		{\
			gl_Position = nb_Mvp * nb_Position;\
			vary_textureCoord = -nb_Position.xyz;\
		}\
	");
	std::shared_ptr<FragmentShader> fragShader = std::make_shared<FragmentShader>
		("\
		varying		vec3		vary_textureCoord;\
		uniform		samplerCube	unif_sampler;\
		\
		void main()\
		{\
			gl_FragColor = textureCube(unif_sampler, vary_textureCoord);\
		}\
	");
	verShader->compile();
	fragShader->compile();
	p = std::make_shared<Program>(verShader, fragShader);
	//必须在link之前绑定
	p->bindAttributeLocation(Program::positionLocation, "nb_Position");
	p->bindAttributeLocation(Program::colorLocation, "nb_Color");
	p->bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	p->bindAttributeLocation(Program::normalLocation, "nb_Normal");
	p->link();
	return p;
}

std::shared_ptr<Program> Programs::glpy()
{
	static std::shared_ptr<Program> p;
	if (p)
		return p;

	auto verShader = std::make_shared<VertexShader>
		("\
		attribute	vec4	nb_Position;\
		attribute	vec4	nb_Color;\
		attribute	vec2	nb_TextCoord;\
		uniform		mat4	nb_Mvp;\
		varying		vec4	vary_color;\
		varying		vec2	vary_textureCoord;\
		\
		void main()\
		{\
			vary_color = nb_Color;\
			vary_textureCoord = nb_TextCoord;\
			gl_Position = nb_Mvp * nb_Position;\
		}\
	");
	auto fragShader = std::make_shared<FragmentShader>
		("\
		varying		vec4		vary_color;\
		varying		vec2		vary_textureCoord;\
		uniform		sampler2D	unif_sampler;\
		\
		void main()\
		{\
			vec4 color = texture2D(unif_sampler, vary_textureCoord);\
			gl_FragColor = color.w * vary_color;\
		}\
	");
	verShader->compile();
	fragShader->compile();
	p = std::make_shared<Program>(verShader, fragShader);
	//必须在link之前绑定
	p->bindAttributeLocation(Program::positionLocation, "nb_Position");
	p->bindAttributeLocation(Program::colorLocation, "nb_Color");
	p->bindAttributeLocation(Program::texCoordLocaltion, "nb_TextCoord");
	p->bindAttributeLocation(Program::normalLocation, "nb_Normal");
	p->link();
	return p;
}
