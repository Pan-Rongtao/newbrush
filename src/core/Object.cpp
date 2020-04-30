#include "newbrush/core/Object.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

MetaObject *Object::getMetaObject()
{
	Descriptor dsp;
	dsp.id = typeid(Object).hash_code();
	dsp.category = "";
	dsp.displayName = "Object";
	dsp.description = "All NB classes's supper Class";
	static MetaObject metaObj(dsp, nullptr);
	return &metaObj;
}

MetaObject *Object::metaObject()
{
	return getMetaObject();
}
