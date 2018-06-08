#include <map>
#include <string>
#include "core/Object.h"
#include "../../src/gles/GlesProgram.h"

namespace nb{ namespace gl {namespace Gles{

class GlesProgram;
class NB_EXPORT ProgramCache
{
public:
	static ProgramCache *GetInstance();
	GlesProgramPtr GetProgram(const std::string &vertexShaderSourcecode, const std::string &fragmentShaderSourcecode);

private:
	ProgramCache() {}
	~ProgramCache() {}

	std::map< const std::string, GlesProgramPtr >	m_mapPrograms;
	static ProgramCache								*g_pInstance;
};

}}}
