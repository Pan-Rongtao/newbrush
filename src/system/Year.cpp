#include <assert.h>
#include "system/Year.h"

using namespace nb::System;

const static int MaxYear = 9999;
const static int MinYear = 0001;
Year::Year()
{
	SetYear(2015);
}


Year::Year(int y)
{
	SetYear(y);
}

Year::Year(const Year &other)
{
	SetYear(other.m_Year);
}

void Year::operator = (const Year &right)
{
	SetYear(right.GetDigit());
}

Year::~Year()
{
}

int Year::GetDigit() const
{
	return m_Year;
}

bool Year::IsLeapYear() const
{
	return Year::IsLeapYear(GetDigit());
}

int Year::GetDayCount() const
{
	return Year::GetDayCount(GetDigit());
}

void Year::SetYear(int y)
{
	//fixed it when define in;
	assert(IsValid(y));
	m_Year = y;
}

//static funs
int Year::MaxValue()
{
	return MaxYear;
}

int Year::MinValue()
{
	return MinYear;
}

bool Year::IsValid(int y)
{
	return y >= MinYear && y <= MaxYear;
}

bool Year::IsLeapYear(int y)
{
	assert(IsValid(y));
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Year::GetDayCount(int y)
{
	assert(IsValid(y));
	return IsLeapYear(y) ? 366 : 365;
}
