#include "FontGlesProgramState.h"
#include "GlesProgram.h"
using namespace nb::gl::Gles;

FontGlesProgramState::FontGlesProgramState()
{

}

FontGlesProgramState::~FontGlesProgramState()
{
}

void FontGlesProgramState::Init()
{
	m_position	= m_program->GetAttribLocation("_position");
	m_uv		= m_program->GetAttribLocation("_uv");
	m_color		= m_program->GetAttribLocation("_color");
	m_texture	= m_program->GetUniformLocation("_texture");
	m_MVP		= m_program->GetUniformLocation("_MVP");
}