#include "catch2/catch.hpp"
#include "newbrush/model/RttrRegistration.h"

using namespace nb;

class A
{
	RTTR_ENABLE()
public:
};

class B : public A
{
	RTTR_ENABLE(A)
public:
	int x = 0;
};
using APtr = std::shared_ptr<A>;
using BPtr = std::shared_ptr<B>;

class CCC
{
public:
	void setV(BPtr v)
	{
		m_v = v;
	}
	BPtr v()
	{
		return m_v;
	}

private:
	BPtr m_v;
};

using CCCPtr = std::shared_ptr<CCC>;

RTTR_REGISTRATION
{
	registration::class_<CCC>("CCC")
	.constructor<>() (policy::ctor::as_std_shared_ptr)
	.property("V", &CCC::v, &CCC::setV);
	;

	registration::class_<A>("A")
	.constructor<>() (policy::ctor::as_std_shared_ptr)
	;

	registration::class_<B>("B")
		.constructor<>() (policy::ctor::as_std_shared_ptr)
		.property("X", &B::x);
	;
}

TEST_CASE("TestRTTR", "[TestRTTR]")
{
	auto tC = type::get_by_name("CCC");
	auto objC = tC.create();
	auto propertyC = tC.get_property("V");

	APtr v;
	auto bd = std::make_shared<B>();
	bd->x = 10;
	v = bd;

	auto tB = type::get_by_name("B");
	auto objB = tB.create();
	auto tBB = objB.get_type();
	auto propertyB = tBB.get_wrapped_type().get_property("X");
	bool bpb = propertyB.set_value(objB, 11);
	/*
	instance ins = v;
	auto ttB = ins.get_wrapped_instance().get_derived_type();
	auto vx = ttB.create();

	vx = v;
	auto dd = vx.get_value<APtr>();
	//auto vvv = ttB.register_wrapper_converter_for_base_classes
	*/
	bool b = propertyC.set_value(objC, objB);
	int xx = 10;
}