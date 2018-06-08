#include "gui/VisualStateStoryboard.h"

using namespace nb::Gui;
using namespace nb::Media;

VisualStateStoryboard::VisualStateStoryboard(void)
{
	m_pstates = new RefObjectSet<VisualState, VisualStatePtr>();
}

VisualStateStoryboard::~VisualStateStoryboard(void)
{
	delete m_pstates;
}

void VisualStateStoryboard::AddState(VisualState *state)
{
	*m_pstates |= state;
}

bool VisualStateStoryboard::HasState(VisualState *state) const
{
	//return m_pstates->find(state) != m_pstates->end();
	return m_pstates->HasObject(state);
}

bool VisualStateStoryboard::Trigger(RefObjectSet<VisualState, VisualStatePtr> *set)
{
	if(!m_pstates->Include(set)) return false;

	Begin();

	return true;
}
