#pragma once
#include <string>
#include "GlesProgram.h"
#include <GLES2/gl2.h>
namespace nb{ namespace gl{ namespace Gles{

class FontShader: public nbObject
{
public:
	FontShader();

	virtual ~FontShader();


protected:
	static void UseFontShader();

	static void UnUseFontShader();

	static void OnGlesDeInit();

	static GLint m_position;

	static GLint m_uv;

	static GLint m_color;

	static GLint m_texture;

	static GLint m_MVP;

	static GlesProgram * m_pShaderProgram;
};

}}}
