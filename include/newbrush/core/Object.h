#pragma once
#include "newbrush/core/Def.h"

namespace nb {

class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API Object
{
	RTTR_ENABLE()
public:
	Object() = default;
	virtual ~Object() = default;

};

}