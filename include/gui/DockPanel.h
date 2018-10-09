#pragma once
#include "../gui/Panel.h"

namespace nb{namespace gui{

enum Dock
{
	Left,
	Right,
	Top,
	Bottom,
};

class DockPanel : public Panel
{
public:
	DockPanel();
	virtual ~DockPanel();

	void setDock(std::shared_ptr<UIElement> element, Dock dock);
	Dock getDock(std::shared_ptr<UIElement> element);

public:
	nb::core::Property_rw<bool>		LastChildFill;

};

}}