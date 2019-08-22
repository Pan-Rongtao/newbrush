#pragma once
#include <vector>
#include "gui/Property.h"

namespace nb{ namespace gui{

class Window;

class WindowCollections
{
public:
	static std::vector<Window *>			Windows;
};

}}