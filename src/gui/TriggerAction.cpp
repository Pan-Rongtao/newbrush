#include "newbrush/gui/TriggerAction.h"

using namespace nb;

void TriggerAction::invoke()
{
}

void BeginStoryboard::invoke()
{
	storyboard->begin();
}
