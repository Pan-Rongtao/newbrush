#pragma once

#include <vector>
#include "gui/VisualState.h"

namespace nb { namespace Gui {

class VisualStateGroupPrivate
{
public:
	VisualStateGroupPrivate(void);
	virtual ~VisualStateGroupPrivate(void);

	void AddChild(VisualState *state);
	VisualState * GetChild(const char *name) const;

	void GotoState(VisualState *state);
	VisualState * GetCurrentState() const;
	int GetStateCount() const {return m_states.GetCount();}

	VisualState * GetState(char *name) const;
private:
	//std::vector<VisualStatePtr> m_states;

	RefObjectSet<VisualState, VisualStatePtr> m_states;
	std::multimap<std::string, VisualStatePtr> m_stateMap;

	VisualStatePtr m_currentState;
};

}};
