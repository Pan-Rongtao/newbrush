#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Size.h"
#include "newbrush/core/Rect.h"
#include "newbrush/media/Thickness.h"
#include "newbrush/core/RoutedEvent.h"

namespace nb{
class Viewport2D;

enum class VisibilityE
{
	Hidden,		//不要显示的元素，但是，保留空间中的元素格式（参与排版策略等）
	Visible,	//显示组件
	Collapsed,	//不要显示元素，并且不希望它的保留空间
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

class Style;
class Transform;
class VisualStateMachine;
class UIElement;
class RoutedEventArgs;
using StylePtr = std::shared_ptr<Style>;
using TransformPtr = std::shared_ptr<Transform>;
using UIElementPtr = std::shared_ptr<UIElement>;
using RoutedEventArgsPtr = std::shared_ptr<RoutedEventArgs>;
using VisualStateMachinePtr = std::shared_ptr<VisualStateMachine>;

class NB_API UIElement : public DependencyObject
{
	RTTR_ENABLE(DependencyObject)
public:
	UIElement();
	virtual ~UIElement() = default;

	static DependencyPropertyPtr NameProperty();		//可视的依赖属性（string）
	static DependencyPropertyPtr VisibilityProperty();	//可视的依赖属性（bool）
	static DependencyPropertyPtr OpacityProperty();		//不透明度的依赖属性（float）
	static DependencyPropertyPtr FocusableProperty();	//是否可用焦点的依赖属性（bool）
	static DependencyPropertyPtr IsFocusedProperty();	//元素当前是否具有焦点的依赖属性（bool）只读
	static DependencyPropertyPtr WidthProperty();		//设定宽的依赖属性（float）
	static DependencyPropertyPtr HeightProperty();		//设定高的依赖属性（float）
	static DependencyPropertyPtr MinWidthProperty();	//最小宽的依赖属性（float）
	static DependencyPropertyPtr MinHeightProperty();	//最小高的依赖属性（float）
	static DependencyPropertyPtr MaxWidthProperty();	//最大宽的依赖属性（float）
	static DependencyPropertyPtr MaxHeightProperty();	//最大高的依赖属性（float）
	static DependencyPropertyPtr ActualSizeProperty();	//实际尺寸的依赖属性（Size）只读
	static DependencyPropertyPtr MarginProperty();		//边缘的依赖属性（Thickness）
	static DependencyPropertyPtr HorizontalAlignmentProperty();	//横向对齐方式的依赖属性（HorizontalAlignmentE）
	static DependencyPropertyPtr VerticalAlignmentProperty();	//纵向对齐方式的依赖属性（VerticalAlignmentE）
	static DependencyPropertyPtr FlowDirectionProperty();		//流向的依赖属性（FlowDirectionE）
	static DependencyPropertyPtr StyleProperty();				//风格的依赖属性（StylePtr)
	static DependencyPropertyPtr StateMachineProperty();		//状态机的依赖属性（VisualStateMachinePtr）
	static DependencyPropertyPtr IsMouseOverProperty();			//鼠标是否在元素上（bool）只读
	static DependencyPropertyPtr RenderTransformProperty();		//变换的依赖属性(std::make_shared<Transform>())

	Event<EventArgs>							Initialized;
	Event<RoutedEventArgs>						Loaded;
	Event<RoutedEventArgs>						Unloaded;
	Event<SizeChangedEventArgs>					SizeChanged;

