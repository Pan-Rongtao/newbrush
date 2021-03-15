#include "Action.h"
#include "newbrush/Animation.h"

using namespace nb;

void StartAnimationAction::execute()
{ 
	animation->begin(); 
}

void StopAnimationAction::execute()
{ 
	animation->stop();
}

void SetPropertyAction::execute()
{ 
	target->setValue(property, value);
}