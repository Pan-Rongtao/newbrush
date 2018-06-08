#include "FontShader.h"

using namespace nb::gl::Gles;
	
GLint	FontShader::m_position	= -1;
GLint	FontShader::m_uv		= -1;
GLint	FontShader::m_color		= -1;
GLint	FontShader::m_texture	= -1;
GLint	FontShader::m_MVP		= -1;
GlesProgram * FontShader::m_pShaderProgram = NULL;
FontShader::FontShader()
{
	if(m_pShaderProgram != NULL)
	{
		return;
	}
	const char* vs =
	{
		"precision  lowp float; "
		"uniform    mat4 _MVP;"
		"attribute  vec3 _position;"
		"attribute  vec3 _uv;"
		"attribute  vec4 _color;"
		"varying    vec3 _outUV;"
		"varying    vec4 _outColor;"
		"void main()"
		"{"
		"   vec4    pos =   vec4(_position.x,_position.y,_position.z,1);"
		"   gl_Position =   _MVP * pos;"
		"   _outUV      =   _uv;"
		"   _outColor   =   _color;"
		"}"
	};
	const char* ps =
	{
		"precision  lowp float; "
		"uniform    sampler2D   _texture;"
		"varying    vec4        _outColor;"
		"varying    vec3        _outUV;"
		"void main()"
		"{"
		"   vec4   color   =   texture2D(_texture,vec2(_outUV.x,_outUV.y));"
		"  	if( _outUV.z > 0.0 )\n "
		"		gl_FragColor    =   color.w * _outColor;\n"
		" 	else "
		"       gl_FragColor    =   color * _outColor;"
		"}"
	};
	m_pShaderProgram = GlesProgram::CreateWithByteArrays(vs, ps);

	m_position	= m_pShaderProgram->GetAttribLocation("_position");
	m_uv		= m_pShaderProgram->GetAttribLocation("_uv");
	m_color		= m_pShaderProgram->GetAttribLocation("_color");
	m_texture	= m_pShaderProgram->GetUniformLocation("_texture");
	m_MVP		= m_pShaderProgram->GetUniformLocation("_MVP");
//	Domain::GetInstance()->GetGlesApp()->AddGlesInfoListener(&FontShader::OnGlesDeInit);
}

FontShader::~FontShader()
{
}


void FontShader::UseFontShader()
{
	m_pShaderProgram->Use();
	glEnableVertexAttribArray(m_position);
	glEnableVertexAttribArray(m_uv);
	glEnableVertexAttribArray(m_color);
}

void FontShader::UnUseFontShader()
{
	glDisableVertexAttribArray(m_position);
	glDisableVertexAttribArray(m_uv);
	glDisableVertexAttribArray(m_color);
	glUseProgram(0);
}
void FontShader::OnGlesDeInit()
{
	if(m_pShaderProgram == NULL) return;
	delete m_pShaderProgram;
	m_pShaderProgram = NULL;
	m_position	= -1;
	m_uv		= -1;
	m_color		= -1;
	m_texture	= -1;
	m_MVP		= -1;
}