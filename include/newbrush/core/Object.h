#pragma once
#include "newbrush/core/Def.h"
#include "newbrush/core/MetaObject.h"

namespace nb {

class MetaObject;
class NB_API Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	//子类应该重写此函数返回自己的MetaObject信息
	static MetaObject *getMetaObject();

	//子类重写返回getMetaObject()即可
	virtual MetaObject *metaObject();
};

#define NB_OBJECT\
	static MetaObject *getMetaObject();\
	virtual MetaObject *metaObject() override\
	{\
		return getMetaObject();\
	}

}