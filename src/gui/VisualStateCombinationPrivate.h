#pragma once

#include <vector>
#include "gui/VisualState.h"

namespace nb { namespace Gui {

class VisualStateCombinationPrivate
{
public:
	VisualStateCombinationPrivate(void);
	virtual ~VisualStateCombinationPrivate(void);

private:
	std::vector<VisualStatePtr> m_states;
};

}}
