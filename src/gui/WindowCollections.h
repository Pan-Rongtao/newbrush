#pragma once
#include <vector>
#include "core/Property.h"

namespace nb{ namespace gui{

class Window;

class WindowCollections
{
public:
	static nb::core::Property_rw<std::vector<Window *>>			Windows;
};

}}