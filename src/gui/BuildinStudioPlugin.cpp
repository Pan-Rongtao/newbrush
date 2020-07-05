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
	RttrRegistration::doRegister();
	return PropertyCategory::getAll().size();
}

NB_API void nb::getCategoryOrders(CCategoryOrder * categorys, int count)
{
	RttrRegistration::doRegister();
	auto const &allPropertyCategorys = PropertyCategory::getAll();
	int i = 0;
	for (const auto &pair : allPropertyCategorys)
	{
		if (i >= count)	break;

		auto &c = categorys[i++];
		auto const &pc = pair.second;
		strcpy(c.name, pc.name().data());
		c.order = pc.order();
	}
}

ClassDescriptorPtr getClassDescriptor(type t)
{
	auto vCD = t.get_metadata(RttrMetadataIndex::ClassDescriptor);
	return vCD.is_type<ClassDescriptorPtr>() ? vCD.get_value<ClassDescriptorPtr>() : nullptr;
}

NB_API int nb::getMetaClassCount()
{
	RttrRegistration::doRegister();
	array_range<type> range = type::get_types();
	auto count = std::count_if(range.begin(), range.end(), [](type t)->bool { return getClassDescriptor(t) != nullptr; });
	return count;
}

constexpr size_t PropertyLimit = sizeof(CClass::propertys) / sizeof(CProperty);
NB_API void nb::getMetaClasses(CClass * classes, int count)
{
	RttrRegistration::doRegister();
	array_range<type> range = type::get_types();
	int i = 0;
	for (type t : range)
	{
		if (i > count)
		{
			break;
		}

		//类信息（没有则表示不需要展示在STUDIO中）
		auto vCD = t.get_metadata(RttrMetadataIndex::ClassDescriptor);
		if (!vCD.is_valid())
		{
			continue;
		}

		auto &cc = classes[i];
		if (vCD.is_type<ClassDescriptorPtr>())
		{
			auto classDescriptor = vCD.get_value<ClassDescriptorPtr>();
			std::string category = classDescriptor ? classDescriptor->category() : "";
			std::string displayName = classDescriptor ? classDescriptor->displayName() : "";
			std::string description = classDescriptor ? classDescriptor->description() : "";

			strcpy(cc.typeName, t.get_name().data());
			strcpy(cc.category, category.data());
			strcpy(cc.displayName, displayName.data());
			strcpy(cc.description, description.data());
		}
		else 
		{
			Log::debug("metadata of [%s] must be set as [ClassDescriptorPtr] type", t.get_name());
		}

		//属性信息
		auto const &allPropertyDescriptors = RttrRegistration::getTypeAllPropertys(t);
		if (allPropertyDescriptors.size() > PropertyLimit)
		{
			Log::warn("[%s]'s property count is overfollow property count limit[%d]", t.get_name().data(), PropertyLimit);
		}

		for (size_t j = 0; j < allPropertyDescriptors.size() && j < PropertyLimit; ++j)
		{
			auto &cProperty = cc.propertys[j];
			auto propertyDescriptor = allPropertyDescriptors[j];
			auto sdkProperty = propertyDescriptor->property();

			cProperty.typeID = propertyDescriptor->property()->globalIndex();
			strcpy(cProperty.valueTypeName, sdkProperty->propertyType().get_name().data());
			strcpy(cProperty.category, propertyDescriptor->category().name().data());
			strcpy(cProperty.displayName, sdkProperty->name().data());
			cProperty.order = propertyDescriptor->order();
			strcpy(cProperty.description, propertyDescriptor->description().data());

			if (sdkProperty->propertyType().is_enumeration())
			{
				enumeration e = sdkProperty->propertyType().get_enumeration();
				if (!e.is_valid())
				{
					Log::warn("[%s] is not register for rttr.", sdkProperty->propertyType().get_name().data());
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
