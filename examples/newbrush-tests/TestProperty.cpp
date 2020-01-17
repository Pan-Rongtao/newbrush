#include "TestProperty.h"

TestProperty::TestProperty()
	: IsBool([&](bool v) {m_bool = v; }, [&]()->bool& {return m_bool; })
	, Integer0([&](int v) {m_int0 = v; }, [&]()->int& {return m_int0; })
	, Integer1([&](int v) {m_int1 = v; }, [&]()->int& {return m_int1; })
	, Float0([&](float v) {m_float0 = v; }, [&]()->float& {return m_float0; })
	, Range([&](Size v) {m_size0 = v; }, [&]()->Size& {return m_size0; })
	, Range1([&](Size v) {m_size1 = v; }, [&]()->Size& {return m_size1; })
	, Visible([&]()->bool& {return m_visible; })
	, BorderSize(nullptr)
{

}

void TestProperty::test()
{
	Integer0 = 1;
	Integer1 = 2;
	int x = Integer1;
	x = 11;
	Integer1 = 5;
	x = Integer1;
	Integer1 = Integer0;
	x = Integer1();
	Integer0 = 3;
	x = Integer1();


	bool v = Visible;
	m_visible = !m_visible;

	Element e;
	m_vt.emplace_back(Element());

//	auto sz = BorderSize();

	tt();
}

void TestProperty::tt() const
{
	int x = Integer1;
	x = Integer1;
	bool v = Visible;
}
