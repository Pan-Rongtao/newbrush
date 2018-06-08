#include "VisualStateGroupPrivate.h"

using namespace nb::Gui;

VisualStateGroupPrivate::VisualStateGroupPrivate(void)
{
}

VisualStateGroupPrivate::~VisualStateGroupPrivate(void)
{
}

void VisualStateGroupPrivate::AddChild(VisualState *state)
{
	if(m_currentState == NULL) m_currentState = state;
//	m_states.push_back(state);
	m_states |= state;

	m_stateMap.insert(std::pair<std::string, VisualStatePtr>(state->GetName(), state));
}

VisualState * VisualStateGroupPrivate::GetChild(const char *name) const
{
	std::multimap<std::string, VisualStatePtr>::const_iterator itor = m_stateMap.find(name);
	if(itor == m_stateMap.end()) return NULL;
	return itor->second;
}

VisualState * VisualStateGroupPrivate::GetState(char *name) const
{
	std::multimap<std::string, VisualStatePtr>::const_iterator itor = m_stateMap.begin();
	for(; itor != m_stateMap.end(); itor++)
	{
		const VisualStatePtr & s = itor->second;
		if(s->GetName() == name)
		{
			return s;
		}
	}

	return NULL;
}

void VisualStateGroupPrivate::GotoState(VisualState *state)
{
	m_currentState = state;
}

VisualState * VisualStateGroupPrivate::GetCurrentState() const
{
	return m_currentState;
}
