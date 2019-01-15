#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Display
{
public:
	Display();
	Display(long id);

	bool isNull() const;

	long id() const;

	void *handle() const;

public:
	static Display defaultx();

private:
	void				*m_Handle;
	long				m_Id;
};

}}
