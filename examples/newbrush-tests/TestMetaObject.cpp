#include "newbrush/core/MetaObject.h"
#include "newbrush/gui/UIElement.h"
#include "catch2/catch.hpp"

using namespace nb;

class DevideMetaObject : public NBObject
{
public:
	NB_OBJECT
};

MetaObject *DevideMetaObject::getMetaObject()
{
	static MetaObject m(Descriptor(typeid(MetaObject).hash_code(), "ContentControl", "MetaObject", "这是一个自定义控件"), NBObject::getMetaObject());
	m.addProperty(Descriptor(UIElement::WidthProperty().globalIndex(), UIElement::WidthProperty().ownerType().name(), UIElement::WidthProperty().name(), "描述元素宽度的属性"));
	return &m;
}

TEST_CASE("Test MetaObject", "[MetaObject]")
{
	auto dmo = std::make_shared<DevideMetaObject>();
	auto p = dmo->metaObject();
	printf("%s's properties\n", p->descriptor().displayName.data());
	for (auto dp : p->propertys())
	{
		printf("%s::%s->%s\n", dp.category.data(), dp.displayName.data(), dp.description.data());
	}

}