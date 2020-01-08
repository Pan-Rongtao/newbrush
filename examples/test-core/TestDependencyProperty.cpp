#include "TestDependencyProperty.h"

class A
{

};
class B : public A
{

};

void TestDependencyProperty::test()
{
	set(BoolPoperty(), 0);
	set(BoolPoperty(), 1);
	set(IntProperty(), 111);
	set(IntProperty(), 111);
	set(FloatProperty(), 222.222);
	set(DoubleProperty(), 333.333);
	std::string s = std::string("abc");
	char axx[] = "abc";
	set(StringProperty(), axx);
	set(StringProperty(), "def");
	set(WStringProperty(), std::wstring(L"def"));
	set(PointProperty(), Point(2, 2));
	set(PointProperty(), Point(2, 2));
	set(SharedPtrProperty(), std::make_shared<B>());
}

DependencyProperty TestDependencyProperty::BoolPoperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, bool>("Bool", true);
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
