#include "TestDependencyProperty.h"

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

void TestDependencyProperty::test()
{
	set(BoolPoperty(), (float)0);
	set(BoolPoperty(), 1);
	set(IntProperty(), 111);
	set(IntProperty(), 111);
	set(FloatProperty(), 222.222);
	set(DoubleProperty(), 333.333);
	std::string s = std::string("abc");
	char axx[] = "abc";
	set(StringProperty(), std::wstring(L"DD"));
	set(StringProperty(), "def");
	set(WStringProperty(), std::string("def"));
	set(PointProperty(), Point(2, 2));
	set(PointProperty(), Point(2, 2));

	std::shared_ptr<A> b = std::make_shared<B>();
	set(SharedPtrProperty(), b);
	auto ret = get<std::shared_ptr<A>>(SharedPtrProperty());
	auto bx = std::dynamic_pointer_cast<B>(ret);
}

DependencyProperty TestDependencyProperty::BoolPoperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, bool>("Bool", true, [](DependencyObject *dp, DependencyPropertyChangedEventArgs *args) {
		auto tdp = dynamic_cast<TestDependencyProperty *>(dp);
		printf("%s changed from %d to %d\n", args->property.name().data(), args->oldValue.extract<bool>(), args->newValue.extract<bool>());
	});
	return dp;
}

DependencyProperty TestDependencyProperty::IntProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, int>("Int", 1);
	return dp;
}

DependencyProperty TestDependencyProperty::FloatProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, float>("Float", 2.0);
	return dp;
}

DependencyProperty TestDependencyProperty::DoubleProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, double>("Double", 3.0);
	return dp;
}

DependencyProperty TestDependencyProperty::StringProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, std::string>("String", "");
	return dp;
}

DependencyProperty TestDependencyProperty::WStringProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, std::wstring>("WString", L"");
	return dp;
}

DependencyProperty TestDependencyProperty::PointProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, Point>("Point", Point(5, 5));
	return dp;
}

DependencyProperty TestDependencyProperty::SharedPtrProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, std::shared_ptr<A>>("SharedPtr", nullptr);
	return dp;
}