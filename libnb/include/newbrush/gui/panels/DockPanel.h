#pragma once
#include "newbrush/gui/panels/Panel.h"

namespace nb{

enum class DockE
{
	Left,
	Right,
	Top,
	Bottom,
};

class NB_API DockPanel : public Panel
{
	RTTR_ENABLE(Panel)
public:
	DockPanel() = default;
	virtual ~DockPanel() = default;

	static DependencyPropertyPtr DockProperty();			//Ä©ÔªËØÌîÂúµÄÒÀÀµÊôĞÔ
	static DependencyPropertyPtr LastChildFillProperty();	//Ä©ÔªËØÌîÂúµÄÒÀÀµÊôĞÔ

	static void setDock(UIElementPtr element, DockE dock);
	static DockE getDock(UIElementPtr element);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
};

}