#pragma once
#include "newbrush/gui/Panel.h"

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
	NB_OBJECT
public:
	static constexpr const char *AttachedPropertyDock = "DockPanel.Dock";

	DockPanel();
	virtual ~DockPanel() = default;

	void setDock(std::shared_ptr<UIElement> element, DockE dock);
	DockE getDock(std::shared_ptr<UIElement> element);

	static DependencyProperty	LastChildFillProperty();	//ĩԪ����������������

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
};

}