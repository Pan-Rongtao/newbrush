#include "newbrush/core/DateTime.h"
#include "catch2/catch.hpp"
#include "newbrush/core/Log.h"

using namespace nb;

namespace A { namespace B{
	class XXX {};
}}

template<class T>
void printClassInfo()
{
	std::type_index t = typeid(T);
	printf("class[%s] fullname=%s\n", t.name(), nb::getFullName(t).data());
	printf("class[%s] namespace=%s\n", t.name(), nb::getNamespace(t).data());
	printf("class[%s] classname=%s\n", t.name(), nb::getClassName(t).data());
};

TEST_CASE("Test nb::Def", "[Def]")
{
	printClassInfo<bool>();
	printClassInfo<int>();
	printClassInfo<int64_t>();
	printClassInfo<float>();
	printClassInfo<double>();
	printClassInfo<std::string>();
	printClassInfo<char>();
	printClassInfo<wchar_t>();
	printClassInfo<nb::Log>();
	printClassInfo<A::B::XXX>();
}