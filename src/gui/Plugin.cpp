#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Grid.h"
#include "newbrush/gui/Canvas.h"
#include "newbrush/gui/Rectangle.h"

using namespace nb;

struct Info
{
	char	type[64];
	char	defaultName[64];
	char	description[256];
};

static std::vector<MetaData> getMetaClasses()
{
	std::vector<MetaData> infos;

	infos.push_back(Window::getMetaData());
	infos.push_back(Grid::getMetaData());
	infos.push_back(Canvas::getMetaData());
	infos.push_back(Rectangle::getMetaData());

	return infos;
}

extern "C" _declspec(dllexport) int getClassesCount()
{
	auto metas = getMetaClasses();
	return metas.size();
}

extern "C" _declspec(dllexport) void getEditorInfos(Info *infos, int count)
{
	auto metas = getMetaClasses();
	for (int i = 0; i < count && i < metas.size(); ++i)
	{
		auto m = metas[i];
		strcpy(infos[i].type, nb::getFullName(m.type).data());
		strcpy(infos[i].defaultName, nb::getClassName(m.type).data());
		strcpy(infos[i].description, "this is xxx");
	}
}