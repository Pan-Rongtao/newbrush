#pragma once
#include "newbrush/core/Def.h"
#include "rttr/registration.h"

namespace nb {

class MetaObject;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;
using rttr::variant;

class NB_API Object
{
	RTTR_ENABLE()
public:
	Object() = default;
	virtual ~Object() = default;

	//子类应该重写此函数返回自己的MetaObject信息
	static std::shared_ptr<MetaObject> getMetaObject();

	//子类重写返回getMetaObject()即可
	virtual std::shared_ptr<MetaObject> metaObject();

};

#define NB_OBJECT \
public:\
	static std::shared_ptr<MetaObject> getMetaObject();\
	virtual std::shared_ptr<MetaObject> metaObject() override\
	{\
		return getMetaObject();\
	}

}