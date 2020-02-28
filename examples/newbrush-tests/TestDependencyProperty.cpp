#include "newbrush/core/DependencyObject.h"
#include "catch2/catch.hpp"

using namespace nb;

class MyObject : public DependencyObject
{
public:
	static DependencyProperty BoolPoperty();
	static DependencyProperty IntProperty();
	static DependencyProperty FloatProperty();
	static DependencyProperty DoubleProperty();
	static DependencyProperty StringProperty();
	static DependencyProperty WStringProperty();
	static DependencyProperty PointProperty();
	static DependencyProperty SharedPtrProperty();

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
	obj.set(MyObject::BoolPoperty(), (float)0);
	obj.set(MyObject::BoolPoperty(), 1);
	obj.set(MyObject::IntProperty(), 111);
	obj.set(MyObject::IntProperty(), 111);
	obj.set(MyObject::FloatProperty(), 222.222);
	obj.set(MyObject::DoubleProperty(), 333.333);
	std::string s = std::string("abc");
	char axx[] = "abc";
	obj.set(MyObject::StringProperty(), std::wstring(L"DD"));
	obj.set(MyObject::StringProperty(), "def");
	obj.set(MyObject::WStringProperty(), std::string("def"));
	obj.set(MyObject::PointProperty(), Point(2, 2));
	obj.set(MyObject::PointProperty(), Point(2, 2));

	std::shared_ptr<A> b = std::make_shared<B>();
	obj.set(MyObject::SharedPtrProperty(), b);
	auto ret = obj.get<std::shared_ptr<A>>(MyObject::SharedPtrProperty());
	auto bx = std::dynamic_pointer_cast<B>(ret);
}

DependencyProperty MyObject::BoolPoperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, bool>("Bool", true, [](DependencyObject *dp, DependencyPropertyChangedEventArgs *args) {
		auto tdp = dynamic_cast<MyObject *>(dp);
		printf("%s changed from %d to %d\n", args->property.name().data(), args->oldValue.extract<bool>(), args->newValue.extract<bool>());
	});
	return dp;
}

DependencyProperty MyObject::IntProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, int>("Int", 1);
	return dp;
}

DependencyProperty MyObject::FloatProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, float>("Float", 2.0);
	return dp;
}

DependencyProperty MyObject::DoubleProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, double>("Double", 3.0);
	return dp;
}

DependencyProperty MyObject::StringProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, std::string>("String", "");
	return dp;
}

DependencyProperty MyObject::WStringProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, std::wstring>("WString", L"");
	return dp;
}

DependencyProperty MyObject::PointProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, Point>("Point", Point(5, 5));
	return dp;
}

DependencyProperty MyObject::SharedPtrProperty()
{
	static auto dp = DependencyProperty::registerDependency<MyObject, std::shared_ptr<A>>("SharedPtr", nullptr, [](DependencyObject *dp, DependencyPropertyChangedEventArgs *args) {
		auto tdp = dynamic_cast<MyObject *>(dp);
		printf("%s changed\n", args->property.name().data());
	});
	return dp;
}
