#include "GlesProgramCache.h"
#include "GlesProgram.h"

using namespace nb::gl::Gles;
GlesProgramCache::GlesProgramCache(void)
{
}

GlesProgramCache::~GlesProgramCache(void)
{
}

GlesProgram* GlesProgramCache::GetProgram(ShaderType type)
{ 
  std::map<ShaderType, GlesProgram*>::iterator it;
  it = m_glesProgramMap.find(type);
  if (it != m_glesProgramMap.end())
  {
	GlesProgram* program = it->second;
	return program;
  }
  return NULL;
}

void GlesProgramCache::AddProgram(ShaderType type,GlesProgram* program)
{
	m_glesProgramMap[type] = program;
}

void GlesProgramCache::ClearProgram()
{
	for(std::map<ShaderType, GlesProgram*>::iterator it=m_glesProgramMap.begin(); it!=m_glesProgramMap.end(); ++it)
	{
		GlesProgram* program = it->second;
		delete program;
	}
	m_glesProgramMap.clear();
}