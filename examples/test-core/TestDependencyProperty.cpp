#include "TestDependencyProperty.h"

void TestDependencyProperty::test()
{
	set(BoolPoperty(), false);
	set(IntProperty(), 111);
	set(FloatProperty(), 222.222f);
	set(DoubleProperty(), 333.333);
	std::string s = std::string("abc");
	set(StringProperty(), s.data());
	set(PointProperty(), Point(2, 2));
	set(SharedPtrProperty(), std::make_shared<int>(1));
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

DependencyProperty TestDependencyProperty::PointProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, Point>("Point", Point(5, 5));
	return dp;
}

DependencyProperty TestDependencyProperty::SharedPtrProperty()
{
	static auto dp = DependencyProperty::registerDependency<TestDependencyProperty, std::shared_ptr<int>>("SharedPtr", nullptr);
	return dp;
}
