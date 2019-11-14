#include "TestAny.h"
#include "core/Any.h"

void TestAny::test()
{
	nb::Any a = std::make_shared<int>(1);
	nb::Any b = a;
	auto x = nb::any_cast<std::shared_ptr<int>>(b);
	*x = 2;
}
