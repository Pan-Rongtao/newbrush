#include "gles/Shader.h"
#include "core/Exception.h"
#include "system/File.h"
#include <GLES2/gl2.h>

using nb::System::Stream;
using nb::System::String;
using nb::System::File;
using nb::gl::Gles::Shader;
using nb::gl::Gles::VertexShader;
using nb::gl::Gles::FragmentShader;

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

Shader::Shader(const nb::System::String &sourceCode)
: m_SourceCode(sourceCode)
{
}

void Shader::SetSourceCode(const nb::System::String &sourceCode)
{
	m_SourceCode = sourceCode;
}

nb::System::String Shader::GetSourceCode() const
{
	return m_SourceCode;
}

void Shader::Compile()
{
	Stream ba = m_SourceCode.ToAscii().GetData();
	const char *p = ba.GetData();
	glShaderSource(m_ShaderHandle, 1, &p, NULL);
	glCompileShader(m_ShaderHandle);
	GLint nShaderStatus;
	glGetShaderiv(m_ShaderHandle, GL_COMPILE_STATUS, &nShaderStatus);
	if(!nShaderStatus)
	{
		GLint nLogLeng;
		glGetShaderiv(m_ShaderHandle, GL_INFO_LOG_LENGTH, &nLogLeng);

		char *pLog = new char[nLogLeng];
		glGetShaderInfoLog(m_ShaderHandle, nLogLeng, NULL, pLog);
		std::string sLog = pLog;
		delete []pLog;

		NB_THROW_EXCEPTION((std::string("shader::compile fail, reason:") + sLog).data());
	}
}

bool Shader::HasCompiled() const
{
	GLint status;
	glGetShaderiv(GetShaderHandle(), GL_COMPILE_STATUS, &status);
	return status != 0;
}

unsigned int Shader::GetShaderHandle() const
{
	return m_ShaderHandle;
}

bool Shader::Equal(Shader *shader) const
{
	return m_SourceCode == shader->m_SourceCode;
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

VertexShader::VertexShader(const nb::System::String &sourceCode)
: Shader(sourceCode)
{
	m_ShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	if(m_ShaderHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create vertex shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}

static VertexShader *g_CommonVertexShader = NULL;
VertexShader *VertexShader::Common()
{
	if(g_CommonVertexShader == NULL)
	{
		g_CommonVertexShader = new VertexShader
			("\
				attribute	vec4	attr_position;\
				attribute	vec4	attr_color;\
				attribute	vec2	attr_textureCoord;\
				uniform		mat4	unif_mvp;\
				varying		vec4	vary_color;\
				varying		vec2	vary_textureCoord;\
			\
				void main()\
				{\
					vary_color = attr_color;\
					vary_textureCoord = attr_textureCoord;\
					gl_Position = unif_mvp * attr_position;\
				}\
			");
		g_CommonVertexShader->Compile();
	}
	return g_CommonVertexShader;
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

FragmentShader::FragmentShader(const nb::System::String &sourceCode)
: Shader(sourceCode)
{
	m_ShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	if(m_ShaderHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create fragment shader fail, gl error code[%d], do you forget to call MakeCurrent pre?", glGetError());
		NB_THROW_EXCEPTION(info);
	}
}

static FragmentShader *g_CommonFragmentShader = NULL;
FragmentShader *FragmentShader::Common()
{
	if(g_CommonFragmentShader == NULL)
	{
		g_CommonFragmentShader = new FragmentShader
			("\
				uniform		sampler2D	sampler;\
				uniform		float		unif_blendIntensity;\
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
		g_CommonFragmentShader->Compile();
	}
	return g_CommonFragmentShader;
}
