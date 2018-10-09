#include "gles/Program.h"
#include "core/Exception.h"
#include "gles/Shader.h"
#include <GLES2/gl2.h>
#include <cstring>

using namespace nb::core;
using namespace nb::gl;

Program::Program()
: m_ProgramHandle(0)
{
	m_ProgramHandle = glCreateProgram();
	if(m_ProgramHandle == 0)
		NB_THROW_EXCEPTION("create shader program fail.");
}

Program::Program(std::shared_ptr<VertexShader> verShader, std::shared_ptr<FragmentShader> fragShader)
: m_VertexShader(verShader)
, m_FragmentShader(fragShader)
, m_ProgramHandle(0)
{
	m_ProgramHandle = glCreateProgram();
	if(m_ProgramHandle == 0)
		NB_THROW_EXCEPTION("create shader program fail.");
}

Program::~Program()
{
	if(m_ProgramHandle != 0)
	{
		glDeleteProgram(m_ProgramHandle);
		m_ProgramHandle = 0;
	}
}

void Program::setVertexShader(std::shared_ptr<VertexShader> verShader)
{
	m_VertexShader = verShader;
}

std::shared_ptr<VertexShader> Program::vertexShader()
{
	return m_VertexShader;
}

void Program::setFragmentShader(std::shared_ptr<FragmentShader> fragShader)
{
	m_FragmentShader = fragShader;
}

std::shared_ptr<FragmentShader> Program::fragmentShader()
{
	return m_FragmentShader;
}

void Program::link()
{
	glAttachShader(m_ProgramHandle, m_VertexShader->handle());
	glAttachShader(m_ProgramHandle, m_FragmentShader->handle());
	glLinkProgram(m_ProgramHandle);
	int nLinkStatus;
	glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &nLinkStatus);
	if(nLinkStatus == 0)
	{
		GLint nLogLeng;
		glGetProgramiv(m_ProgramHandle, GL_INFO_LOG_LENGTH, &nLogLeng);

		char *pLog = new char[nLogLeng];
		glGetProgramInfoLog(m_ProgramHandle, nLogLeng, nullptr, pLog);
		std::string sLog = pLog;
		delete []pLog;
		NB_THROW_EXCEPTION((std::string("program::link fail, reason:") + sLog).data());
	}
}

int Program::getAttributeLocation(const char *name) const
{
	return glGetAttribLocation(m_ProgramHandle, name);
}

int Program::getUniformLocation(const char *name) const
{
	return glGetUniformLocation(m_ProgramHandle, name);
}

void Program::bindAttributeLocation(unsigned int location, const char *name)
{
	glBindAttribLocation(m_ProgramHandle, location, name);
}

void Program::use()
{
	glUseProgram(m_ProgramHandle);
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

void Program::uniformDefault()
{
	SourceDecoder decoder;
	decoder.decode(m_VertexShader->source(), m_FragmentShader->source());
	std::map<std::string, size_t> uniforms;
	decoder.getUniforms(uniforms);
	for (auto iter = uniforms.begin(); iter != uniforms.end(); ++iter)
	{
		int location = getUniformLocation(iter->first.data());
		size_t hash = iter->second;
		if (hash == typeid(int).hash_code())
		{
			uniform(location, 1);
		}
		else if (hash == typeid(float).hash_code())
		{
			uniform(location, 1.0f);
		}
		else if (hash == typeid(nb::core::Vec2).hash_code())
		{
			uniform(location, Vec2(1.0f, 1.0f));
		}
		else if (hash == typeid(nb::core::Vec3).hash_code())
		{
			uniform(location, Vec3(1.0f, 1.0f, 1.0f));
		}
		else if (hash == typeid(nb::core::Vec4).hash_code())
		{
			uniform(location, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (hash == typeid(nb::core::Matrix2x2).hash_code())
		{
			uniform(location, Matrix2x2::identity());
		}
		else if (hash == typeid(nb::core::Matrix3x3).hash_code())
		{
			uniform(location, Matrix3x3::identity());
		}
		else if (hash == typeid(nb::core::Matrix4x4).hash_code())
		{
			uniform(location, Matrix4x4::identity());
		}
	}
}
