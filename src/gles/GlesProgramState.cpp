#include "GlesProgramState.h"
#include "GlesProgram.h"

using namespace nb::gl::Gles;

GlesProgramState::GlesProgramState()
{
}

GlesProgramState::~GlesProgramState(void)
{
}

void GlesProgramState::InitPrivate(GlesProgram* program)
{
	m_program = program;
	Init();
}

void GlesProgramState::Use()
{
	m_program->Use();
}

void GlesProgramState::UnUse()
{
	m_program->UnUse();
}