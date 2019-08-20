#pragma once
#include "../core/Def.h"
#include "../core/Property.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"
#include "../gles/RenderObject.h"
#include "../gui/AnimationTimeline.h"
#include "gui/DependencyObject.h"
#include "gui/Style.h"
#include "gui/VisualStateMachine.h"

namespace nb{ namespace gl{
	class Context;
}}

namespace nb{namespace gui{

using std::shared_ptr;

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

class NB_API UIElement : public DependencyObject, public std::enable_shared_from_this<UIElement>
{
public:
	UIElement();
	virtual ~UIElement() = default;

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
	core::Property_r<shared_ptr<gl::RenderObject>>			Renderer;
	core::Property_rw<shared_ptr<Style>>					style;
	//core::Property_rw<shared_ptr<VisualStateMachine>>		StateMachine;

	static const DependencyProperty							VisibilityProperty();
	static const DependencyProperty							OpacityProperty();
	static const DependencyProperty							FocusableProperty();
	static const DependencyProperty 						WidthProperty();
	static const DependencyProperty 						HeightProperty();
	static const DependencyProperty 						MinWidthProperty();
	static const DependencyProperty 						MinHeightProperty();
	static const DependencyProperty 						MaxWidthProperty();
	static const DependencyProperty 						MaxHeightProperty();
	static const DependencyProperty 						DesiredSizeProperty();
	static const DependencyProperty 						ActualSizeProperty();
	static const DependencyProperty 						RenderSizeProperty();
	static const DependencyProperty 						OffsetProperty();
	static const DependencyProperty 						MarginProperty();
	static const DependencyProperty 						HorizontalAlignmentProperty();
	static const DependencyProperty 						VerticalAlignmentProperty();
	static const DependencyProperty 						FlowDirectionProperty();
	static const DependencyProperty 						RendererProperty();
	static const DependencyProperty 						StyleProperty();
	static const DependencyProperty 						StateMachineProperty();

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

	
	struct MouseEnterArgs {};
	core::Event<MouseEnterArgs>								MouseEnter;

	struct MouseLeaveArgs {};
	core::Event<MouseLeaveArgs>								MouseLeave;

	struct MouseMoveArgs {};
	core::Event<MouseMoveArgs>								MouseMove;

	struct MouseDownArgs {};
	core::Event<MouseDownArgs>								MouseDown;

	struct MouseUpArgs {};
	core::Event<MouseUpArgs>								MouseUp;

	struct MouseLeftButtonDownArgs {};
	core::Event<MouseLeftButtonDownArgs>					MouseLeftButtonDown;

	struct MouseLeftButtonUpArgs {}; 
	core::Event<MouseLeftButtonUpArgs>						MouseLeftButtonUp;

	struct MouseRightButtonDownArgs {};
	core::Event<MouseRightButtonDownArgs>					MouseRightButtonDown;

	struct MouseRightButtonUpArgs {};
	core::Event<MouseRightButtonUpArgs>						MouseRightButtonUp;

	struct MouseWheelArgs {};
	core::Event<MouseWheelArgs>								MouseWheel;
	

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
	void onPropertyChanged(const PropertyChangedArg &args);
};

}
}