	Event<DependencyPropertyChangedEventArgs>	IsEnableChanged;
	Event<DependencyPropertyChangedEventArgs>	IsHitTestVisibleChanged;
	Event<DependencyPropertyChangedEventArgs>	IsVisibleChanged;
	Event<EventArgs>							LayoutUpdated;
	Event<MouseEventArgs>						GotMouseCapture;
	Event<MouseEventArgs>						LostMouseCapture;
	Event<TouchEventArgs>						GotTouchCapture;
	Event<TouchEventArgs>						LostTouchCapture;
	Event<DependencyPropertyChangedEventArgs>	FocusableChanged;
	Event<RoutedEventArgs>						LostFocus;
	Event<RoutedEventArgs>						GotFocus;
	Event<DragEventArgs>						PreviewDragEnter;
	Event<DragEventArgs>						DragEnter;
	Event<DragEventArgs>						PreviewDragLeave;
	Event<DragEventArgs>						DragLeave;
	Event<DragEventArgs>						PreviewDragOver;
	Event<DragEventArgs>						DragOver;
	Event<DragEventArgs>						PreviewDrop;
	Event<DragEventArgs>						Drop;
	Event<DependencyPropertyChangedEventArgs>	IsKeyboardFocusedChanged;
	Event<KeyboardFocusChangedEventArgs>		PreviewGotKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		GotKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		PreviewLostKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		LostKeyboardFocus;
	Event<KeyEventArgs>							PreviewKeyDown;
	Event<KeyEventArgs>							KeyDown;
	Event<KeyEventArgs>							PreviewKeyUp;
	Event<KeyEventArgs>							KeyUp;
	Event<MouseEventArgs>						MouseEnter;
	Event<MouseEventArgs>						MouseLeave;
	Event<MouseButtonEventArgs>					PreviewMouseDown;
	Event<MouseButtonEventArgs>					MouseDown;
	Event<MouseButtonEventArgs>					PreviewMouseLeftButtonDown;
	Event<MouseButtonEventArgs>					MouseLeftButtonDown;
	Event<MouseButtonEventArgs>					PreviewMouseLeftButtonUp;
	Event<MouseButtonEventArgs>					MouseLeftButtonUp;
	Event<MouseEventArgs>						PreviewMouseMove;
	Event<MouseEventArgs>						MouseMove;
	Event<MouseButtonEventArgs>					PreviewMouseRightButtonDown;
	Event<MouseButtonEventArgs>					MouseRightButtonDown;
	Event<MouseButtonEventArgs>					PreviewMouseRightButtonUp;
	Event<MouseButtonEventArgs>					MouseRightButtonUp;
	Event<MouseButtonEventArgs>					PreviewMouseUp;
	Event<MouseButtonEventArgs>					MouseUp;
	Event<MouseWheelEventArgs>					PreviewMouseWheel;
	Event<MouseWheelEventArgs>					MouseWheel;
	Event<TouchEventArgs>						PreviewTouchEnter;
	Event<TouchEventArgs>						TouchEnter;
	Event<TouchEventArgs>						PreviewTouchLeave;
	Event<TouchEventArgs>						TouchLeave;
	Event<TouchEventArgs>						PreviewTouchDown;
	Event<TouchEventArgs>						TouchDown;
	Event<TouchEventArgs>						PreviewTouchMove;
	Event<TouchEventArgs>						TouchMove;
	Event<TouchEventArgs>						PreviewTouchUp;
	Event<TouchEventArgs>						TouchUp;

	static RoutedEvent							LoadedEvent();
	static RoutedEvent							UnloadedEvent();
	static RoutedEvent							SizeChangedEvent();
	static RoutedEvent							DragEnterEvent();
	static RoutedEvent							DragLeaveEvent();
	static RoutedEvent							DragOverEvent();
	static RoutedEvent							DropEvent();
	static RoutedEvent							GotFocusEvent();
	static RoutedEvent							GotKeyboardFocusEvent();
	static RoutedEvent							GotMouseCaptureEvent();
	static RoutedEvent							KeyDownEvent();
	static RoutedEvent							KeyUpEvent();
	static RoutedEvent							LostFocusEvent();
	static RoutedEvent							LostKeyboardFocusEvent();
	static RoutedEvent							LostMouseCaptureEvent();
	static RoutedEvent							LostTouchCaptureEvent();
	static RoutedEvent							MouseDownEvent();
	static RoutedEvent							MouseEnterEvent();
	static RoutedEvent							MouseLeaveEvent();
	static RoutedEvent							MouseLeftButtonDownEvent();
	static RoutedEvent							MouseLeftButtonUpEvent();
	static RoutedEvent							MouseMoveEvent();
	static RoutedEvent							MouseRightButtonDownEvent();
	static RoutedEvent							MouseRightButtonUpEvent();
	static RoutedEvent							MouseUpEvent();
	static RoutedEvent							MouseWheelEvent();
	static RoutedEvent							PreviewDragEnterEvent();
	static RoutedEvent							PreviewDragLeaveEvent();
	static RoutedEvent							PreviewDragOverEvent();
	static RoutedEvent							PreviewDropEvent();
	static RoutedEvent							PreviewGotKeyboardFocusEvent();
	static RoutedEvent							PreviewKeyDownEvent();
	static RoutedEvent							PreviewKeyUpEvent();
	static RoutedEvent							PreviewLostKeyboardFocusEvent();
	static RoutedEvent							PreviewMouseDownEvent();
	static RoutedEvent							PreviewMouseLeftButtonDownEvent();
	static RoutedEvent							PreviewMouseLeftButtonUpEvent();
	static RoutedEvent							PreviewMouseMoveEvent();
	static RoutedEvent							PreviewMouseRightButtonDownEvent();
	static RoutedEvent							PreviewMouseRightButtonUpEvent();
	static RoutedEvent							PreviewMouseUpEvent();
	static RoutedEvent							PreviewMouseWheelEvent();
	static RoutedEvent							PreviewTouchDownEvent();
	static RoutedEvent							PreviewTouchMoveEvent();
	static RoutedEvent							PreviewTouchUpEvent();
	static RoutedEvent							TouchDownEvent();
	static RoutedEvent							TouchEnterEvent();
	static RoutedEvent							TouchLeaveEvent();
	static RoutedEvent							TouchMoveEvent();
	static RoutedEvent							TouchUpEvent();

