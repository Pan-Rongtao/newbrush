#include "gles/Material.h"
#include "gles/Program.h"

using nb::gl::Gles::Material;
using nb::gl::Gles::MaterialEventListener;
using nb::gl::Gles::Program;
using nb::gl::Gles::Texture;

Material::Material()
: m_Program(NULL)
, m_Texture(NULL)
, m_Listener(NULL)
{
}

Material::Material(Program *program)
: m_Program(program)
, m_Texture(NULL)
, m_Listener(NULL)
{
}

Material::Material(Program *program, Texture *texture)
: m_Program(program)
, m_Texture(texture)
, m_Listener(NULL)
{
}

void Material::SetProgram(Program *program)
{
	m_Program = program;
}

Program *Material::GetProgram() const
{
	return m_Program;
}

void Material::SetTexture(Texture *texture)
{
	m_Texture = texture;
	if(m_Listener)
		m_Listener->On_Texture_Changed();
}

Texture *Material::GetTexture() const
{
	return m_Texture;
}

bool Material::Equal(Material *material) const
{
	return m_Program->Equal(material->m_Program) && m_Texture == material->m_Texture;
}

void Material::SetListener(MaterialEventListener *listener)
{
	m_Listener = listener;
}
