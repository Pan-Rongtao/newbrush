#pragma once

#include "RefObject.h"

namespace nb { namespace core {

class NB_API PropertyLock : public RefObject
{
public:
	PropertyLock(void);
	virtual ~PropertyLock(void);
};

typedef nbObjectPtrDerive<PropertyLock, RefObjectPtr> PropertyLockPtr;

}}

