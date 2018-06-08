#pragma once

#include "Object.h"

class NB_CORE_DECLSPEC_X_INTERFACE nbPropertyVariant : public nbObject
{
public:
	nbPropertyVariant(void);
	virtual ~nbPropertyVariant(void);

	operator int(){return 0;}
	operator nbObject *(){return NULL;}
};
