#pragma once

#include "RefObject.h"

namespace nb { namespace Core {

class NB_CORE_DECLSPEC_X_INTERFACE PropertyLock : public RefObject
{
public:
	PropertyLock(void);
	virtual ~PropertyLock(void);
};

typedef nbObjectPtrDerive<PropertyLock, RefObjectPtr> PropertyLockPtr;

}}

