#include "catch2/catch.hpp"
#include "newbrush/core/MetaType.h"

using namespace nb;

namespace Test
{
	class A : public Object
	{
	public:
		
		static std::shared_ptr<A> create()
		{
			return std::make_shared<A>();
		}
	};

	class B : public Object
	{
	public:
		NB_STATIC_MOUDULE(B)
	};
} 

using namespace Test;
TEST_CASE("Test MetaType", "[MetaType]")
{
	MetaType::registerClass<A>();
	MetaType::registerClass<B>();

	 
	auto a = MetaType::makeObject(typeid(A).name());
	auto b = MetaType::makeObject(typeid(B).name());
}