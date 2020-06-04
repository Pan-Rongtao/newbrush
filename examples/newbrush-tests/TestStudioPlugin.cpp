#include "newbrush/gui/BuildinStudioPlugin.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test StudioPlugin", "[StudioPlugin]")
{
	auto categoryOrderCount = getCategoryOrderCount();
	CCategoryOrder *categoryOrders = new CCategoryOrder[categoryOrderCount];
	getCategoryOrders(categoryOrders, categoryOrderCount);
	std::vector<CCategoryOrder> vtCategoryOrders{ categoryOrders, categoryOrders + categoryOrderCount };
	delete[]categoryOrders;

	auto classCount = getMetaObjectCount();
	CClass *classes = new CClass[classCount];
	getMetaObjects(classes, classCount);
	std::vector<CClass> vtClasses(classes, classes + classCount);
	delete[]classes;
}