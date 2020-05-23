#include "newbrush/gui/BuildinStudioPlugin.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test StudioPlugin", "[StudioPlugin]")
{
	auto count = getMetaObjectCount();
	CClassInfo *infos = new CClassInfo[count];
	getMetaObjects(infos, count);

	std::vector<CClassInfo> vtInfos;
	for (int i = 0; i < count; ++i)
	{
		vtInfos.push_back(infos[i]);
	}

	delete[]infos;
}