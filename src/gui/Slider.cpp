#include "newbrush/gui/Slider.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

Slider::Slider()
{
}

Size Slider::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Slider::arrangeOverride(const Size & finalSize)
{
	return Size();
}

std::shared_ptr<MetaObject> Slider::getMetaObject()
{
	auto meta = MetaObject::get<Slider, RangeBase>("控件", "Slider", "滑动条，可拖动交互的范围数值控制组件。", [] {return std::make_shared<Slider>(); });
	return meta;
}
