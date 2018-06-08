#pragma once
#include <GLES2/gl2.h>
#include "GlesProgramState.h"
namespace nb{ namespace gl{ namespace Gles{

class PrimitiveGlesProgramState: public GlesProgramState
{
public:

	GLint	m_iPosition;

	GLint	m_iColor;

	GLint	m_iMVP;
protected:
	virtual void Init();
};
typedef nbObjectPtrDerive<PrimitiveGlesProgramState, GlesProgramStatePtr> PrimitiveGlesProgramStatePtr;


}}}