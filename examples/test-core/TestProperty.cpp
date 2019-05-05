#include "TestProperty.h"

TestProperty::TestProperty()
{
	IsBool.notify(std::bind(&TestProperty::notifyIsBool, this, std::placeholders::_1, std::placeholders::_2));
}

void TestProperty::test()
{
	bool b = IsBool;

	IsBool = true;

	b = IsBool;

	Size s = Range;
	Range = Size(2.0, 0.0);
	s = Range;
	float xx =((Size)Range).width();

	Range1.bind([&]()->Size & {return m_range1; });
//	Range1.bind(nullptr);
	Size s1 = Range1;
	m_range1 = {3, 3};
	Range1 = Size(10.11f, 2.f); 
	s1 = Range1;
	Range = Range1;
	
	bool br = Visible;
	Visible.bind([&]()->bool& {return m_b; });

	bool bxx = Visible;
	m_b = true;
	bxx = Visible;
	Name = "123";
//	Visible = Visible;
//	std::string ss = Name;
}

void TestProperty::notifyIsBool(bool _old, bool _new)
{

}
