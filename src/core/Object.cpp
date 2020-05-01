#include "newbrush/core/Object.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

MetaObject *Object::getMetaObject()
{
	ClassDescriptor dsp;
	dsp.id = typeid(Object).hash_code();
	dsp.category = "";
	dsp.displayName = "Object";
	dsp.description = "All NB classes's supper Class";
	static MetaObject metaObj(dsp);
	return &metaObj;
}

MetaObject *Object::metaObject()
{
	return getMetaObject();
}
