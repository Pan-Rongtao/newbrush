#include "newbrush/gui/BuildinStudioPlugin.h"
#include "newbrush/gui/Canvas.h"
#include "newbrush/gui/DockPanel.h"
#include "newbrush/gui/WrapPanel.h"
#include "newbrush/gui/StackPanel.h"
#include "newbrush/gui/Grid.h"
#include "newbrush/gui/UniformGrid.h"
#include "newbrush/gui/Button.h"
#include "newbrush/gui/RepeatButton.h"
#include "newbrush/gui/Line.h"
#include "newbrush/gui/Polyline.h"
#include "newbrush/gui/Polygon.h"
#include "newbrush/gui/Path.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

void registerCommonType()
{
//	auto meta = MetaObject::get<int, Object>("通用", "Int", "整型", nullptr);

	auto x = std::make_shared<int>();
	auto p = *x;
}

void BuildinStudioPlugin::getMetametaObjectsOverride(std::vector<std::shared_ptr<MetaObject>> &metaObjects)
{
	metaObjects.push_back(Canvas::getMetaObject());
	metaObjects.push_back(DockPanel::getMetaObject());
	metaObjects.push_back(WrapPanel::getMetaObject());
	metaObjects.push_back(StackPanel::getMetaObject());
	metaObjects.push_back(Grid::getMetaObject());
	metaObjects.push_back(UniformGrid::getMetaObject());
	metaObjects.push_back(Button::getMetaObject());
	metaObjects.push_back(RepeatButton::getMetaObject());
	metaObjects.push_back(Window::getMetaObject());
	metaObjects.push_back(Line::getMetaObject());
	metaObjects.push_back(Polyline::getMetaObject());
	metaObjects.push_back(Polygon::getMetaObject());
	metaObjects.push_back(Path::getMetaObject());
	metaObjects.push_back(Rectangle::getMetaObject());
	metaObjects.push_back(Ellipse::getMetaObject());
}
/*
//NB_PLUGIN_ENTRY_FOR_STUDIO(BuildinStudioPlugin)
extern "C" NB_API int GetMetaObjectCount()
{
	BuildinStudioPlugin plugin;
	std::vector<std::shared_ptr<MetaObject>> metaObjects;
	plugin.getMetametaObjectsOverride(metaObjects);
	return metaObjects.size(); 
}

extern "C" NB_API void getMetaObjects(CClassInfo *infos, int count)
{
	BuildinStudioPlugin plugin;
	std::vector<std::shared_ptr<MetaObject>> metaObjects;
	plugin.getMetametaObjectsOverride(metaObjects);
	for (size_t i = 0; i < (size_t)count && i < metaObjects.size(); ++i)
	{
		auto obj = metaObjects[i];
		auto classDsp = obj->classDescriptor();
		auto &cClass = infos[i];
		strcpy(cClass.typeName, nb::getFullName(classDsp.type).data());
		strcpy(cClass.category, classDsp.category.data());
		strcpy(cClass.displayName, classDsp.displayName.data());
		strcpy(cClass.description, classDsp.description.data());
		
		auto propertyLimit = sizeof(CClassInfo::propertys) / sizeof(CPropertyInfo);
		auto &allProperties = obj->getAllProperties();
		for (auto j = 0; j < propertyLimit; ++j)
		{
			auto &cProperty = cClass.propertys[j];
			if (j < allProperties.size())
			{
				auto sdkProperty = allProperties[j];
				cProperty.type = sdkProperty.type;
				strcpy(cProperty.category, sdkProperty.category.data());
				strcpy(cProperty.displayName, sdkProperty.displayName.data());
				strcpy(cProperty.description, sdkProperty.description.data());
				cProperty.valueType = sdkProperty.valueType;
				strcpy(cProperty.extra, sdkProperty.extra.data());
			}
			else
			{
				cProperty.type = 0;
				strcpy(cProperty.category, "");
				strcpy(cProperty.displayName, "");
				strcpy(cProperty.description, "");
				cProperty.valueType = -1;
				strcpy(cProperty.extra, "");
			}
		}
	}
}
*/
NB_API int nb::getMetaObjectCount()
{
	//BuildinStudioPlugin plugin;
	//std::vector<std::shared_ptr<MetaObject>> metaObjects;
	//plugin.getMetametaObjectsOverride(metaObjects);
	//return metaObjects.size();
	//
	
	using namespace rttr;
	array_range<type> range = type::get_types();
	return range.size();
}

