#pragma once
#include "../gui/Panel.h"

namespace nb{ namespace gui{

enum class DockE
{
	Left,
	Right,
	Top,
	Bottom,
};

class NB_API DockPanel : public Panel
{
public:
	static constexpr const char *AttachedPropertyDock = "DockPanel.Dock";

	DockPanel();
	virtual ~DockPanel() = default;

	void setDock(std::shared_ptr<UIElement> element, DockE dock);
	DockE getDock(std::shared_ptr<UIElement> element);

	Property_rw<bool>				LastChildFill;

	static const DependencyProperty	LastChildFillProperty();

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;
};

}}