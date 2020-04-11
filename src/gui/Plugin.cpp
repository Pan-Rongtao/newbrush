#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Grid.h"
#include "newbrush/gui/Canvas.h"

using namespace nb;

struct Info
{
	long long	id;
	char		name[64];
	char		description[256];
};

static std::vector<EditorInfo> getMetaClasses()
{
	std::vector<EditorInfo> infos;

	infos.push_back(Window::getEditorInfo());
	infos.push_back(Grid::getEditorInfo());
	infos.push_back(Canvas::getEditorInfo());

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
		infos[i].id = m.id;
		strcpy(infos[i].name, m.name.data());
		strcpy(infos[i].description, m.description.data());
	}
}