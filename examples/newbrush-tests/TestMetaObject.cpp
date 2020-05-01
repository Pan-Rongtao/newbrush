#include "newbrush/core/MetaObject.h"
#include "newbrush/gui/UIElement.h"
#include "catch2/catch.hpp"

using namespace nb;

class DevideMetaObject : public Object
{
public:
	NB_OBJECT
};

MetaObject *DevideMetaObject::getMetaObject()
{
	auto meta = MetaObject::get<DevideMetaObject, Object>("Shape", "Object", "矩形，形状的一种，可填充画刷，也可设置边框", [] {return std::make_shared<DevideMetaObject>(); });
//	ClassDescriptor dsp(typeid(DevideMetaObject).hash_code(), "Shape", "Object", "矩形，形状的一种，可填充画刷，也可设置边框", Object::getMetaObject(), [] {return std::make_shared<DevideMetaObject>(); });
//	static MetaObject metaObj(dsp);
	meta->addProperty(Descriptor(UIElement::WidthProperty().globalIndex(), UIElement::WidthProperty().ownerType().name(), UIElement::WidthProperty().name(), "描述元素宽度的属性"));
	return meta.get();
}

TEST_CASE("Test MetaObject", "[MetaObject]")
{
	auto metaObj = DevideMetaObject::getMetaObject();
	auto classDsp = metaObj->classDescriptor();
	printf("[%s(%d),%s,%s]\n", classDsp.category.data(), classDsp.id, classDsp.displayName.data(), classDsp.description.data());
	for (auto dp : metaObj->propertys())
	{
		printf("%s::%s->%s\n", dp.category.data(), dp.displayName.data(), dp.description.data());
	}

}