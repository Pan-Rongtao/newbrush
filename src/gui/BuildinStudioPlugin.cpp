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

using namespace nb;

std::vector<MetaData> BuildinStudioPlugin::getMetaClassesOverride()
{
	std::vector<MetaData> classes;
	classes.push_back(Canvas::getMetaData());
	classes.push_back(DockPanel::getMetaData());
	classes.push_back(WrapPanel::getMetaData());
	classes.push_back(StackPanel::getMetaData());
	classes.push_back(Grid::getMetaData());
	classes.push_back(UniformGrid::getMetaData());
	classes.push_back(Button::getMetaData());
	classes.push_back(RepeatButton::getMetaData());
	classes.push_back(Window::getMetaData());
	classes.push_back(Line::getMetaData());
	classes.push_back(Polyline::getMetaData());
	classes.push_back(Polygon::getMetaData());
	classes.push_back(Path::getMetaData());
	classes.push_back(Rectangle::getMetaData());
	classes.push_back(Ellipse::getMetaData());
	return classes;
}

NB_PLUGIN_FOR_STUDIO(BuildinStudioPlugin)
