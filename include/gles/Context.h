#pragma once
#include "core/NewBrushDef.h"
#include "gles/Context.h"

namespace nb{ namespace gl{ namespace egl{

class Configure;
class NB_EXPORT Context
{
public:
	Context(const Configure &configure);
	~Context();

	void *GetEGLHandle() const;

private:
	void		*m_Handle;
};

}}}
