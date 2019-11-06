#pragma once
#include "../TestBase.h"
#include "core/NoneCopyable.h"

class Element : public nb::NoneCopyable
{
};
class Devide : public Element
{
};

class TestNoneCopyable : public TestBase
{
public:
	void test();


};

