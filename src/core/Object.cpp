#include "newbrush/core/Object.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

std::shared_ptr<MetaObject> Object::getMetaObject()
{
	auto meta = MetaObject::get<Object, void>("", "Object", "超类", [] {return std::make_shared<Object>(); });
	return meta;
}

std::shared_ptr<MetaObject> Object::metaObject()
{
	return getMetaObject();
}
