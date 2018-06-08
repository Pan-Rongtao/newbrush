#pragma once

#include <list>
#include "gui/VisualStateGroup.h"
#include "gui/VisualStateCombination.h"
#include "gui/VisualStateStoryboard.h"

namespace nb { namespace Gui {

class VisualStateStoryboard;
class VisualStateManagerPrivate
{
public:
	VisualStateManagerPrivate(void);
	virtual ~VisualStateManagerPrivate(void);

	void AddGroup(VisualStateGroup *group);
	VisualStateGroup * GetGroup(const char *name) const;

	void AddStoryboard(VisualStateStoryboard *storyboard);
	void TestGotoState(VisualStateGroup *group, VisualState *state);

private:
	std::multimap<std::string, VisualStateGroupPtr> m_groups;
	std::list<VisualStateCombinationPtr> m_combinations;
	std::list<VisualStateStoryboardPtr> m_storyboards;
};

}}
