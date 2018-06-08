#include "gles/ProgramCache.h"

using namespace nb::gl::Gles;
ProgramCache *ProgramCache::g_pInstance = NULL;
ProgramCache *ProgramCache::GetInstance()
{
	if(g_pInstance == NULL)
		g_pInstance = new ProgramCache();
	return g_pInstance;
}

GlesProgramPtr ProgramCache::GetProgram(const std::string &vertexShaderSourcecode, const std::string &fragmentShaderSourcecode)
{
	std::string sKey = vertexShaderSourcecode + fragmentShaderSourcecode;
	std::map< const std::string, GlesProgramPtr >::const_iterator iterFind = m_mapPrograms.find(sKey);
	if(iterFind == m_mapPrograms.end())
	{
		GlesProgram *program = GlesProgram::CreateWithByteArrays(vertexShaderSourcecode.data(), fragmentShaderSourcecode.data());
		m_mapPrograms[sKey] = program;
		return program;
	}
	else
	{
		return iterFind->second;
	}
}
