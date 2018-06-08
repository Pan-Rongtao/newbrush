#include "PrimitiveGlesProgramState.h"
#include "GlesProgram.h"
using namespace nb::gl::Gles;


void PrimitiveGlesProgramState::Init()
{
	m_iPosition		 =	m_program->GetAttribLocation("_position");
	m_iColor		 =	m_program->GetUniformLocation("_color");
	m_iMVP			 =	m_program->GetUniformLocation("_MVP");
}