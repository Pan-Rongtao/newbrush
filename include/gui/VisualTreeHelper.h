#pragma once
#include "../core/Def.h"

namespace nb
{
namespace gui
{

class UIElement;
class NB_API VisualTreeHelper
{
public:
	static uint32_t getChildCount(UIElement *element);
	static UIElement * getChild(UIElement *element, uint32_t childIndex);

};

}
}