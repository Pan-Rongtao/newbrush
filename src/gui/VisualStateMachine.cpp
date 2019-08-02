#include "gui/VisualStateMachine.h"

using namespace nb::core;
using namespace nb::gui;

void VisualStateMachine::addGroup(std::shared_ptr<VisualStateGroup> group)
{
	for (auto const &g : m_groups)
		if (g->Name == group->Name)
		{
			nbThrowException(std::logic_error, "[%s] is already exists", g->Name().data());
		}
	m_groups.push_back(group);
}

bool VisualStateMachine::gotoState(const std::string &groupName, const std::string & stateName, bool useTransitions)
{
	for (auto const &g : m_groups)
	{
		if (g->Name() == groupName)
		{
			if (useTransitions)
			{
				
			}
			for (auto const &s : g->States())
			{
				if (s->Name == stateName)
				{
					s->Storyboard()->begin();
					return true;
				}
			}
		}
	}
	return false;
}
