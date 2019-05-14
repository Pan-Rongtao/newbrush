#pragma once
#include "../gui/Panel.h"

namespace nb{namespace gui{

enum class DockE
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

	void setDock(std::shared_ptr<UIElement> element, DockE dock);
	DockE getDock(std::shared_ptr<UIElement> element);

	nb::core::Property_rw<bool>		LastChildFill;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;
};

}}