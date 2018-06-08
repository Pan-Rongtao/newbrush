#pragma once

#include "Storyboard.h"
#include "VisualState.h"

#include <set>

namespace nb { namespace Gui {

class VisualState;
class NB_EXPORT VisualStateStoryboard : public nb::Media::Storyboard
{
public:
	VisualStateStoryboard(void);
	virtual ~VisualStateStoryboard(void);

	void AddState(VisualState *state);

	bool HasState(VisualState *state) const;

	bool Trigger(RefObjectSet<VisualState, VisualStatePtr> *set);

private:
	RefObjectSet<VisualState, VisualStatePtr> *m_pstates;
};

typedef nbObjectPtrDerive<VisualStateStoryboard, nb::Media::StoryboardPtr> VisualStateStoryboardPtr;

}}
