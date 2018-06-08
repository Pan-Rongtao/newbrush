#pragma once

#include "core/Object.h"

namespace nb{ namespace gl { namespace Gles{

class GlesProgram;
class GlesProgramCache;
class GlesProgramState : public nbObject
{
public:
	friend class GlesProgramCache;

	GlesProgramState();

	virtual ~GlesProgramState();

	virtual void Use();

	virtual void UnUse();

protected:

	virtual void Init() = 0;

	GlesProgram* m_program;
private:

	void InitPrivate(GlesProgram* program);
};

typedef nbObjectPtrDerive<GlesProgramState, nbObjectPtr> GlesProgramStatePtr;

}}}
