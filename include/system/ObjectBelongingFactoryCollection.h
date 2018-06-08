#pragma once

#include "Array.h"
#include "ObjectBelongingFactory.h"

namespace nb { namespace System {

class NB_EXPORT ObjectBelongingFactoryCollection : public ObjectArray<ObjectBelongingFactory>
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ObjectBelongingFactoryCollection(void);
	virtual ~ObjectBelongingFactoryCollection(void);
};

}}
