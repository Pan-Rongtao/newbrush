#pragma once
#include "../TestBase.h"
#include <core/Property.h>
#include <core/Size.h>

using namespace nb::core;

class TestProperty : public TestBase
{
public:
	TestProperty();
	virtual void test() override;

	Property_rw<bool>	IsBool;
	Property_rw<int>	Integer0;
	Property_rw<int>	Integer1;
	Property_rw<float>	Float0;
	Property_rw<Size>	Range;
	Property_rw<Size>	Range1;
	Property_r<bool>	Visible;
	Property_w<std::string> Name;
	Property_r<Size>	SZR;

private:
	void notifyIsBool(bool _old, bool _new);

	Size	m_range1{Size(11,22)};
	Size	m_szGetter{ Size(1.11, 2.22) };
	bool	m_b{false};
};

class AA
{
};