#pragma once
#include "newbrush/Object.h"

namespace nb
{

class Animation;

class NB_API Action : public Object
{
public:
	virtual void execute() = 0;
};

class NB_API AnimationAction : public Action
{
public:
	ref<Animation> animation;
};

class NB_API StartAnimationAction : public AnimationAction
{
public:
	virtual void execute();
};

class NB_API StopAnimationAction : public AnimationAction
{
public:
	virtual void execute();
};

class NB_API SetPropertyAction : public Action
{
public:
	virtual void execute();

	ref<Object> target;
	property property;
	var value;
};

}