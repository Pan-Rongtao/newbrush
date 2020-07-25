#include "newbrush/core/media/TileBrush.h"
#include "newbrush/core/media/Media.h"
#include "newbrush/core/Rect.h"

using namespace nb;

DependencyPropertyPtr TileBrush::AligmentXProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, AlignmentXE>("AligmentX", AlignmentXE::Center);
	return dp;
}

DependencyPropertyPtr TileBrush::AligmentYProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, AlignmentYE>("AligmentY", AlignmentYE::Center);
	return dp;
}

DependencyPropertyPtr TileBrush::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, StretchE>("Stretch", StretchE::Uniform);
	return dp;
}

DependencyPropertyPtr TileBrush::TileModeProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, TileModeE>("TileMode", TileModeE::None);
	return dp;
}

DependencyPropertyPtr TileBrush::ViewboxProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, Rect>("Viewbox", Rect());
	return dp;
}

DependencyPropertyPtr TileBrush::ViewportProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, Rect>("Viewport", Rect());
	return dp;
}

DependencyPropertyPtr TileBrush::ViewboxUnitsProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, BrushMappingModeE>("ViewboxUnits", BrushMappingModeE::RelativeToBoundingBox);
	return dp;
}

DependencyPropertyPtr TileBrush::ViewportUnitsProperty()
{
	static auto dp = DependencyProperty::registerDependency<TileBrush, BrushMappingModeE>("ViewportUnits", BrushMappingModeE::RelativeToBoundingBox);
	return dp;
}
