#pragma once
#include <vector>
#include "core/Property.h"

namespace nb{ namespace gui{

class Window;

class WindowCollections
{
public:
	static std::vector<Window *>			Windows;
};

}}