	const Size &desiredSize() const;

	virtual UIElementPtr clone() const;

	//获取子节点个数，本实现返回0
	virtual uint32_t childrenCount() const;

	//获取子节点，本实现抛出std::out_of_range
	virtual UIElement *getChild(uint32_t index);

	void setParent(UIElement *element);
	UIElement *getParent();

	UIElement *getRoot();
	Point worldOffset() const;
	void updateLayout();

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);
	virtual void onRender(Viewport2D & drawContext);
	
	void addHandler(const RoutedEvent &event, const RoutedEventHandler &handler);
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler &handler);
	void raiseEvent(RoutedEventArgsPtr args);
	
	virtual bool hitTestCore(const Point &pt) const;
	
public:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);

protected:
	void addLogicalChild(UIElementPtr child);
	void removeLogicalChild(UIElementPtr child);

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual void onStyleChanged(StylePtr oldStyle, StylePtr newStyle);

	virtual void onDragEnter(const DragEventArgs &args);
	virtual void onDragLeave(const DragEventArgs &args);
	virtual void onDragOver(const DragEventArgs &args);
	virtual void onDrop(const DragEventArgs &args);
	virtual void onGotFocus(const RoutedEventArgs &args);
	virtual void onGotKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onGotMouseCapture(const MouseEventArgs &args);
	virtual void onGotTouchCapture(const TouchEventArgs &args);
	virtual void onKeyDown(const KeyEventArgs &args);
	virtual void onKeyUp(const KeyEventArgs &args);
	virtual void onLostFocus(const RoutedEventArgs &args);
	virtual void onLostKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onLostMouseCapture(const MouseEventArgs &args);
	virtual void onLostTouchCapture(const TouchEventArgs &args);
	virtual void onMouseEnter(const MouseEventArgs &args);
	virtual void onMouseLeave(const MouseEventArgs &args);
	virtual void onMouseDown(const MouseButtonEventArgs &args);
	virtual void onMouseUp(const MouseButtonEventArgs &args);
	virtual void onMouseLeftButtonDown(const MouseButtonEventArgs &args);
	virtual void onMouseLeftButtonUp(const MouseButtonEventArgs &args);
	virtual void onMouseRightButtonDown(const MouseButtonEventArgs &args);
	virtual void onMouseRightButtonUp(const MouseButtonEventArgs &args);
	virtual void onMouseMove(const MouseEventArgs &args);
	virtual void onMouseWheel(const MouseWheelEventArgs &args);
	virtual void onTouchDown(const TouchEventArgs &args);
	virtual void onTouchEnter(const TouchEventArgs &args);
	virtual void onTouchLeave(const TouchEventArgs &args);
	virtual void onTouchMove(const TouchEventArgs &args);
	virtual void onTouchUp(const TouchEventArgs &args);
	//preview
	virtual void onPreviewDragEnter(const DragEventArgs &args);
	virtual void onPreviewDragLeave(const DragEventArgs &args);
	virtual void onPreviewDragOver(const DragEventArgs &args);
	virtual void onPreviewDrop(const DragEventArgs &args);
	virtual void onPreviewGotKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onPreviewKeyDown(const KeyEventArgs &args);
	virtual void onPreviewKeyUp(const KeyEventArgs &args);
	virtual void onPreviewLostKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onPreviewMouseDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseLeftButtonDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseLeftButtonUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseRightButtonDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseRightButtonUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseMove(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseWheel(const MouseWheelEventArgs &args);
	virtual void onPreviewTouchDown(const TouchEventArgs &args);
	virtual void onPreviewTouchEnter(const TouchEventArgs &args);
	virtual void onPreviewTouchLeave(const TouchEventArgs &args);
	virtual void onPreviewTouchMove(const TouchEventArgs &args);
	virtual void onPreviewTouchUp(const TouchEventArgs &args);

private:
	enum Flags
	{
		IsMouseOverCache,
		IsLeftButtonDownCache,
		IsRightButtonDownCache,
		Flags_Max = 32,
	};

	void changedLogicParent(UIElement* parent);
	void onMouseMoveThunk(const MouseEventArgs &e, const Point &pt);
	void onMouseButtonThunk(const MouseButtonEventArgs &e, const Point &pt);

	UIElement	*m_parent;
	std::map<size_t, std::vector<RoutedEventHandler>>	m_eventHandlers;
	std::bitset<Flags_Max>	m_flags;
	Size m_lastMesaaeAvailabelSize;
	bool m_measureInProgress;
	Size m_desiredSize;
	Point m_offsetToParent;
	Size m_renderSize;

	friend class Window;
	friend class UIElementCollection;
};

}