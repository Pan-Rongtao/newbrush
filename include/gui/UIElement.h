#pragma once
#include "../core/Def.h"
#include "../gui/Property.h"
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

	Property_rw<VisibilityE>						Visibility;				//可视
	Property_rw<float>								Opacity;				//不透明度
	Property_rw<bool>								Focusable;				//是否可用焦点
	Property_rw<float>								Width;					//设定宽
	Property_rw<float>								Height;					//设定高
	Property_rw<float>								MinWidth;				//最小宽
	Property_rw<float>								MinHeight;				//最小高
	Property_rw<float>								MaxWidth;				//最大宽
	Property_rw<float>								MaxHeight;				//最大高
	Property_r<Size>								DesiredSize;			//期望尺寸
	Property_r<Size>								ActualSize;				//实际尺寸
	Property_rw<Size>								RenderSize;				//渲染尺寸
	Property_rw<Point>								Offset;					//相对父偏移量
	Property_rw<Thickness>							Margin;					//边缘
	Property_rw<HorizontalAlignmentE>				HorizontalAlignment;	//横向对齐方式
	Property_rw<VerticalAlignmentE>					VerticalAlignment;		//纵向对齐方式
	Property_rw<FlowDirectionE>						FlowDirection;			//
	Property_r<shared_ptr<gl::RenderObject>>		Renderer;				//渲染物
	Property_rw<shared_ptr<Style>>					style;					//风格
	//Property_rw<shared_ptr<VisualStateMachine>>	StateMachine;

	static const DependencyProperty					VisibilityProperty();	//可视的依赖属性
	static const DependencyProperty					OpacityProperty();		//不透明度的依赖属性
	static const DependencyProperty					FocusableProperty();	//是否可用焦点的依赖属性
	static const DependencyProperty 				WidthProperty();		//设定宽的依赖属性
	static const DependencyProperty 				HeightProperty();		//设定高的依赖属性
	static const DependencyProperty 				MinWidthProperty();		//最小宽的依赖属性
	static const DependencyProperty 				MinHeightProperty();	//最小高的依赖属性
	static const DependencyProperty 				MaxWidthProperty();		//最大宽的依赖属性
	static const DependencyProperty 				MaxHeightProperty();	//最大高的依赖属性
	static const DependencyProperty 				DesiredSizeProperty();	//期望尺寸的依赖属性
	static const DependencyProperty 				ActualSizeProperty();	//实际尺寸的依赖属性
	static const DependencyProperty 				RenderSizeProperty();	//渲染尺寸的依赖属性
	static const DependencyProperty 				OffsetProperty();		//相对父偏移量的依赖属性
	static const DependencyProperty 				MarginProperty();		//边缘的依赖属性
	static const DependencyProperty 				HorizontalAlignmentProperty();	//横向对齐方式的依赖属性
	static const DependencyProperty 				VerticalAlignmentProperty();	//纵向对齐方式的依赖属性
	static const DependencyProperty 				FlowDirectionProperty();		//
	static const DependencyProperty 				RendererProperty();		//渲染物的依赖属性
	static const DependencyProperty 				StyleProperty();		//风格的依赖属性
	static const DependencyProperty 				StateMachineProperty();	//状态机的依赖属性

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
	void onPropertyChanged(const PropertyChangedArgs &args);
};

}
}
