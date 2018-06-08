#include "gles/Program.h"
#include "core/Exception.h"
#include "gles/Shader.h"
#include "system/String.h"
#include <GLES2/gl2.h>

using nb::System::String;
using nb::Math::Vec2;
using nb::Math::Vec2I;
using nb::Math::Vec3;
using nb::Math::Vec3I;
using nb::Math::Vec4;
using nb::Math::Vec4I;
using nb::Math::Matrix2x2;
using nb::Math::Matrix3x3;
using nb::Math::Matrix4x4;
using nb::gl::Gles::Program;
using nb::gl::Gles::VertexShader;
using nb::gl::Gles::FragmentShader;

Program::Program()
: m_VertexShader(NULL)
, m_FragmentShader(NULL)
, m_ProgramHandle(0)
{
	m_ProgramHandle = glCreateProgram();
	if(m_ProgramHandle == 0)
		NB_THROW_EXCEPTION("create shader program fail.");
}

Program::Program(VertexShader *verShader, FragmentShader *fragShader)
: m_VertexShader(verShader)
, m_FragmentShader(fragShader)
, m_ProgramHandle(0)
{
	m_ProgramHandle = glCreateProgram();
	if(m_ProgramHandle == 0)
		NB_THROW_EXCEPTION("create shader program fail.");

	m_VertexShader->Compile();
	m_FragmentShader->Compile();
}

Program::~Program()
{
	if(m_ProgramHandle != 0)
	{
		glDeleteProgram(m_ProgramHandle);
		m_ProgramHandle = 0;
	}
}

void Program::SetVertexShader(VertexShader *verShader)
{
	m_VertexShader = verShader;
	m_VertexShader->Compile();
}

void Program::SetFragmentShader(FragmentShader *fragShader)
{
	m_FragmentShader = fragShader;
	m_FragmentShader->Compile();
}

void Program::SetShader(VertexShader *verShader, FragmentShader *fragShader)
{
	SetVertexShader(verShader);
	SetFragmentShader(fragShader);
}

void Program::Link()
{
	glAttachShader(m_ProgramHandle, m_VertexShader->GetShaderHandle());
	glAttachShader(m_ProgramHandle, m_FragmentShader->GetShaderHandle());
	glLinkProgram(m_ProgramHandle);
	int nLinkStatus;
	glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &nLinkStatus);
	if(nLinkStatus == 0)
	{
		GLint nLogLeng;
		glGetProgramiv(m_ProgramHandle, GL_INFO_LOG_LENGTH, &nLogLeng);

		char *pLog = new char[nLogLeng];
		glGetProgramInfoLog(m_ProgramHandle, nLogLeng, NULL, pLog);
		std::string sLog = pLog;
		delete []pLog;
		NB_THROW_EXCEPTION((std::string("program::link fail, reason:") + sLog).data());
	}
}

int Program::GetAttributeLocation(const char *name) const
{
	return glGetAttribLocation(m_ProgramHandle, name);
}

int Program::GetUniformLocation(const char *name) const
{
	return glGetUniformLocation(m_ProgramHandle, name);
}

void Program::Use()
{
	glUseProgram(m_ProgramHandle);
}

void Program::UnUse()
{
	glUseProgram(0);
}

bool Program::Equal(Program *program) const
{
	return m_VertexShader->Equal(program->m_VertexShader) && m_FragmentShader->Equal(program->m_FragmentShader);
}

void Program::VertexAttribute(int location, float v)
{
	glVertexAttrib1f(location, v);
}

void Program::VertexAttribute(int location, const nb::Math::Vec2 &vec)
{
	glVertexAttrib2f(location, vec.X(), vec.Y());
}

void Program::VertexAttribute(int location, const nb::Math::Vec3 &vec)
{
	glVertexAttrib3f(location, vec.X(), vec.Y(), vec.Z());
}

void Program::VertexAttribute(int location, const nb::Math::Vec4 &vec)
{
	glVertexAttrib4f(location, vec.X(), vec.Y(), vec.Z(), vec.W());
}

void Program::VertexAttribute(int location, nb::Math::Vec2 *vec)
{
//	glVertexAttrib2fv(location, data);
}

void Program::VertexAttribute(int location, nb::Math::Vec3 *vec)
{
//
}

void Program::VertexAttribute(int location, nb::Math::Vec4 *vec)
{
//
}

void Program::VertexAttributePointer(int location, int dimension, int stride, const void *data)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, dimension, GL_FLOAT, GL_FALSE, stride, data);
}

void Program::Uniform(int location, float v)
{
	glUniform1f(location, v);
}

void Program::Uniform(int location, float *v, int count)
{
	glUniform1fv(location, count, v);
}

void Program::Uniform(int location, const Vec2 &vec)
{
	glUniform2f(location, vec.X(), vec.Y());
}

