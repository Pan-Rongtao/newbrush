#pragma once
#include "GlesProgramState.h"
#include <GLES2/gl2.h>

namespace nb{ namespace gl{ namespace Gles{

class FontGlesProgramState: public GlesProgramState
{
public:
	FontGlesProgramState();
	virtual ~FontGlesProgramState();
	GLint m_position;
	GLint m_uv;
	GLint m_color;
	GLint m_texture;
	GLint m_MVP;
protected:
	virtual void Init();
};
typedef nbObjectPtrDerive<FontGlesProgramState, GlesProgramStatePtr> FontGlesProgramStatePtr;
	
}}}