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

	Property_rw<VisibilityE>						Visibility;
	Property_rw<float>								Opacity;
	Property_rw<bool>								Focusable;
	Property_rw<float>								Width;
	Property_rw<float>								Height;
	Property_rw<float>								MinWidth;
	Property_rw<float>								MinHeight;
	Property_rw<float>								MaxWidth;
	Property_rw<float>								MaxHeight;
	Property_r<Size>								DesiredSize;
	Property_r<Size>								ActualSize;
	Property_rw<Size>								RenderSize;
	Property_rw<Point>								Offset;
	Property_rw<Thickness>							Margin;
	Property_rw<HorizontalAlignmentE>				HorizontalAlignment;
	Property_rw<VerticalAlignmentE>					VerticalAlignment;
	Property_rw<FlowDirectionE>						FlowDirection;
	Property_r<shared_ptr<gl::RenderObject>>		Renderer;
	Property_rw<shared_ptr<Style>>					style;
	//Property_rw<shared_ptr<VisualStateMachine>>	StateMachine;

	static const DependencyProperty					VisibilityProperty();
	static const DependencyProperty					OpacityProperty();
	static const DependencyProperty					FocusableProperty();
	static const DependencyProperty 				WidthProperty();
	static const DependencyProperty 				HeightProperty();
	static const DependencyProperty 				MinWidthProperty();
	static const DependencyProperty 				MinHeightProperty();
	static const DependencyProperty 				MaxWidthProperty();
	static const DependencyProperty 				MaxHeightProperty();
	static const DependencyProperty 				DesiredSizeProperty();
	static const DependencyProperty 				ActualSizeProperty();
	static const DependencyProperty 				RenderSizeProperty();
	static const DependencyProperty 				OffsetProperty();
	static const DependencyProperty 				MarginProperty();
	static const DependencyProperty 				HorizontalAlignmentProperty();
	static const DependencyProperty 				VerticalAlignmentProperty();
	static const DependencyProperty 				FlowDirectionProperty();
	static const DependencyProperty 				RendererProperty();
	static const DependencyProperty 				StyleProperty();
	static const DependencyProperty 				StateMachineProperty();

	uint32_t childCount() const;
	void addChild(std::shared_ptr<UIElement> child);
	void insertChild(uint32_t index, std::shared_ptr<UIElement> child);
	void removeChild(std::shared_ptr<UIElement> child);
	void removeChild(uint32_t index, uint32_t count = 1);
	void clearChild();
	std::shared_ptr<UIElement> childAt(uint32_t index);
	bool containsChild(std::shared_ptr<UIElement> element) const;

	std::shared_ptr<UIElement> getRoot();
	Point worldOffset();
	void updateLayout();

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext);

	
	struct MouseEnterArgs {};
	Event<MouseEnterArgs>							MouseEnter;

	struct MouseLeaveArgs {};
	Event<MouseLeaveArgs>							MouseLeave;

	struct MouseMoveArgs {};
	Event<MouseMoveArgs>							MouseMove;

	struct MouseDownArgs {};
	Event<MouseDownArgs>							MouseDown;

	struct MouseUpArgs {};
	Event<MouseUpArgs>								MouseUp;

	struct MouseLeftButtonDownArgs {};
	Event<MouseLeftButtonDownArgs>					MouseLeftButtonDown;

	struct MouseLeftButtonUpArgs {}; 
	Event<MouseLeftButtonUpArgs>					MouseLeftButtonUp;

	struct MouseRightButtonDownArgs {};
	Event<MouseRightButtonDownArgs>					MouseRightButtonDown;

	struct MouseRightButtonUpArgs {};
	Event<MouseRightButtonUpArgs>					MouseRightButtonUp;

	struct MouseWheelArgs {};
	Event<MouseWheelArgs>							MouseWheel;
	

public:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);
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
