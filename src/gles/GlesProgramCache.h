#pragma once
#include <map>
#include "GlesProgramId.h"
#include "core/Object.h"
namespace nb{ namespace gl{ namespace Gles{

class GlesProgram;
class GlesProgramState;
class GlesProgramCache : public nbObject
{
public:
	GlesProgramCache(void);

	~GlesProgramCache(void);
	
	GlesProgram* GetProgram(ShaderType type);

	template<class T>
	T* GetProgramState(ShaderType type)
	{
		std::map<ShaderType, GlesProgram*>::iterator it;
		it = m_glesProgramMap.find(type);
		if (it != m_glesProgramMap.end())
		{
			T* t = new T();
			GlesProgram* program = it->second;
			t->InitPrivate(program);
			return t;
		}
		return NULL;
	};

	void AddProgram(ShaderType type,GlesProgram* program);

	void ClearProgram();

private:
	std::map<ShaderType, GlesProgram*> m_glesProgramMap;
};


}}}
