#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/DependencyProperty.h"
#include "catch2/catch.hpp"

using namespace nb;

class MyObject : public DependencyObject
{
public:
	static DependencyPropertyPtr BoolPoperty();
	static DependencyPropertyPtr IntProperty();
	static DependencyPropertyPtr FloatProperty();
	static DependencyPropertyPtr DoubleProperty();
	static DependencyPropertyPtr StringProperty();
	static DependencyPropertyPtr WStringProperty();
	static DependencyPropertyPtr PointProperty();
	static DependencyPropertyPtr SharedPtrProperty();

};
class A
{
public:
	virtual ~A() {}
	int a{ 1 };
};
class B : public A
{
public:
	int b{ 2 };
};

TEST_CASE("Test nb::DependencyProperty", "[DependencyProperty]")
{
	MyObject obj;
	obj.setValue(MyObject::BoolPoperty(), (float)0);
	obj.setValue(MyObject::BoolPoperty(), 1);
	obj.setValue(MyObject::IntProperty(), 111);
	obj.setValue(MyObject::IntProperty(), 111);
	obj.setValue(MyObject::FloatProperty(), 222.222);
	obj.setValue(MyObject::DoubleProperty(), 333.333);
	std::string s = std::string("abc");
	char axx[] = "abc";
	obj.setValue(MyObject::StringProperty(), std::wstring(L"DD"));
	obj.setValue(MyObject::StringProperty(), "def");
	obj.setValue(MyObject::WStringProperty(), std::string("def"));
	obj.setValue(MyObject::PointProperty(), Point(2, 2));
	obj.setValue(MyObject::PointProperty(), Point(2, 2));

	std::shared_ptr<A> b = std::make_shared<B>();
	obj.setValue(MyObject::SharedPtrProperty(), b);
	obj.setValue(MyObject::SharedPtrProperty(), b);
	auto ret = obj.getValue<std::shared_ptr<A>>(MyObject::SharedPtrProperty());
	auto bx = std::dynamic_pointer_cast<B>(ret);
}

DependencyPropertyPtr MyObject::BoolPoperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, bool>("Bool", true, [](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		auto tdp = dynamic_cast<MyObject *>(obj);
		printf("%s changed from %d to %d\n", args->property->name().data(), args->oldValue.get_value<bool>(), args->newValue.get_value<bool>());
	});
	return dp;
}

DependencyPropertyPtr MyObject::IntProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, int>("Int", 1);
	return dp;
}

DependencyPropertyPtr MyObject::FloatProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, float>("Float", 2.0);
	return dp;
}

DependencyPropertyPtr MyObject::DoubleProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, double>("Double", 3.0);
	return dp;
}

DependencyPropertyPtr MyObject::StringProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, std::string>("String", "");
	return dp;
}

DependencyPropertyPtr MyObject::WStringProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, std::wstring>("WString", L"");
	return dp;
}

DependencyPropertyPtr MyObject::PointProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, Point>("Point", Point(5, 5));
	return dp;
}

DependencyPropertyPtr MyObject::SharedPtrProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, std::shared_ptr<A>>("SharedPtr", nullptr, [](DependencyObject *dp, DependencyPropertyChangedEventArgs *args) {
		auto tdp = dynamic_cast<MyObject *>(dp);
		printf("%s changed\n", args->property->name().data());
	});
	return dp;
}
