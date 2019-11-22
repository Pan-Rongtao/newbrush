#pragma once
#include "../TestBase.h"
#include <core/Property.h>
#include <core/Size.h>

using namespace nb;

class Element
{
public:
	Element()
		: IsPressed([&](bool v) {return m_pressed; }, [&]()->bool& {return m_pressed; })
	{

	}

	Property_rw<bool>	IsPressed;

private:
	bool	m_pressed{ false };
};

class TestProperty : public TestBase
{
public:
	TestProperty();
	virtual void test() override;

	void tt() const;

	Property_rw<bool>	IsBool;
	Property_rw<int>	Integer0;
	Property_rw<int>	Integer1;
	Property_rw<float>	Float0;
	Property_rw<Size>	Range;
	Property_rw<Size>	Range1;
	Property_r<bool>	Visible;
	Property_r<Size>	BorderSize;
	
private:
	bool	m_bool{ false };
	int		m_int0{ 0 };
	int		m_int1{ 0 };
	float	m_float0{ 0.0f };
	Size	m_size0{ Size(11,22) };
	Size	m_size1{ Size(1.11f, 2.22f) };
	bool	m_visible{ false };
	std::vector<Element>	m_vt;
};
