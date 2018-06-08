#pragma once
namespace nb { namespace Gui{

class IElementRender
{
public:
	virtual void OnRender(float x, float y) = 0;
};

}}
