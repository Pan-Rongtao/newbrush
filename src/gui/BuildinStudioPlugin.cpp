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
#include "newbrush/gui/RttrRegistration.h"
#include "newbrush/core/Log.h"

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
	auto count = std::count_if(range.begin(), range.end(), [](type t)->bool {
		var vAsVisual = t.get_metadata(RttrClassMetadataIndex::AsVisual);
		bool asVisual = vAsVisual.is_type<bool>() ? vAsVisual.get_value<bool>() : false;
		return asVisual;
	});
	return count;
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

		//class info
		auto typeName = t.get_name();
		var vAsVisual = t.get_metadata(RttrClassMetadataIndex::AsVisual);
		if (!vAsVisual.is_valid())
			continue;
		var vCategory = t.get_metadata(RttrClassMetadataIndex::Category);
		var vDisplayName = t.get_metadata(RttrClassMetadataIndex::DisplayName);
		var vDescription = t.get_metadata(RttrClassMetadataIndex::Description);

		if (!vAsVisual.is_type<bool>())				Log::debug("metadata of [%s] must be set as [bool] type", t.get_name());
		if (!vCategory.is_type<std::string>())		Log::debug("metadata of [%s] must be set as [std::string] type", t.get_name());
		if (!vDisplayName.is_type<std::string>())	Log::debug("metadata of [%s] must be set as [std::string] type", t.get_name());
		if (!vDescription.is_type<std::string>())	Log::debug("metadata of [%s] must be set as [std::string] type", t.get_name());

		bool asVisual = vAsVisual.is_type<bool>() ? vAsVisual.get_value<bool>() : false;
		std::string category = vCategory.is_type<std::string>() ? vCategory.get_value<std::string>() : "";
		std::string displayName = vDisplayName.is_type<std::string>() ? vDisplayName.get_value<std::string>() : "";
		std::string description = vDescription.is_type<std::string>() ? vDescription.get_value<std::string>() : "";


		auto &cClass = infos[i];
		strcpy(cClass.typeName, typeName.data());
		strcpy(cClass.category, category.data());
		strcpy(cClass.displayName, displayName.data());
		strcpy(cClass.description, description.data());

		//properties info
		auto propertyLimit = sizeof(CClassInfo::propertys) / sizeof(CPropertyInfo);
		std::vector<std::shared_ptr<DependencyProperty>> allProperties = RttrRegistration::getTypeAllPropertys(t);
		if (allProperties.size() > propertyLimit)
		{
			Log::warn("[%s]'s property count is overfollow property count limit[%d]", t.get_name().data(), propertyLimit);
		}

		for (size_t j = 0; j < allProperties.size() && j < propertyLimit; ++j)
		{
			auto &cProperty = cClass.propertys[j];
			auto p = allProperties[j];
			auto propertyMeta = p->defaultMetadata();
			cProperty.typeID = p->globalIndex();
			strcpy(cProperty.valueTypeName, p->propertyType().get_name().data());
			strcpy(cProperty.category, propertyMeta->category() ? propertyMeta->category()->name().data() : "");
			strcpy(cProperty.displayName, p->name().data());
			strcpy(cProperty.description, propertyMeta->category() ? propertyMeta->description().data() : "");
			if (p->propertyType().is_enumeration())
			{
				enumeration e = p->propertyType().get_enumeration();
				if (!e.is_valid())
				{
					Log::warn("[%s] is not register for rttr.", p->propertyType().get_name().data());
				}
				std::string enumSource;
				auto r = e.get_names();
				for (string_view name : r)
				{
					enumSource = enumSource + name.to_string() + "|";
				}
				if (!enumSource.empty())
				{
					enumSource.pop_back();
				}
				strcpy(cProperty.enumSource, enumSource.data());
			}
		}
		++i;
	}
}
