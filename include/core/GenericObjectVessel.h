#pragma once

#include "Object.h"

namespace nb { namespace Core {
class NB_CORE_DECLSPEC_X_INTERFACE GenericObjectVessel : public nbObject
{
public:
	GenericObjectVessel(void);
	virtual ~GenericObjectVessel(void);

	template<class T>
	void operator = (T *object)
	{
	}

	template<class T>
	GenericObjectVessel(T *object)
	{
	}
};

}}
