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
using namespace rttr;

void BuildinStudioPlugin::getMetametaObjectsOverride()
{
}

NB_API int nb::getCategoryOrderCount()
{
	auto const &allPropertyCategorys = PropertyCategory::getAll();
	return allPropertyCategorys.size();
}

NB_API void nb::getCategoryOrders(CCategoryOrder * categorys, int count)
{
	auto const &allPropertyCategorys = PropertyCategory::getAll();
	int i = 0;
	for (const auto &pair : allPropertyCategorys)
	{
		if (i >= count)	break;

		auto &c = categorys[i++];
		auto const &pc = pair.second;
		strcpy(c.name, pc->name().data());
		c.order = pc->order();
	}
}

NB_API int nb::getMetaObjectCount()
{
	array_range<type> range = type::get_types();
	auto count = std::count_if(range.begin(), range.end(), [](type t)->bool {
		var vAsVisual = t.get_metadata(RttrClassMetadataIndex::AsVisual);
		bool asVisual = vAsVisual.is_type<bool>() ? vAsVisual.get_value<bool>() : false;
		return asVisual;
	});
	return count;
}

NB_API void nb::getMetaObjects(CClass * classes, int count)
{
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


		auto &cc = classes[i];
		strcpy(cc.typeName, typeName.data());
		strcpy(cc.category, category.data());
		strcpy(cc.displayName, displayName.data());
		strcpy(cc.description, description.data());

		//properties info
		auto propertyLimit = sizeof(CClass::propertys) / sizeof(CProperty);
		std::vector<std::shared_ptr<DependencyProperty>> allProperties = RttrRegistration::getTypeAllPropertys(t);
		if (allProperties.size() > propertyLimit)
		{
			Log::warn("[%s]'s property count is overfollow property count limit[%d]", t.get_name().data(), propertyLimit);
		}

		for (size_t j = 0; j < allProperties.size() && j < propertyLimit; ++j)
		{
			auto &cProperty = cc.propertys[j];
			auto p = allProperties[j];
			auto propertyMeta = p->defaultMetadata();
			cProperty.typeID = p->globalIndex();
			strcpy(cProperty.valueTypeName, p->propertyType().get_name().data());
			strcpy(cProperty.category, propertyMeta->category() ? propertyMeta->category()->name().data() : "");
			cProperty.categoryOrder = propertyMeta->category() ? propertyMeta->category()->order() : INT_MAX;
			strcpy(cProperty.displayName, p->name().data());
			cProperty.order = propertyMeta->order();
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
