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

//NB_PLUGIN_ENTRY_FOR_STUDIO(BuildinStudioPlugin)
extern "C" NB_API int getMetaClassesCount()
{
//	return 1;
	BuildinStudioPlugin plugin;
	std::vector<std::shared_ptr<MetaObject>> metaObjects; 
	plugin.getMetametaObjectsOverride(metaObjects); 
	return metaObjects.size(); 
}

extern "C" NB_API void getMetaClasses(CClassInfo *infos, int count)
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
			}
			else
			{
				cProperty.type = 0;
				strcpy(cProperty.category, "");
				strcpy(cProperty.displayName, "");
				strcpy(cProperty.description, "");
			}
		}
	}
}