#include "TestProperty.h"

TestProperty::TestProperty()
{
	IsBool.setNotify(std::bind(&TestProperty::notifyIsBool, this, std::placeholders::_1, std::placeholders::_2));
}

void TestProperty::Test()
{
	bool b = IsBool;

	IsBool = true;

	b = IsBool;

	Size s = Range;
	Range = Size(2.0, 0.0);
	s = Range;
	float xx =((Size)Range).width();

	Size s1 = Range1;
	Range1 = Size(10.11, 2);
	s1 = Range1;

	bool br = Visible;


//	Visible = true;
	Name = "123";
//	std::string ss = Name;
}

void TestProperty::notifyIsBool(bool _old, bool _new)
{

}
