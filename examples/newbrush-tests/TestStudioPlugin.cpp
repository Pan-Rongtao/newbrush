#include "newbrush/gui/BuildinStudioPlugin.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace rttr;

TEST_CASE("Test StudioPlugin", "[StudioPlugin]")
{
#if 1
	auto range = type::get_types();
	std::vector<type> vtTypes(range.begin(), range.end());
	std::string s;
	for (auto t : vtTypes)
	{
		s = s + t.get_name().data() + "\r\n";
	}
#endif
	auto categoryOrderCount = getCategoryOrderCount();
	CCategoryOrder *categoryOrders = new CCategoryOrder[categoryOrderCount];
	getCategoryOrders(categoryOrders, categoryOrderCount);
	std::vector<CCategoryOrder> vtCategoryOrders{ categoryOrders, categoryOrders + categoryOrderCount };
	delete[]categoryOrders;

	auto classCount = getMetaClassCount();
	CClass *classes = new CClass[classCount];
	getMetaClasses(classes, classCount);
	std::vector<CClass> vtClasses(classes, classes + classCount);
	delete[]classes;
}