#pragma once
#include "../core/Def.h"
#include "../core/Property.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"
#include "../gles/RenderObject.h"
#include "../gui/AnimationTimeline.h"
#include "gui/DependencyProperty.h"
#include "gui/Style.h"
#include "gui/VisualStateMachine.h"

namespace nb{ namespace gl{
	class Context;
}}

namespace nb{namespace gui{

enum class VisibilityE
{
	Hidden,
	Visible,
	Collapsed,
};

enum class HorizontalAlignmentE
{
	Left,
	Center,
	Right,
	Stretch,
};

enum class VerticalAlignmentE
{
	Top,
	Center,
	Bottom,
	Stretch,
};

enum class FlowDirectionE
{
	LeftToRight,
	RightToLeft,
};

enum class OrientationE
{
	Horizontal,
	Vertical,
};

class NB_API UIElement : public std::enable_shared_from_this<UIElement>
{
public:
	UIElement();
	virtual ~UIElement();

	uint32_t childCount() const;
	void addChild(std::shared_ptr<UIElement> child);
	void insertChild(uint32_t index, std::shared_ptr<UIElement> child);
	void removeChild(std::shared_ptr<UIElement> child);
	void removeChild(uint32_t index, uint32_t count = 1);
	void clearChild();
	std::shared_ptr<UIElement> childAt(uint32_t index);
	bool containsChild(std::shared_ptr<UIElement> element) const;

	std::shared_ptr<UIElement> getRoot();
	core::Point worldOffset();
	void updateLayout();

	void measure(const core::Size &availabelSize);
	void arrage(const core::Rect &finalRect);
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext);


public:
	core::Property_rw<VisibilityE>							Visibility;
	core::Property_rw<float>								Opacity;
	core::Property_rw<bool>									Focusable;
	core::Property_rw<float>								Width;
	core::Property_rw<float>								Height;
	core::Property_rw<float>								MinWidth;
	core::Property_rw<float>								MinHeight;
	core::Property_rw<float>								MaxWidth;
	core::Property_rw<float>								MaxHeight;
	core::Property_r<core::Size>							DesiredSize;
	core::Property_r<core::Size>							ActualSize;
	core::Property_rw<core::Size>							RenderSize;
	core::Property_rw<core::Point>							Offset;
	core::Property_rw<Thickness>							Margin;
	core::Property_rw<HorizontalAlignmentE>					HorizontalAlignment;
	core::Property_rw<VerticalAlignmentE>					VerticalAlignment;
	core::Property_rw<FlowDirectionE>						FlowDirection;
//	core::Property_r<std::shared_ptr<UIElement>>			Parent;
	core::Property_r<std::shared_ptr<gl::RenderObject>>		Renderer;
	core::Property_rw<std::shared_ptr<Style>>				style;
	core::Property_rw<std::shared_ptr<VisualStateMachine>>	StateMachine;

	struct MouseEnterArgs {}; core::Event<MouseEnterArgs>	MouseEnter;
	struct MouseLeaveArgs {}; core::Event<MouseLeaveArgs>	MouseLeave;
	struct MouseDownArgs {}; core::Event<MouseDownArgs>		MouseDown;
	struct MouseUpArgs {}; core::Event<MouseUpArgs>			MouseUp;
	struct MouseLeftButtonDownArgs {}; core::Event<MouseLeftButtonDownArgs>		MouseLeftButtonDown;
	struct MouseLeftButtonUpArgs {}; core::Event<MouseLeftButtonUpArgs>			MouseLeftButtonUp;
	struct MouseRightButtonDownArgs {}; core::Event<MouseRightButtonDownArgs>	MouseRightButtonDown;
	struct MouseRightButtonUpArgs {}; core::Event<MouseRightButtonUpArgs>		MouseRightButtonUp;
	struct MouseWheelArgs {}; core::Event<MouseWheelArgs>						MouseWheel;
	
public:
	virtual core::Size measureOverride(const core::Size &availableSize);
	virtual core::Size arrangeOverride(const core::Size &finalSize);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void onMouseLeftButtonDown();
	virtual void onMouseLeftButtonUp();
	virtual void onMouseRightButtonDown();
	virtual void onMouseRightButtonUp();
	virtual void onMouseMove();
	virtual void onMouseWheel(int delta);

protected:
	std::shared_ptr<UIElement>								m_parent;
	std::vector<std::shared_ptr<UIElement>>					m_children;

private:
	nb::core::Size											m_desiredSize;
	nb::core::Size											m_actualSize;
	std::shared_ptr<gl::RenderObject>						m_renderer;
};

}
}