void Program::Uniform(int location, Vec2 *vec, int count)
{
	int dimension = vec->GetDimension();
	float *data = new float[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].GetData(), dimension * sizeof(float));
	glUniform2fv(location, count, data);
	delete []data;
}

void Program::Uniform(int location, const Vec3 &vec)
{
	glUniform3f(location, vec.X(), vec.Y(), vec.Z());
}

void Program::Uniform(int location, Vec3 *vec, int count)
{
	int dimension = vec->GetDimension();
	float *data = new float[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].GetData(), dimension * sizeof(float));
	glUniform3fv(location, count, data);
	delete []data;
}

void Program::Uniform(int location, const Vec4 &vec)
{
	glUniform4f(location, vec.X(), vec.Y(), vec.Z(), vec.W());
}

void Program::Uniform(int location, Vec4 *vec, int count)
{
	int dimension = vec->GetDimension();
	float *data = new float[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].GetData(), dimension * sizeof(float));
	glUniform4fv(location, count, data);
	delete []data;
}

void Program::Uniform(int location, int v)
{
	glUniform1i(location, v);
}

void Program::Uniform(int location, int *v, int count)
{
	glUniform1iv(location, count, v);
}

void Program::Uniform(int location, const Vec2I &vec)
{
	glUniform2i(location, vec.X(), vec.Y());
}

void Program::Uniform(int location, Vec2I *vec, int count)
{
	int dimension = vec->GetDimension();
	int *data = new int[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].GetData(), dimension * sizeof(float));
	glUniform2iv(location, count, data);
	delete []data;
}

void Program::Uniform(int location, const Vec3I &vec)
{
	glUniform3i(location, vec.X(), vec.Y(), vec.Z());
}

void Program::Uniform(int location, Vec3I *vec, int count)
{
	int dimension = vec->GetDimension();
	int *data = new int[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].GetData(), dimension * sizeof(float));
	glUniform3iv(location, count, data);
	delete []data;
}

void Program::Uniform(int location, const Vec4I &vec)
{
	glUniform4i(location, vec.X(), vec.Y(), vec.Z(), vec.W());
}

void Program::Uniform(int location, Vec4I *vec, int count)
{
	int dimension = vec->GetDimension();
	int *data = new int[count * dimension];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * dimension * sizeof(float), vec[i].GetData(), dimension * sizeof(float));
	glUniform4iv(location, count, data);
	delete []data;
}

void Program::Uniform(int location, const Matrix2x2 &matrix)
{
	int n = matrix.GetColumn() * matrix.GetRow();
	float *data = new float[n];
	memcpy(data, matrix.GetData(), n * sizeof(float));
	glUniformMatrix2fv(location, 1, GL_FALSE, data);
	delete []data;
}

void Program::Uniform(int location, Matrix2x2 *matrix, int count)
{
	int n = matrix->GetColumn() * matrix->GetRow();
	float *data = new float[n * count];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * n * sizeof(float), matrix[i].GetData(), n * sizeof(float));
	glUniformMatrix2fv(location, count, GL_FALSE, data);
	delete []data;
}

void Program::Uniform(int location, const Matrix3x3 &matrix)
{
	int n = matrix.GetColumn() * matrix.GetRow();
	float *data = new float[n];
	memcpy(data, matrix.GetData(), n * sizeof(float));
	glUniformMatrix3fv(location, 1, GL_FALSE, data);
	delete []data;
}

void Program::Uniform(int location, Matrix3x3 *matrix, int count)
{
	int n = matrix->GetColumn() * matrix->GetRow();
	float *data = new float[n * count];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * n * sizeof(float), matrix[i].GetData(), n * sizeof(float));
	glUniformMatrix3fv(location, count, GL_FALSE, data);
	delete []data;
}

void Program::Uniform(int location, const Matrix4x4 &matrix)
{
	int n = matrix.GetColumn() * matrix.GetRow();
	float *data = new float[n];
	memcpy(data, matrix.GetData(), n * sizeof(float));
	glUniformMatrix4fv(location, 1, GL_FALSE, data);
	delete []data;
}

void Program::Uniform(int location, Matrix4x4 *matrix, int count)
{
	int n = matrix->GetColumn() * matrix->GetRow();
	float *data = new float[n * count];
	for(int i = 0; i != count; ++i)
		memcpy(data + i * n * sizeof(float), matrix[i].GetData(), n * sizeof(float));
	glUniformMatrix4fv(location, count, GL_FALSE, data);
	delete []data;
}

static Program *g_CommonProgram = NULL;
Program *Program::Common()
{
	if(g_CommonProgram == NULL)
	{
		g_CommonProgram = new Program(VertexShader::Common(), FragmentShader::Common());
		g_CommonProgram->Link();
	}
	return g_CommonProgram;
}
