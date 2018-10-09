#include "gles/Material.h"
#include "gles/Program.h"

using namespace nb::gl;

Material::Material()
{
}

Material::Material(std::shared_ptr<Program> program)
: m_program(program)
{
}

Material::Material(std::shared_ptr<Program> program, const std::vector<std::shared_ptr<Texture>> &textures)
: m_program(program)
, m_textures(textures)
{
}

void Material::setProgram(std::shared_ptr<Program> program)
{
	m_program = program;
}

std::shared_ptr<Program> Material::program()
{
	return m_program;
}

std::vector<std::shared_ptr<Texture>>& Material::textures()
{
	return m_textures;
}

const std::vector<std::shared_ptr<Texture>>& Material::textures() const
{
	return m_textures;
}
