#include "newbrush/core/MetaObject.h"
#include "newbrush/gui/UIElement.h"
#include "catch2/catch.hpp"

using namespace nb;

class DevideMetaObject : public Object
{
public:
	NB_OBJECT

	template <class T1, class T2>
	static typename std::enable_if<std::is_void<T2>::value, int>::type get()
	{
		return 0;
	}

	template <class T1, class T2>
	static typename std::enable_if<!std::is_void<T2>::value, int>::type get()
	{
		return 1;
	}

};

std::shared_ptr<MetaObject> DevideMetaObject::getMetaObject()
{
	auto meta = MetaObject::get<DevideMetaObject, Object>("Shape", "Object", "矩形，形状的一种，可填充画刷，也可设置边框", [] {return std::make_shared<DevideMetaObject>(); });
	meta->addProperty(UIElement::WidthProperty(), "杂项", "描述元素宽度的属性", PropertyDescriptor::Single);
	return meta;
}

TEST_CASE("Test MetaObject", "[MetaObject]")
{
	auto metaObj = DevideMetaObject::getMetaObject();
	auto classDsp = metaObj->classDescriptor();
	printf("[%s(%d),%s,%s]\n", classDsp.category.data(), classDsp.type.hash_code(), classDsp.displayName.data(), classDsp.description.data());
	for (auto dp : metaObj->properties())
	{
		printf("%s::%s->%s\n", dp.category.data(), dp.displayName.data(), dp.description.data());
	}

	DevideMetaObject xx;
	DevideMetaObject::get<int, int>();
}