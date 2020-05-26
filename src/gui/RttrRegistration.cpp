#include "rttr/registration.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/Log.h"
#include "newbrush/core/Binding.h"

using namespace nb;
using namespace rttr;

//enums
RTTR_REGISTRATION
{
	auto k = nb::getTickCount();

	/////////////////////////Point//////////////////////
	registration::class_<Point>(nb::getClassName(typeid(nb::Point)))
		.constructor<>()(policy::ctor::as_object)
		.constructor<float, float>()(policy::ctor::as_object)
		;
	//////////////////////end Point/////////////////////

	registration::enumeration<BindingModeE>("BindingModeE")
	(
		value("OneTime", BindingModeE::OneTime),
		value("OneWayToTarget", BindingModeE::OneWayToTarget),
		value("OneWayToSource", BindingModeE::OneWayToSource),
		value("TwoWay", BindingModeE::TwoWay)
	);

	registration::enumeration<PropertyCategoryE>("PropertyCategoryE")
	(
		value("画笔", PropertyCategoryE::Brush),
		value("外观", PropertyCategoryE::Appearance),
		value("公共", PropertyCategoryE::Public),
		value("自动化", PropertyCategoryE::Automation),
		value("布局", PropertyCategoryE::Layout),
		value("文本", PropertyCategoryE::Text),
		value("转换", PropertyCategoryE::Transform),
		value("杂项", PropertyCategoryE::Misc),
		value("自定义", PropertyCategoryE::Custom)
	);

	auto types = type::get_types();
	std::vector<type> ts(types.begin(), types.end());
	std::vector<string_view> tNames;
	for (auto const &t : ts)
	{
		tNames.push_back(t.get_name());
	}

	auto kk = nb::getTickCount();
	Log::info("RTTR registration cost [%d] ms.", kk - k);
}
