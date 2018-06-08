#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace gl{ namespace egl{

class NB_EXPORT Display
{
public:
	Display();
	Display(long id);

	bool IsNull() const;

	long GetId() const;

	void *GetEGLHandle() const;

public:
	static Display Default();

private:
	void				*m_Handle;
	long				m_Id;
};

}}}
