#pragma once
#include "newbrush/model/Def.h"

namespace nb {

class NB_API Object
{
	RTTR_ENABLE()
public:
	virtual ~Object() = default;

protected:
	Object() = default;
};

using ObjectPtr = std::shared_ptr<Object>;

}