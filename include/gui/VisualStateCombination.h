#pragma once

#include "core/Object.h"

namespace nb { namespace Gui {

class VisualStateCombination
{
public:
	VisualStateCombination(void);
	virtual ~VisualStateCombination(void);
};

typedef nbObjectPtrDerive<VisualStateCombination, nbObjectPtr> VisualStateCombinationPtr;

}}
