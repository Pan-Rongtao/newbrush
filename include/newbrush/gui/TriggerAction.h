#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/media/Storyboard.h"

namespace nb 
{

class NB_API TriggerAction
{
public:
	virtual void invoke();
};

class NB_API BeginStoryboard : public TriggerAction
{
public:
	virtual void invoke() override;

	StoryboardPtr	storyboard;
};

using TriggerActionPtr = std::shared_ptr<TriggerAction>;

}