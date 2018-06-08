#include "VisualStateManagerPrivate.h"

using namespace nb::Gui;

VisualStateManagerPrivate::VisualStateManagerPrivate(void)
{
}

VisualStateManagerPrivate::~VisualStateManagerPrivate(void)
{
}

void VisualStateManagerPrivate::AddGroup(VisualStateGroup *group)
{
	m_groups.insert(std::pair<std::string, VisualStateGroupPtr>(group->GetName(), group));
}

VisualStateGroup * VisualStateManagerPrivate::GetGroup(const char *name) const
{
	std::multimap<std::string, VisualStateGroupPtr>::const_iterator itor = m_groups.find(name);
	if(itor == m_groups.end()) return NULL;
	return itor->second;
}

void VisualStateManagerPrivate::AddStoryboard(VisualStateStoryboard *storyboard)
{
	m_storyboards.push_back(storyboard);
}

void VisualStateManagerPrivate::TestGotoState(VisualStateGroup *group, VisualState *state)
{
	group->GotoState(state);

	RefObjectSet<VisualState, VisualStatePtr> set;

	std::multimap<std::string, VisualStateGroupPtr>::const_iterator itor = m_groups.begin();
	for(; itor != m_groups.end(); itor++)
	{
		set |= itor->second->GetCurrentState();
	}

	std::list<VisualStateStoryboardPtr>::iterator itorStoryboard = m_storyboards.begin();
	for(; itorStoryboard != m_storyboards.end(); itorStoryboard++)
	{
		if((*itorStoryboard)->Trigger(&set)) return;
	}
}
