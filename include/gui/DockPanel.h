#pragma once
#include "../gui/Panel.h"

namespace nb{
namespace gui{

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

	static DependencyProperty	LastChildFillProperty();	//Ä©ÔªËØÌîÂúµÄÒÀÀµÊôĞÔ

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
};

}}