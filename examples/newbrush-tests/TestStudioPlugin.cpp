#include "newbrush/gui/BuildinStudioPlugin.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test StudioPlugin", "[StudioPlugin]")
{
	BuildinStudioPlugin plugin;
	auto ss = sizeof(CClassInfo);
	std::vector<std::shared_ptr<MetaObject>> metaObjects;
	plugin.getMetametaObjectsOverride(metaObjects);
	auto count = 15;
	CClassInfo *infos = new CClassInfo[count];
	for (size_t i = 0; i < (size_t)count && i < metaObjects.size(); ++i)
	{
		auto obj = metaObjects[i];
		auto classDsp = obj->classDescriptor();
		auto cClass = infos[i];
		strcpy(cClass.typeName, nb::getFullName(classDsp.type).data());
		strcpy(cClass.category, classDsp.category.data());
		strcpy(cClass.displayName, classDsp.displayName.data());
		strcpy(cClass.description, classDsp.description.data());

		auto propertyCount = sizeof(CClassInfo::propertys) / sizeof(CPropertyInfo);
		auto &allProperties = obj->getAllProperties();
		for (auto j = 0; j < propertyCount; ++j)
		{
			auto cProperty = cClass.propertys[j];
			if (j < allProperties.size())
			{
				auto sdkProperty = allProperties[j];
				cProperty.type = sdkProperty.type;
				strcpy(cProperty.category, sdkProperty.category.data());
				strcpy(cProperty.displayName, sdkProperty.displayName.data());
				strcpy(cProperty.description, sdkProperty.description.data());
				cProperty.valueType = cProperty.valueType;
				strcpy(cProperty.extra, sdkProperty.extra.data());
			}
			else
			{
				strcpy(cProperty.category, "");
				strcpy(cProperty.displayName, "");
				strcpy(cProperty.description, "");
				cProperty.valueType = -1;
				strcpy(cProperty.extra, "");
			}
		}
	}
}