NB_API void nb::getMetaObjects(CClassInfo * infos, int count)
{
	//BuildinStudioPlugin plugin;
	//std::vector<std::shared_ptr<MetaObject>> metaObjects;
	//plugin.getMetametaObjectsOverride(metaObjects);
	//for (size_t i = 0; i < (size_t)count && i < metaObjects.size(); ++i)
	//{
	//	auto obj = metaObjects[i];
	//	auto classDsp = obj->classDescriptor();
	//	auto &cClass = infos[i];
	//	strcpy(cClass.typeName, nb::getFullName(classDsp.type).data());
	//	strcpy(cClass.category, classDsp.category.data());
	//	strcpy(cClass.displayName, classDsp.displayName.data());
	//	strcpy(cClass.description, classDsp.description.data());

	//	auto propertyLimit = sizeof(CClassInfo::propertys) / sizeof(CPropertyInfo);
	//	auto &allProperties = obj->getAllProperties();
	//	for (auto j = 0; j < propertyLimit; ++j)
	//	{
	//		auto &cProperty = cClass.propertys[j];
	//		if (j < allProperties.size())
	//		{
	//			auto sdkProperty = allProperties[j];
	//			cProperty.type = sdkProperty.type;
	//			strcpy(cProperty.category, sdkProperty.category.data());
	//			strcpy(cProperty.displayName, sdkProperty.displayName.data());
	//			strcpy(cProperty.description, sdkProperty.description.data());
	//			cProperty.valueType = sdkProperty.valueType;
	//			strcpy(cProperty.extra, sdkProperty.extra.data());
	//		}
	//		else
	//		{
	//			cProperty.type = 0;
	//			strcpy(cProperty.category, "");
	//			strcpy(cProperty.displayName, "");
	//			strcpy(cProperty.description, "");
	//			cProperty.valueType = -1;
	//			strcpy(cProperty.extra, "");
	//		}
	//	}
	//}
	using namespace rttr;
	array_range<type> range = type::get_types();
	int i = 0;
	for (type t : range)
	{
		if (i > count)	break;
		if (t == type::get<Window>())
		{
			int x = 0;
			++x;
		}
		auto typeName = t.get_name();
		auto category = t.get_metadata("Category").to_string();
		auto displayName = t.get_metadata("DisplayName").to_string();
		auto description = t.get_metadata("Description").to_string();
		auto p0 = t.get_metadata(1);
		if (p0.is_valid())
		{
			//auto p = p0.get_value<DependencyProperty>();
		}
		auto &cClass = infos[i];
		strcpy(cClass.typeName, typeName.data());
		strcpy(cClass.category, category.data());
		strcpy(cClass.displayName, displayName.data());
		strcpy(cClass.description, description.data());

		auto propertyLimit = sizeof(CClassInfo::propertys) / sizeof(CPropertyInfo);
		std::vector<DependencyPropertyPtr> dps;
		DependencyProperty::getTypePropertys(t, dps);
		for (decltype(propertyLimit) j = 0; j < propertyLimit; ++j)
		{
			auto &cProperty = cClass.propertys[j];
			if (j < dps.size())
			{
				auto sdkProperty = dps[j];
				cProperty.type = sdkProperty->propertyType().get_id();
				strcpy(cProperty.category, sdkProperty->defaultMetadata()->category()->name().data());
				strcpy(cProperty.displayName, sdkProperty->name().data());
				strcpy(cProperty.description, sdkProperty->defaultMetadata()->description().data());
				cProperty.valueType = sdkProperty->propertyType().get_id();
				if(sdkProperty->propertyType().is_enumeration())
					strcpy(cProperty.extra, "a|b");
			}
			else
			{
				cProperty.type = 0;
				strcpy(cProperty.category, "");
				strcpy(cProperty.displayName, "");
				strcpy(cProperty.description, "");
				cProperty.valueType = -1;
				strcpy(cProperty.extra, "");
			}
		}
		++i;
	}
}
